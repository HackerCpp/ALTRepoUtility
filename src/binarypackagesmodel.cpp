#include "binarypackagesmodel.h"
#include <QModelIndex>

BinaryPackagesModel::
BinaryPackagesModel(altrepoapi::BinaryPackages data)
    : m_data(data)
{

}


void BinaryPackagesModel::
update(altrepoapi::BinaryPackages data){
    beginRemoveRows(QModelIndex(), 0, m_data.size());
    endRemoveRows();
    beginInsertRows(QModelIndex(), 0, data.size());
    m_data = data;
    endInsertRows();
}


QModelIndex BinaryPackagesModel::
index(int row, int column, const QModelIndex &parent ) const{
    //if(parent.isValid())
      //  return QModelIndex();
    if(row >= m_data.size())
        return QModelIndex();
    return createIndex(row, column, nullptr);
}

QModelIndex BinaryPackagesModel::
parent(const QModelIndex &child) const {
    if(!child.isValid())
        return QModelIndex();
    return QModelIndex();
}
//QModelIndex BinaryPackagesModel::
//sibling(int row, int column, const QModelIndex &idx) const {

//}

int BinaryPackagesModel::
rowCount(const QModelIndex &parent ) const {
    return m_data.size();
}

int BinaryPackagesModel::
columnCount(const QModelIndex &parent ) const {
    return m_header.size();
}
bool BinaryPackagesModel::
hasChildren(const QModelIndex &parent ) const {
   return false;
}

QVariant BinaryPackagesModel::
data(const QModelIndex &index, int role ) const {
    if(role == Qt::DisplayRole){
        auto packageInfo = m_data.at(index.row());
        switch(index.column()){
            case 0: return QString::fromStdString(packageInfo.name);
            case 1: return QString::number(packageInfo.epoch);
            case 2: return QString::fromStdString(packageInfo.version);
            case 3: return QString::fromStdString(packageInfo.release);
            case 4: return QString::fromStdString(packageInfo.arch);
            case 5: return QString::fromStdString(packageInfo.disttag);
            case 6: return QString::number(packageInfo.buildTime);
            case 7: return QString::fromStdString(packageInfo.source);
        }
    }
    return QVariant();
}

QVariant BinaryPackagesModel::
headerData(int section, Qt::Orientation orientation, int role ) const {
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return QString::fromStdString(m_header.at(section));
    return QVariant();
}
