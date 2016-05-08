#include "budgetmodel.h"

BudgetModel::BudgetModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void BudgetModel::addBudget(const Budget &budget)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_budgets << budget;
    endInsertRows();
}

int BudgetModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_budgets.count();
}

QVariant BudgetModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_budgets.count())
        return QVariant();

    const Budget &budget = m_budgets[index.row()];
    if (role == TypeRole)
        return budget.type();
    else if (role == SizeRole)
        return budget.size();
    return QVariant();
}

QHash<int, QByteArray> BudgetModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[SizeRole] = "size";
    return roles;
}
