/*!
  \author Esmerald Aliaj
  \version 0.1 03/03/16.
*/

#include "globaldata.h"


namespace GlobalData
{
    QSettings *appSettings;
    unsigned int layoutMode;
    unsigned int currentUser;

    QString lastDatabaseConnectionError;
    QString lastRegisterError;
    QString lastLoginError;

    QString userName;
}
