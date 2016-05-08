#ifndef BUDGET_H
#define BUDGET_H

#include <QDateTime>
#include <QObject>
#include <QString>

class Budget : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QDateTime creationDate READ creationDate WRITE setCreationDate NOTIFY creationDateChanged)
    Q_PROPERTY(QDateTime expirationDate READ expirationDate WRITE setExpirationDate NOTIFY expirationDateChanged)
    Q_PROPERTY(bool expired READ expired WRITE setExpired NOTIFY expiredChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit Budget(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    QDateTime creationDate() const;
    void setCreationDate(const QDateTime &creationDate);

    QDateTime expirationDate() const;
    void setExpirationDate(const QDateTime &expirationDate);

    bool expired() const;
    void setExpired(const bool &expired);

    int value() const;
    void setValue(const int &value);

signals:
    void nameChanged(const QString &name);
    void descriptionChanged(const QString &description);
    void creationDateChanged(const QDateTime &creationDate);
    void expirationDateChanged(const QDateTime &expirationDate);
    void expiredChanged(const bool &expired);
    void valueChanged(const int &value);

private:
    QString mName;
    QString mDescription;
    QDateTime mCreationDate;
    QDateTime mExpirationDate;
    bool mExpired;
    int mValue;
};

#endif // BUDGET_H
