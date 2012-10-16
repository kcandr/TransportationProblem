#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QList>

struct planCell {
    int plan;
    bool isVisited;
};

namespace Ui {
class MainWindow;
}
class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_addProvider_clicked();
    void on_delProvider_clicked();
    void on_addCustomer_clicked();
    void on_delCustomer_clicked();
    void on_startButton_clicked();

private:
    QStack<int> rowIndexStack;
    QStack<int> colIndexStack;
    Ui::MainWindow *ui;
    QList<int> a;
    QList<int> b;
    QList<QList<int> > c;
    QList<QList<planCell> > x;
    QList<int> u;
    QList<int> v;
    QList<int> minusR, minusC, plusR, plusC;
    int row, column;
    int brow, bcolumn;
    QStandardItemModel *modelU;
    QStandardItemModel *modelV;
    void fillProviders();
    void fillCustomers();
    void fillTariff();
    bool isClosed();
    void createPlan();
    void printPlan();
    void findUV();
    void printUV();
    bool planIsGood();
    void findBadCell();
    void findCycle();
    bool findInRow(int r);
    bool findInCol(int c);
    void findMinAndBuildNewPlan();
};

#endif // MAINWINDOW_H
