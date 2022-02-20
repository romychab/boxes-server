#ifndef ADDRESSESMODEL_H
#define ADDRESSESMODEL_H

#include <QAbstractListModel>
#include <QtNetwork/QNetworkInterface>

class AddressesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AddressesModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QList<QHostAddress> addresses;
private:
};

#endif // ADDRESSESMODEL_H
