/*!
  \author Esmerald Aliaj
  \version 0.1 03/03/16.
*/

#include "commonfunctions.h"

CommonFunctions::CommonFunctions()
{

}

bool CommonFunctions::checkIfFileExists(QString path) {
    QFileInfo checkFile(path);
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

bool CommonFunctions::checkIfFileExists(QFileInfo checkFile) {
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

bool CommonFunctions::createDirectoryIfNotExists(QString path) {
    if (!QDir(path).exists()) {
        return QDir().mkdir(path);
    }
    return false;
}

bool CommonFunctions::createDirectoryIfNotExists(QDir path) {
    if (!path.exists()) {
        return path.mkpath(".");
    }
    return false;
}

bool CommonFunctions::copyFile(QString file) {
    QFileInfo fileInfo(file);
    if (checkIfFileExists(fileInfo)) {
        return true;
    } else {
        if (createDirectoryIfNotExists(fileInfo.dir())) {
            return QFile::copy(":/App/assets/database/database.db", file);
        } else {
            return false;
        }
    }
}

QString CommonFunctions::generateSalt(const int length) {
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+|`~;:,<.>/?'");

   QString randomString;
   for(int i = 0; i < length; ++i) {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

QString CommonFunctions::generateHash(const QString password, const QString salt) {
   QCryptographicHash hash(QCryptographicHash::Sha512);
   hash.addData(password.toLatin1());
   hash.addData(salt.toLatin1());
   return hash.result().toHex();
}
