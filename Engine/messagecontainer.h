#ifndef MESSAGECONTAINER_H
#define MESSAGECONTAINER_H

#include <QString>

const QString DATABASE_FILE_EXISTS = "Database file found for this user.";
const QString DATABASE_FILE_DOESNT_EXISTS = "Database file was not found for this user.";
const QString NO_EMAIL_AND_NAME = "You need to provide at least your email or username in order to login.";
const QString EMAIL_IN_USE = "This email is in use.";
const QString USERNAME_IN_USE = "This username is in use.";
const QString WRONG_PASSWORD = "Wrong password";
const QString NO_HASH_SALT = "Password hash and salt not found";

#endif // MESSAGECONTAINER_H
