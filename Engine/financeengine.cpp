/*!
  \author Esmerald Aliaj
  \version 0.1 03/03/16.
*/

#include "financeengine.h"

FinanceEngine::FinanceEngine(QObject *parent)
  : QObject(parent)
  , m_databaseHandler(parent)
{

}

FinanceEngine::~FinanceEngine()
{
}

void FinanceEngine::CreateBudget(const QString name, const QString description, const QDateTime expiry, const int value)
{
    if (m_databaseHandler.CreateBudget(name, description, expiry, value)) {
        Q_EMIT BudgetCreationSucceeded();
        return;
    } else {
        Q_EMIT BudgetCreationFailed();
        return;
    }
}

QList<QObject *> FinanceEngine::ListBudget(const QString name, const QString nameFilterType, const QString nameFilterConnection,
                               const QString description, const QString descriptionFilterType, const QString descriptionFilterConnection,
                               const QString creationTime, const QString creationTimeFilterType, const QString creationTimeFilterConnection,
                               const QString expiryFrom, const QString expiryTo, const QString expiryFilterConnection,
                               const QString expired, const QString expiredFilterConnection,
                               const QString value, const QString valueFilterType)
{
    return m_databaseHandler.ListBudget(name, nameFilterType, nameFilterConnection,
                                     description, descriptionFilterType, descriptionFilterConnection,
                                     creationTime, creationTimeFilterType, creationTimeFilterConnection,
                                     expiryFrom, expiryTo, expiryFilterConnection,
                                     expired, expiredFilterConnection,
                                     value, valueFilterType);
}

QObject* FinanceEngine::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    FinanceEngine *financeEngine = new FinanceEngine();
    return financeEngine;
}
