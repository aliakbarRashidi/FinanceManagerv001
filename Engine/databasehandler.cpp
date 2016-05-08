/*!
  \author Esmerald Aliaj
  \version 0.1 03/03/16.
*/

#include "databasehandler.h"
#include "commonfunctions.h"
#include "globaldata.h"
#include "messagecontainer.h"

namespace
{
    const qint64 daysPerYear = 365;
}  // end namespace

DatabaseHandler::DatabaseHandler(QObject *parent) : QObject(parent)
{
    // Get the path to a known writable location and create it if it does not exist.
    // If it does exist check to see if it contains the database file, if not copy a new one.
    db_path = QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).filePath("database.db");
    CommonFunctions::copyFile(db_path);

    // We now try to open a connection to the database.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_path);

    qDebug() << db_path;
    if (db.isValid()) {
        if (!db.open()) {
            qWarning("Could not secure a connection to the database. Reason:: %s", qPrintable(db.lastError().text()));
            GlobalData::lastDatabaseConnectionError = db.lastError().text();
        }
    }
}

DatabaseHandler::~DatabaseHandler()
{
}

bool DatabaseHandler::CreateAccount(QString name, QString email, QString password, QDateTime birthdate)
{
    QString salt = CommonFunctions::generateSalt();
    QString hash = CommonFunctions::generateHash(password, salt);

    QSqlQuery query;
    query.setForwardOnly(true);
    query.prepare("INSERT INTO glf_users (glu_name, glu_passwordhash, glu_passwordsalt, glu_emailaddress, glu_emailverified, glu_birthdate, glu_age, glu_creationtime, glu_lastedittime) "
                  "VALUES (:glu_name, :glu_passwordhash, :glu_passwordsalt, :glu_emailaddress, :glu_emailverified, :glu_birthdate, :glu_age, :glu_creationtime, :glu_lastedittime)");
    query.bindValue(":glu_name", name);
    query.bindValue(":glu_passwordhash", hash);
    query.bindValue(":glu_passwordsalt", salt);
    query.bindValue(":glu_emailaddress", email);
    query.bindValue(":glu_emailverified", false);
    query.bindValue(":glu_birthdate", birthdate.toMSecsSinceEpoch());
    query.bindValue(":glu_age", birthdate.daysTo(QDateTime::currentDateTimeUtc()) / daysPerYear);
    query.bindValue(":glu_creationtime", QDateTime::currentMSecsSinceEpoch());
    query.bindValue(":glu_lastedittime", QDateTime::currentMSecsSinceEpoch());

    // Log attempt to create user
    if (!query.exec()) {
        qWarning("Could not create user account for user with Name: '%s' and Email: '%s'. Reason:: %s", qPrintable(name), qPrintable(email), qPrintable(query.lastError().text()));
        GlobalData::lastRegisterError = query.lastError().databaseText();
        return false;
    } else {
        qDebug("New user with Name: '%s' and Email: '%s' created.", qPrintable(name), qPrintable(email));
        return true;
    }
}

bool DatabaseHandler::Authenticate(QString value, QString field, QString password)
{
    QSqlQuery query;
    query.setForwardOnly(true);
    if (field == "email") {
        query.prepare("SELECT glu_passwordhash, glu_passwordsalt FROM glf_users WHERE glu_emailaddress = :value");
    } else if (field == "name") {
        query.prepare("SELECT glu_passwordhash, glu_passwordsalt FROM glf_users WHERE glu_name = :value");
    } else {
        GlobalData::lastLoginError = NO_EMAIL_AND_NAME;
        return false;
    }
    query.bindValue(":value", value);

    if (!query.exec()) {
        qWarning("Could not log in user: '%s'. Reason:: %s", qPrintable(value), qPrintable(query.lastError().text()));
        GlobalData::lastLoginError = query.lastError().databaseText();
        return false;
    } else {
        qDebug("User exists.");
        while (query.next()) {
            qDebug("Password hash and salt found.");
            QString hash = query.value(0).toString();
            QString salt = query.value(1).toString();
            if (hash == CommonFunctions::generateHash(password, salt)) {
                qDebug("Password is correct. User logged in.");
                return true;
            } else {
                qDebug("Password is not correct. User was not logged in.");
                GlobalData::lastLoginError = WRONG_PASSWORD;
                return false;
            }
        }
        GlobalData::lastLoginError = NO_HASH_SALT;
        qDebug("Password hash and salt not found.");
        return false;
    }
}

bool DatabaseHandler::CreateBudget(QString name, QString description, QDateTime expiry, int value)
{
    QSqlQuery query;
    query.setForwardOnly(true);
    query.prepare("INSERT INTO glf_budget (glb_name, glb_description, glb_createdat, glb_expiresat, glb_expired, glb_value) "
                  "VALUES (:glb_name, :glb_description, :glb_createdat, :glb_expiresat, :glb_expired, :glb_value)");
    query.bindValue(":glb_name", name);
    query.bindValue(":glb_description", description);
    query.bindValue(":glb_createdat", QDateTime::currentMSecsSinceEpoch());
    query.bindValue(":glb_expiresat", expiry.toMSecsSinceEpoch());
    query.bindValue(":glb_expired", expiry < QDateTime::currentDateTime());
    query.bindValue(":glb_value", value);

    // Log attempt to create user
    if (!query.exec()) {
        qWarning("Could not create budget with Name: '%s'. Reason:: %s", qPrintable(name), qPrintable(query.lastError().text()));
        GlobalData::lastRegisterError = query.lastError().databaseText();
        return false;
    } else {
        qDebug("New budget with Name: '%s' created.", qPrintable(name));
        return true;
    }
}

QList<QObject*> DatabaseHandler::ListBudget(const QString name, const QString nameFilterType, const QString nameFilterConnection,
                                 const QString description, const QString descriptionFilterType, const QString descriptionFilterConnection,
                                 const QString creationTime, const QString creationTimeFilterType, const QString creationTimeFilterConnection,
                                 const QString expiryFrom, const QString expiryTo, const QString expiryFilterConnection,
                                 const QString expired, const QString expiredFilterConnection,
                                 const QString value, const QString valueFilterType)
{
    QSqlQuery query;
    query.setForwardOnly(true);

    QString queryString;

    QString headerPart = "";
    QString namePart = "";
    QString descriptionPart = "";
    QString creationTimePart = "";
    QString expiryFromPart = "";
    QString expiredPart = "";
    QString valuePart = "";
    QString footerPart = "";

    // Header part.
    headerPart = "SELECT * FROM glf_budget WHERE";

    // Name part.
    if (name != "") {
        if (nameFilterType == QLatin1String("is equal"))
            namePart = " (glb_name = :glb_name1 OR :glb_name2 IS NULL) " % nameFilterConnection;
        else if (nameFilterType == QLatin1String("contains"))
            namePart = " (glb_name LIKE '%'||:glb_name1||'%' OR :glb_name2 IS NULL) " % nameFilterConnection;
        else
            namePart = " (glb_name NOT LIKE '%'||:glb_name1||'%' OR :glb_name2 IS NULL) " % nameFilterConnection;
    }

    // Description part.
    if (description != "") {
        if (descriptionFilterType == QLatin1String("is equal"))
            descriptionPart = " (glb_description = :glb_description1 OR :glb_description2 IS NULL) " % descriptionFilterConnection;
        else if (descriptionFilterType == QLatin1String("contains"))
            descriptionPart = " (glb_description LIKE '%'||:glb_description1||'%' OR :glb_description2 IS NULL) " % descriptionFilterConnection;
        else
            descriptionPart = " (glb_description NOT LIKE '%'||:glb_description1||'%' OR :glb_description2 IS NULL) " % descriptionFilterConnection;
    }

    // CreationTime part.
    if (creationTime != "") {
        if (creationTimeFilterType == QLatin1String("before"))
            creationTimePart = " (glb_createdat <= :glb_createdat1 OR :glb_createdat2 IS NULL) " % creationTimeFilterConnection;
        else
            creationTimePart = " (glb_createdat >= :glb_createdat1 OR :glb_createdat2 IS NULL) " % creationTimeFilterConnection;
    }

    // ExpiryFrom part.
    if (expiryFrom != "" || expiryTo != "") {
        expiryFromPart = " (glb_expiresat BETWEEN :expiryFrom1 AND :expiryTo1) OR (:expiryFrom2 IS NULL AND :expiryTo2 IS NULL) " % expiryFilterConnection;
    }

    // Expired part.
    if (expired != "N/A") {
        expiredPart = " (glb_expired = :glb_expired1 OR :glb_expired2 IS NULL) " % expiredFilterConnection;
    }

    // Value part.
    if (value != "") {
        if (valueFilterType == QLatin1String("is equal"))
            valuePart = " (glb_value = :glb_value1 OR :glb_value2 IS NULL) AND";
        else if (descriptionFilterType == QLatin1String("bigger"))
            valuePart = " (glb_value > :glb_value1 OR :glb_value2 IS NULL) AND";
        else
            valuePart = " (glb_value < :glb_value1 OR :glb_value2 IS NULL) AND";
    }

    footerPart = " glb_owner = :glb_owner AND glb_deleted = 0";

    queryString = headerPart %
            namePart %
            descriptionPart %
            creationTimePart %
            expiryFromPart %
            expiredPart %
            valuePart %
            footerPart;

    query.prepare(queryString);

    query.bindValue(":glb_name1", name);
    query.bindValue(":glb_name2", name);
    query.bindValue(":glb_description1", description);
    query.bindValue(":glb_description2", description);
    query.bindValue(":glb_createdat1", QDateTime::fromString(creationTime).toMSecsSinceEpoch());
    query.bindValue(":glb_createdat2", QDateTime::fromString(creationTime).toMSecsSinceEpoch());
    query.bindValue(":expiryFrom1", QDateTime::fromString(expiryFrom).toMSecsSinceEpoch());
    query.bindValue(":expiryTo1", QDateTime::fromString(expiryTo).toMSecsSinceEpoch());
    query.bindValue(":expiryFrom2", QDateTime::fromString(expiryFrom).toMSecsSinceEpoch());
    query.bindValue(":expiryTo2", QDateTime::fromString(expiryTo).toMSecsSinceEpoch());
    query.bindValue(":glb_expired1", expired == "Yes" ? true : false);
    query.bindValue(":glb_expired2", expired == "Yes" ? true : false);
    query.bindValue(":glb_value1", value.toInt());
    query.bindValue(":glb_value2", value.toInt());
    query.bindValue(":glb_owner", 1);

    if (!query.exec()) {
        qWarning("Could not get a list for all available budgets. Reason: %s", query.lastError().databaseText());
        GlobalData::lastRegisterError = query.lastError().databaseText();
    } else {
        QList<QObject*> budgets;
        while (query.next()) {
            Budget *budget = new Budget();
            budget->setName(query.value("glb_name").toString());
            budget->setDescription(query.value("glb_description").toString());

            budget->setCreationDate(QDateTime::fromMSecsSinceEpoch(query.value("glb_createdat").toLongLong()));

            budget->setExpirationDate(QDateTime::fromMSecsSinceEpoch(query.value("glb_expiresat").toLongLong()));

            qDebug() << QDateTime::fromMSecsSinceEpoch(query.value("glb_expiresat").toLongLong());

            budget->setExpired(query.value("glb_expired").toBool());
            budget->setValue(query.value("glb_value").toInt());

            budgets.append(budget);
        }

        return budgets;
    }
}
