#include "budget.h"

Budget::Budget(QObject *parent) :
    QObject(parent)
{
}

QString Budget::name() const
{
    return mName;
}

void Budget::setName(const QString &name)
{
    if (name != mName) {
        mName = name;
        emit nameChanged(mName);
    }
}

QString Budget::description() const
{
    return mName;
}

void Budget::setDescription(const QString &description)
{
    if (description != mDescription) {
        mDescription = description;
        emit descriptionChanged(mDescription);
    }
}

QDateTime Budget::creationDate() const
{
    return mCreationDate;
}

void Budget::setCreationDate(const QDateTime &creationDate)
{
    if (creationDate != mCreationDate) {
        mCreationDate = creationDate;
        emit creationDateChanged(mCreationDate);
    }
}

QDateTime Budget::expirationDate() const
{
    return mExpirationDate;
}

void Budget::setExpirationDate(const QDateTime &expirationDate)
{
    if (expirationDate != mExpirationDate) {
        mExpirationDate = expirationDate;
        emit expirationDateChanged(mExpirationDate);
    }
}

bool Budget::expired() const
{
    return mExpired;
}

void Budget::setExpired(const bool &expired)
{
    if (expired != mExpired) {
        mExpired = expired;
        emit expiredChanged(mExpired);
    }
}

int Budget::value() const
{
    return mValue;
}

void Budget::setValue(const int &value)
{
    if (value != mValue) {
        mValue = value;
        emit valueChanged(mValue);
    }
}
