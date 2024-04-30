#ifndef BINARYPACKAGESWIDGET_H
#define BINARYPACKAGESWIDGET_H

#include <QWidget>
#include "binarypackagesmodel.h"
#include <libs/AltRepoApi/altrepoapi.h>

class QVBoxLayout;
class QTableView;
class QPushButton;
class QComboBox;

class BinaryPackagesWidget : public QWidget
{
    Q_OBJECT
    altrepoapi::AltRepoApi m_altRepoApi;
    BinaryPackagesModel *m_model;
    QVBoxLayout *m_mainLayout;
    QTableView *m_tableView;
    QPushButton *m_btnUpdate;
    QComboBox *m_repoCombo;
public:
    explicit BinaryPackagesWidget(altrepoapi::BinaryPackages data,QWidget *parent = nullptr);
    ~BinaryPackagesWidget(){}

    void result(altrepoapi::BinaryPackages);
    void error(std::string error);
    const altrepoapi::BinaryPackages &packages() const;
public slots:
    void load();

};

#endif // BINARYPACKAGESWIDGET_H
