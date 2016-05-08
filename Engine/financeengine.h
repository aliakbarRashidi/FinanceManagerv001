#ifndef FinanceEngine_H
#define FinanceEngine_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

#include "databasehandler.h"
#include "commonfunctions.h"

#include "SqlQueryModel.h"

#if defined(Q_OS_WIN)
    #if defined(FINANCEMANAGERLIB_EXPORT)
        #define DECLSPEC Q_DECL_EXPORT
    #elif defined(FINANCEMANAGERLIB_IMPORT)
        #define DECLSPEC Q_DECL_IMPORT
    #endif
#endif
#if !defined(DECLSPEC)
    #define DECLSPEC
#endif

class FinanceEngine : public QObject
{
    Q_OBJECT

public:
    FinanceEngine(QObject * parent = 0);
    ~FinanceEngine();

    static QObject *qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine);

public slots:
    void CreateBudget(const QString name, const QString description, const QDateTime expiry, const int value);
    QList<QObject*> ListBudget(const QString name, const QString nameFilterType, const QString nameFilterConnection,
                    const QString description, const QString descriptionFilterType, const QString descriptionFilterConnection,
                    const QString creationTime, const QString creationTimeFilterType, const QString creationTimeFilterConnection,
                    const QString expiryFrom, const QString expiryTo, const QString expiryFilterConnection,
                    const QString expired, const QString expiredFilterConnection,
                    const QString value, const QString valueFilterType);

signals:
    void BudgetCreationSucceeded();
    void BudgetCreationFailed();

private:
    DatabaseHandler m_databaseHandler;
    //SessionManager *m_sessionManager;
};

#endif // FinanceEngine_H
