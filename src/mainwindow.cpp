#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QVBoxLayout"
#include <QSplitter>

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
    m_mainLayout->addWidget(m_splitter);
    m_mainWidget->setLayout(m_mainLayout);
    setCentralWidget(m_mainWidget);
    show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

