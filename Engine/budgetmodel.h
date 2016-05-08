#ifndef BUDGETMODEL_H
#define BUDGETMODEL_H


#include <QAbstractListModel>
#include <QStringList>

#include "budget.h"

class BudgetModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AnimalRoles {
        TypeRole = Qt::UserRole + 1,
        SizeRole
    };

    BudgetModel(QObject *parent = 0);

    void addBudget(const Budget &budget);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Budget> m_budgets;
};

#endif // BUDGETMODEL_H
