#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modelU = new QStandardItemModel(0, 1, this);
    modelV = new QStandardItemModel(1, 0, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addProvider_clicked()
{
    int row = ui->tableProvider->rowCount();

    ui->tableProvider->setRowCount(row + 1);
    ui->tableProvider->setFixedHeight((row + 1) * 40 + 25);
    modelU->setRowCount(row + 1);
    ui->tableU->setFixedHeight((row + 1) * 40 + 25);
    ui->table->setRowCount(row + 1);
    ui->table->setFixedHeight((row + 1) * 40 + 15);
}

void MainWindow::on_delProvider_clicked()
{
    int row = ui->tableProvider->rowCount();

    ui->tableProvider->setRowCount(row - 1);
    ui->tableProvider->setFixedHeight((row - 1) * 40 + 25);
    modelU->setRowCount(row - 1);
    ui->tableU->setFixedHeight((row - 1) * 40 + 15);
    ui->table->setRowCount(row - 1);
    ui->table->setFixedHeight((row - 1) * 40 + 15);
}

void MainWindow::on_addCustomer_clicked()
{
    int column = ui->tableCustomer->columnCount();
    ui->tableCustomer->setColumnCount(column + 1);
    ui->tableCustomer->setFixedWidth((column + 1) * 40 + 25);
    modelV->setColumnCount(column + 1);
    ui->tableV->setFixedWidth((column + 1) * 40 + 15);
    ui->table->setColumnCount(column + 1);
    ui->table->setFixedWidth((column + 1) * 50 + 15);
}

void MainWindow::on_delCustomer_clicked()
{
    int column = ui->tableCustomer->columnCount();
    ui->tableCustomer->setColumnCount(column - 1);
    ui->tableCustomer->setFixedWidth((column - 1) * 50 + 25);
    modelV->setColumnCount(column + 1);
    ui->tableV->setFixedWidth((column - 1) * 40 + 25);
    ui->table->setColumnCount(column - 1);
    ui->table->setFixedWidth((column - 1) * 50 + 15);
}

void MainWindow::on_startButton_clicked()
{
    row = ui->tableProvider->rowCount();
    column = ui->tableCustomer->columnCount();

    a = new int[row];
    v = new int[column];
    b = new int[column];
    u = new int[row];
    c = new int[row * column];

    fillProviders();
    fillCustomers();
    fillTariff();
    if (isClosed())
    {
        createPlan();
        printPlan();
        findUV();
        printUV();
    };
}

void MainWindow::fillProviders()
{
    for (int i = 0; i < row; ++i)
        a[i] = ui->tableProvider->item(i, 0)->text().toInt();
}

void MainWindow::fillCustomers()
{
    for (int j = 0; j < column; ++j)
        b[j] = ui->tableCustomer->item(0, j)->text().toInt();
}

void MainWindow::fillTariff()
{
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            c[i * column + j] = ui->table->item(i, j)->text().toInt();
}

bool MainWindow::isClosed()
{
    int sumA = 0;
    int sumB = 0;

    for (int i = 0; i < row; ++i)
        sumA += a[i];
    for (int j = 0; j < column; ++j)
        sumB += b[j];

    return sumA == sumB;
}

void MainWindow::createPlan()
{
    x = new int[row * column];
    for (int l = 0; l < row; ++l)
        for (int k = 0; k < column; ++k)
            x[l * column + k] = -1;
    int filledCells = 0;
    int i = 0, j = 0;

    while (i != row)
    {
        if (a[i] > b[j])
        {
            x[i * column + j] = b[j];
            a[i] = a[i] - b[j];
            ++j;
            ++filledCells;
            continue;
        }
        else if (a[i] < b[j])
        {
            x[i * column + j] = a[i];
            b[j] = b[j] - a[i];
            ++i;
            ++filledCells;
            continue;
        }
        else
        {
            x[i * column + j] = a[i];
            b[j] = 0;
            ++i;
            ++filledCells;
            continue;
        };
    }
}

void MainWindow::printPlan()
{
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            if (x[i * column + j] != -1) {
                ui->table->item(i, j)->setText(
                            ui->table->item(i, j)->text().append(
                                " [" + QString::number(x[i * column + j]) + "]"));
                ui->table->item(i, j)->setSelected(true);
            };
}

void MainWindow::findUV()
{
    for (int i = 0; i < row; ++i)
        u[i] = -32000;
    for (int j = 0; j < column; ++j)
        v[j] = -32000;
    u[0] = 0;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            if (x[i * column + j] >= 0)
            {
                if (u[i] > -32000 && v[j] == -32000)
                {
                    v[j] = c[i * column + j] + u[i];
                };
                if (v[j] > -32000 && u[i] == -32000)
                {
                    u[i] = v[j] - c[i * column + j];
                };
            };
}

void MainWindow::printUV()
{
    for (int i = 0; i < row; ++i) {
        modelU->setItem(i, 0, new QStandardItem(QString::number(u[i])));
    };
    ui->tableU->setModel(modelU);
    qDebug() << "--";
    for (int j = 0; j < column; ++j) {
        modelV->setItem(0, j, new QStandardItem(QString::number(v[j])));
    };
    ui->tableV->setModel(modelV);
    qDebug() << "==";
}
