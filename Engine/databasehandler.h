#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>
#include <QStandardPaths>
#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QStringBuilder>

#include "budget.h"

//!  Database Handler.
/*!
    databasehandler.h
    Deal with CRUD database operations needed by all other classes.

    \author Esmerald Aliaj
    \version 0.1 03/03/16.
*/
class DatabaseHandler : public QObject
{
    Q_OBJECT

public:
    //! Default constructor.
    /*!
      Instantiate a database handler object.
      \param parent a QObject argument that will serve as the parent for the current handler.
      \sa DatabaseHandler(), ~DatabaseHandler(), dbCreateAccount()
    */
    DatabaseHandler(QObject * parent = 0);

    //! Destructor.
    /*!
      Destructor for a database handelr object.
      \sa DatabaseHandler(), ~DatabaseHandler(), dbCreateAccount()
    */
    ~DatabaseHandler();

    // Session Manager

    //! Create new account.
    /*!
      Create a new account, taking care of properly formatting dates and hashing the password.
      \return True if the operation was successful, false otherwise.
      \param name a QString argument that holds the name for the new account.
      \param email a QString argument that holds the email to be used for the new account.
      \param password a QString argument that that holds the password for the new account.
      \param birthdate a QDateTime argument that holds the birthdate for the new account.
      \sa DatabaseHandler(), ~DatabaseHandler(), dbCreateAccount()
    */
    static bool CreateAccount(QString name, QString email, QString password, QDateTime birthdate);

    //! Authenticate.
    /*!
      Try to log-in with the provided credentials.
      \return True if the operation was successful, false otherwise.
      \param name a QString argument that holds the name of the user to logon.
      \param email a QString argument that holds the email of the user to logon.
      \param password a QString argument that that holds the password of the user to logon.
      \sa DatabaseHandler(), ~DatabaseHandler(), dbCreateAccount()
    */
    static bool Authenticate(QString value, QString field, QString password);


    // Finance Engine

    //! Create Budget.
    /*!
      Create a new Budget Item.
      \return True if the operation was successful, false otherwise.
      \param name .
      \param description .
      \param expiry .
      \sa
    */
    static bool CreateBudget(QString name, QString description, QDateTime expiry, int value);

    //! List Budget.
    /*!
    */
    static QList<QObject*> ListBudget(const QString name, const QString nameFilterType, const QString nameFilterConnection,
                           const QString description, const QString descriptionFilterType, const QString descriptionFilterConnection,
                           const QString creationTime, const QString creationTimeFilterType, const QString creationTimeFilterConnection,
                           const QString expiryFrom, const QString expiryTo, const QString expiryFilterConnection,
                           const QString expired, const QString expiredFilterConnection,
                           const QString value, const QString valueFilterType);

private:
    QString db_path;
};

#endif // DATABASEHANDLER_H
