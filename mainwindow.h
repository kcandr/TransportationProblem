#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

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
    Ui::MainWindow *ui;
    int* a;
    int* b;
    int* c;
    int* x;
    int* u;
    int* v;
    int row, column;
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
};

#endif // MAINWINDOW_H
