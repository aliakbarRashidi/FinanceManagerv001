#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QDebug>

#include "databasehandler.h"
#include "commonfunctions.h"
#include "globaldata.h"

class SessionManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString author READ UserName WRITE SetUserName NOTIFY UserChanged)

public:
    SessionManager(QObject * parent = 0);
    ~SessionManager();

    static QObject *qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine);

    void SetUserName(const QString &userName) {
        if (userName != GlobalData::userName) {
            GlobalData::userName = userName;
            emit UserChanged();
        }
    }

    QString UserName() const {
        return GlobalData::userName;
    }

public slots:
    void CreateAccount(const QString &name, const QString &email, const QString &password, const QDateTime &birthdate);
    void Authenticate(const QString &value, const QString &field, const QString &password);

signals:
    void AccountCreationSucceeded();
    void AccountCreationFailed();
    void AuthenticationSucceeded();
    void AuthenticationFailed();
    void UserChanged();

private:
    DatabaseHandler m_databaseHandler;
};

#endif // SESSIONMANAGER_H
