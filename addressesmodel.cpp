#include <QtNetwork/QNetworkInterface>

#include "addressesmodel.h"

AddressesModel::AddressesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    this->addresses = QNetworkInterface::allAddresses();

    QMutableListIterator<QHostAddress> iterator(this->addresses);
    while (iterator.hasNext()) {
        QHostAddress address = iterator.next();
        if (address.protocol() != QAbstractSocket::IPv4Protocol) {
            iterator.remove();
        }
    }
}

int AddressesModel::rowCount(const QModelIndex &parent) const
{
    return this->addresses.count();
}


QVariant AddressesModel::data(const QModelIndex &index, int role) const
{
    QHostAddress address = this->addresses.at(index.row());
    if (role == Qt::DisplayRole) {
        return address.toString();
    } else if (role == Qt::UserRole) {
        return address.toIPv4Address();
    } else {
        return QVariant();
    }
}
