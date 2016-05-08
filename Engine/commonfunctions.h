#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include <QFileInfo>
#include <QTranslator>
#include <QDir>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>

namespace
{
    const int saltLength = 20;
}

class CommonFunctions
{
public:
    CommonFunctions();

    static bool checkIfFileExists(QString path);
    static bool checkIfFileExists(QFileInfo path);
    static bool createDirectoryIfNotExists(QString path);
    static bool createDirectoryIfNotExists(QDir path);
    static bool copyFile(QString file);
    static QString generateSalt(const int length = saltLength);
    static QString generateHash(const QString password, const QString salt);

};

#endif // COMMONFUNCTIONS_H
