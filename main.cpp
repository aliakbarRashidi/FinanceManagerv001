#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QIcon>
#include <QDir>
#include <QtQml>

#include "financeengine.h"
#include "sessionmanager.h"
#include "filelogger.h"

//http://stackoverflow.com/questions/5183630/calendar-recurring-repeating-events-best-storage-method
//http://doc.qt.io/qt-5/topics-web-content.html
//https://wiki.qt.io/How_to_Use_a_QSqlQueryModel_in_QML
//http://stackoverflow.com/questions/20988224/best-way-to-have-qml-function-and-c-slot-and-vice-versa-for-the-same-item

FileLogger* logger;

QString searchConfigFile()
{
    QString binDir = QCoreApplication::applicationDirPath();
    QString appName = QCoreApplication::applicationName();
    QString fileName(appName + ".ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir + "/etc");
    searchList.append(binDir + "/../etc");
    searchList.append(binDir + "/../../etc"); // For development without shadow build
    searchList.append(binDir + "/../" + appName + "/etc"); // For development with shadow build
    searchList.append(binDir + "/../../" + appName + "/etc"); // For development with shadow build
    searchList.append(binDir + "/../../../" + appName + "/etc"); // For development with shadow build
    searchList.append(binDir + "/../../../../" + appName + "/etc"); // For development with shadow build
    searchList.append(binDir + "/../../../../../" + appName + "/etc"); // For development with shadow build
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir + "/" + fileName);
        if (file.exists())
        {
            // Found
            fileName = QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s", qPrintable(fileName));
            return fileName;
        }
    }

    // Not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found", qPrintable(dir), qPrintable(fileName));
    }
    qFatal("Cannot find config file %s", qPrintable(fileName));
    return 0;
}

int main(int argc, char *argv[])
{
    // Seed random number generator.
    qsrand(QDateTime::currentDateTime().toTime_t());

    // Create app, and register organization data.
    QGuiApplication app(argc, argv);
    app.setOrganizationName("greenleafone7");
    app.setOrganizationDomain("greenleafone7");
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());

    // Find the configuration file.
    QString configFileName = searchConfigFile();

    // Configure logging into a file.
//    QSettings* logSettings = new QSettings(configFileName, QSettings::IniFormat, &app);
//    logSettings->beginGroup("logging");
//    FileLogger* logger = new FileLogger(logSettings, 10000, &app);
//    logger->installMsgHandler();

    // Create qml engine and bindings.
    QQmlApplicationEngine engine;

    // Load main qml engine.
    engine.load(QUrl(QStringLiteral("qrc:/App/main.qml")));

    //qmlRegisterUncreatableType<SessionManager>("FinanceManager", 0, 1, "SessionManager", SessionManager::qmlSingleton); //This is useful where the type is only intended for providing attached properties or enum values.
    qmlRegisterSingletonType<SessionManager>("FinanceManager", 0, 1, "SessionManager", SessionManager::qmlSingleton);
    //qmlRegisterType<FinanceEngine>("FinanceManager", 0, 1, FinanceEngine());
    qmlRegisterSingletonType<FinanceEngine>("FinanceManager", 0, 1, "FinanceEngine", FinanceEngine::qmlSingleton);

    // Un-comment when you find a logo.
    // Set app icon
    /*QIcon icon(":images/logo-small.ico");
    app.setWindowIcon(icon)*/;

    return app.exec();
}
