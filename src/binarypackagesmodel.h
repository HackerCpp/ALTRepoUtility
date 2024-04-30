#ifndef BINARYPACKAGESMODEL_H
#define BINARYPACKAGESMODEL_H

#include <QAbstractItemModel>
#include <libs/AltRepoApi/binarypackages.h>
#include <vector>

class BinaryPackagesModel : public QAbstractItemModel
{
    altrepoapi::BinaryPackages m_data;
    std::vector<std::string> m_header{"Name","Epoch","Version","Release","Arch","Disttag","BuildTime","Source"};
public:
    BinaryPackagesModel(altrepoapi::BinaryPackages data);
    void update(altrepoapi::BinaryPackages data);
    const altrepoapi::BinaryPackages &data()const{return m_data;}


    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    //virtual QModelIndex sibling(int row, int column, const QModelIndex &idx) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


};

#endif // BINARYPACKAGESMODEL_H
