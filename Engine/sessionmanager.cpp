#include "sessionmanager.h"

SessionManager::SessionManager(QObject *parent)
    : QObject(parent)
    , m_databaseHandler(parent)
{
}

SessionManager::~SessionManager()
{
}

void SessionManager::CreateAccount(const QString &name, const QString &email, const QString &password, const QDateTime &birthdate)
{
    if (m_databaseHandler.CreateAccount(name, email, password, birthdate)) {
        Q_EMIT AccountCreationSucceeded();
        return;
    } else {
        Q_EMIT AccountCreationFailed();
        return;
    }
}

void SessionManager::Authenticate(const QString &value, const QString &field, const QString &password)
{
    if (m_databaseHandler.Authenticate(value, field, password)) {
        Q_EMIT AuthenticationSucceeded();
        return;
    } else {
        Q_EMIT AuthenticationFailed();
        return;
    }
}

QObject* SessionManager::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    SessionManager *sessionManager = new SessionManager();
    return sessionManager;
}
