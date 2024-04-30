#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <libs/AltRepoApi/altrepoapi.h>
#include "binarypackageswidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QSplitter;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *m_mainWidget;
    QVBoxLayout *m_mainLayout;
    QSplitter *m_splitter;
    BinaryPackagesWidget *m_bpwOne;
    BinaryPackagesWidget *m_bpwTwo;
    //altrepoapi::AltRepoApi m_altRepoApi;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
