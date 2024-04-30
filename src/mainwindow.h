#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <libs/AltRepoApi/altrepoapi.h>
#include "binarypackageswidget.h"
#include <vector>
#include <functional>

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

    QWidget *m_compareWidget;
    QVBoxLayout *m_compareLayout;
    QTableView *m_compareView;
    QPushButton *m_compareBtnUpdate;
    QComboBox *m_compareCombo;
    BinaryPackagesModel *m_compareModel;

    BinaryPackagesWidget *m_bpwOne;
    BinaryPackagesWidget *m_bpwTwo;
    std::vector<
        std::function<
            altrepoapi::BinaryPackages(const altrepoapi::BinaryPackages &one,
                                       const altrepoapi::BinaryPackages &two)
    >> m_functions;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void update();
public:
    auto missingPackages(const altrepoapi::BinaryPackages &one,
                         const altrepoapi::BinaryPackages &two)const
    ->altrepoapi::BinaryPackages ;


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
