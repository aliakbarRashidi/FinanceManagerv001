#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSettings>
#include <QModelIndexList>
#include <QStringList>
#include <QColor>
#include <QSet>


namespace GlobalData
{
    enum StartupDir
    {
        defaultDir = 0,
        rememberLastDir,
        specifiedDir
    };

    extern QSettings *appSettings;
    extern unsigned int layoutMode;
    extern unsigned int currentUser;

    extern QString lastDatabaseConnectionError;
    extern QString lastRegisterError;
    extern QString lastLoginError;

    extern QString userName;
}

#endif // GLOBAL_H
