#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QVBoxLayout"
#include <QSplitter>
#include <QTableView>
#include <QComboBox>
#include <QPushButton>
#include <future>
#include <list>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_mainWidget = new QWidget();
    m_mainLayout = new QVBoxLayout();
    m_splitter = new QSplitter(Qt::Horizontal);
    m_bpwOne = new BinaryPackagesWidget({});
    m_bpwTwo = new BinaryPackagesWidget({});
    m_splitter->addWidget(m_bpwOne);
    m_splitter->addWidget(m_bpwTwo);

    //Compare
    m_compareWidget = new QWidget;
    m_compareLayout = new QVBoxLayout;
    m_compareView = new QTableView;
    m_compareBtnUpdate = new QPushButton{"Update"};
    m_compareCombo = new QComboBox;
    m_compareCombo->insertItem(0, "yes on the left but not on the right", {});
    m_compareCombo->insertItem(1, "yes on the right but not on the left", {});
    m_compareCombo->insertItem(2, "the release of which is larger on the left", {});
    m_functions.push_back(
       [&](const altrepoapi::BinaryPackages &one,
          const altrepoapi::BinaryPackages &two){
        return missingPackages(one,two);
    });
    m_functions.push_back(
       [&](const altrepoapi::BinaryPackages &one,
          const altrepoapi::BinaryPackages &two){
        return missingPackages(two, one);
    });
    m_compareModel = new BinaryPackagesModel{{}};
    m_compareView->setModel(m_compareModel);
    m_compareWidget->setLayout(m_compareLayout);
    m_compareLayout->addWidget(m_compareCombo);
    m_compareLayout->addWidget(m_compareBtnUpdate);
    m_compareLayout->addWidget(m_compareView);
    m_splitter->insertWidget(1,m_compareWidget);

    m_mainLayout->addWidget(m_splitter);
    m_mainWidget->setLayout(m_mainLayout);
    setCentralWidget(m_mainWidget);

    connect(m_compareBtnUpdate, &QPushButton::released, this, &MainWindow::update);
    show();
}

void MainWindow::
update(){
    m_compareBtnUpdate->setDisabled(true);
    m_compareBtnUpdate->setText("Calculated...");
    QCoreApplication::processEvents();
    auto left = m_bpwOne->packages();
    auto right = m_bpwTwo->packages();
    int currentIndex = m_compareCombo->currentIndex();
    try{
        m_compareModel->update(m_functions.at(currentIndex)(left,right));
    }
    catch(std::out_of_range exe){}
    catch(...){}
    m_compareBtnUpdate->setEnabled(true);
    m_compareBtnUpdate->setText("Update");
}

auto MainWindow::missingPackages(const altrepoapi::BinaryPackages &one,
                                 const altrepoapi::BinaryPackages &two)const
->altrepoapi::BinaryPackages
{
    altrepoapi::BinaryPackages result;
#ifdef MULTITHREAD
    std::list<std::pair<altrepoapi::BinaryPackages::PackageInfo,std::future<bool>>>futures;
    for(const auto &pInfo : one.vector()){
        futures.push_back({pInfo,
                  std::async(std::launch::async,
                        [=]()->bool{
                            auto iter = std::find_if(two.vector().begin(),two.vector().end(),[=](const auto& pi){return pi.name == pInfo.name;});
                            if(iter == two.vector().end())
                                return true;
                            return false;
                   })
        });
    }
    for(auto &pair : futures){
        if(!pair.second.get())
            continue;
        result << pair.first;
    }
#else
    for(const auto &pInfo : one.vector()){
            auto finded = std::find_if(two.vector().begin(),two.vector().end(),[=](const auto& pi){return pi.name == pInfo.name;});
            if(finded != two.vector().end())
                continue;
            result << pInfo;
    }
#endif
    return result;
}

MainWindow::~MainWindow()
{
    delete ui;
}

