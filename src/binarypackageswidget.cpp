#include "binarypackageswidget.h"

#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QComboBox>

BinaryPackagesWidget::
BinaryPackagesWidget(altrepoapi::BinaryPackages data,QWidget *parent)
    : QWidget{parent}
{
    m_model = new BinaryPackagesModel(data);
    m_mainLayout = new QVBoxLayout();
    m_tableView = new QTableView();
    m_btnUpdate = new QPushButton("Load");
    m_repoCombo = new QComboBox();
    m_repoCombo->addItem("P9",altrepoapi::AltRepoApi::Repos::P9);
    m_repoCombo->addItem("P10",altrepoapi::AltRepoApi::Repos::P10);
    m_repoCombo->addItem("SISYPHUS",altrepoapi::AltRepoApi::Repos::SISYPHUS);

    m_tableView->setModel(m_model);
    m_mainLayout->addWidget(m_repoCombo);
    m_mainLayout->addWidget(m_btnUpdate);
    m_mainLayout->addWidget(m_tableView);
    setLayout(m_mainLayout);
    show();
    connect(m_btnUpdate,&QPushButton::released,this,&BinaryPackagesWidget::load);
}


void BinaryPackagesWidget::
result(altrepoapi::BinaryPackages pkg){
    m_btnUpdate->setEnabled(true);
    m_btnUpdate->setText("Load");
    m_model->update(pkg);
    m_tableView->update();
}

void BinaryPackagesWidget::
error(std::string error){
    m_btnUpdate->setEnabled(true);
    m_btnUpdate->setText("Load");
}

const altrepoapi::BinaryPackages &BinaryPackagesWidget::
packages()const{
    return m_model->data();
}

void BinaryPackagesWidget::
load(){
    m_btnUpdate->setText("Loading...");
    m_btnUpdate->setDisabled(true);

    m_altRepoApi.exportBinaryPackages_async((altrepoapi::AltRepoApi::Repos)m_repoCombo->currentIndex(),
               std::bind(&BinaryPackagesWidget::result,this,std::placeholders::_1),
               std::bind(&BinaryPackagesWidget::error,this,std::placeholders::_1));
}



