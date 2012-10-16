#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QStack>

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

    fillProviders();
    fillCustomers();
    fillTariff();
    if (isClosed())
    {
        createPlan();
        //printPlan();
        findUV();
        printUV();
        if (!planIsGood()) {
            findBadCell();
            findCycle();
            findMinAndBuildNewPlan();

        };
    };
    printPlan();
}

void MainWindow::fillProviders()
{
    for (int i = 0; i < row; ++i)
        a << ui->tableProvider->item(i, 0)->text().toInt();
}

void MainWindow::fillCustomers()
{
    for (int j = 0; j < column; ++j)
        b << ui->tableCustomer->item(0, j)->text().toInt();
}

void MainWindow::fillTariff()
{
    for (int i = 0; i < row; ++i){
        QList<int> newList;
        for (int j = 0; j < column; ++j)
            newList.append(ui->table->item(i, j)->text().toInt());
        c.append(newList);
    }
}

bool MainWindow::isClosed()
{
    int sumA = 0;
    int sumB = 0;

    for (int i = 0; i < row; ++i)
        sumA += a.at(i);
    for (int j = 0; j < column; ++j)
        sumB += b.at(j);

    return sumA == sumB;
}

void MainWindow::createPlan()
{
    planCell tmp;
    tmp.plan = -1;
    tmp.isVisited = false;
    for (int l = 0; l < row; ++l) {
        QList<planCell> newList;
        for (int k = 0; k < column; ++k)
            newList.append(tmp);
        x.append(newList);
    }
    int filledCells = 0;
    int i = 0, j = 0;

    while (i != row)
    {
        if (a.at(i) > b.at(j))
        {
            x[i][j].plan = b[j];
            a[i] = a.at(i) - b.at(j);
            ++j;
            ++filledCells;
            continue;
        }
        else if (a.at(i) < b.at(j))
        {
            x[i][j].plan = a.at(i);
            b[j] = b.at(j) - a.at(i);
            ++i;
            ++filledCells;
            continue;
        }
        else
        {
            x[i][j].plan = a.at(i);
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
            if (x[i][j].plan != -1) {
                ui->table->item(i, j)->setText(
                            ui->table->item(i, j)->text().append(
                                " [" + QString::number(x[i][j].plan) + "]"));
                ui->table->item(i, j)->setSelected(true);
            };
}

void MainWindow::findUV()
{
    for (int i = 0; i < row; ++i)
        u << -32000;
    for (int j = 0; j < column; ++j)
        v << -32000;
    u[0] = 0;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            if (x[i][j].plan >= 0)
            {
                if (u[i] > -32000 && v[j] == -32000)
                {
                    v[j] = c.at(i).at(j) + u[i];
                };
                if (v[j] > -32000 && u[i] == -32000)
                {
                    u[i] = v[j] - c.at(i).at(j);
                };
            };
}

void MainWindow::printUV()
{
    modelU->clear();
    modelV->clear();
    for (int i = 0; i < row; ++i) {
        modelU->setItem(i, 0, new QStandardItem(QString::number(u[i])));
    };
    ui->tableU->setModel(modelU);

    for (int j = 0; j < column; ++j) {
        modelV->setItem(0, j, new QStandardItem(QString::number(v[j])));
    };
    ui->tableV->setModel(modelV);
}

bool MainWindow::planIsGood()
{
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            if (v[j] - u[i] > c.at(i).at(j))
                return false;
    return true;
}

void MainWindow::findBadCell()
{
    int max = -1;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            if (v[j] - u[i] - c.at(i).at(j) > max) {
                max = v[j] - u[i] - c.at(i).at(j);
                brow = i;
                bcolumn = j;
            };
}

void MainWindow::findCycle()
{
    rowIndexStack.push(brow);
    colIndexStack.push(bcolumn);
    do {
        if (!findInRow(rowIndexStack.top()) && rowIndexStack.top() != brow) {
            rowIndexStack.pop();
            colIndexStack.pop();
        };
        if (!findInCol(colIndexStack.top()) && colIndexStack.top() != bcolumn) {
            rowIndexStack.pop();
            colIndexStack.pop();
        };
        //qDebug() << rowIndexStack;
        //qDebug() << colIndexStack;
    } while (/*rowIndexStack.top() != brow && */colIndexStack.top() != bcolumn);
    qDebug() << rowIndexStack;
    qDebug() << colIndexStack;
}

bool MainWindow::findInRow(int r)
{
    for (int j = 0; j < column; ++j)
        if (x[r][j].plan > -1 && !x[r][j].isVisited){
            rowIndexStack.push(r);
            colIndexStack.push(j);
            x[r][j].isVisited = true;
            return true;
        };
    return false;
}

bool MainWindow::findInCol(int c)
{
    for (int i = 0; i < row; ++i)
        if (x[i][c].plan > -1 && !x[i][c].isVisited) {
            rowIndexStack.push(i);
            colIndexStack.push(c);
            x[i][c].isVisited = true;
            return true;
        };
    return false;
}

void MainWindow::findMinAndBuildNewPlan()
{
    int min = 1000;
    int i = 0;
    while (!rowIndexStack.isEmpty())
    {
        minusR << rowIndexStack.pop();
        minusC << colIndexStack.pop();
        if (x[minusR.at(i)][minusC.at(i)].plan < min)
            min = x[minusR[i]][minusC[i]].plan;
        plusR << rowIndexStack.pop();
        plusC << colIndexStack.pop();
        ++i;
    };
    /* Create new plan */
    for (int l = 0; l < minusR.size(); ++l)
    {
        if (x[minusR.at(l)][minusC[l]].plan > min)
            x[minusR.at(l)][minusC[l]].plan -= min;
        else
            x[minusR.at(l)][minusC[l]].plan = -1;
        x[minusR.at(l)][minusC[l]].isVisited = false;
    };
    for (int k = 0; k < plusR.size(); ++k)
    {
        if (x[plusR.at(k)][plusC.at(k)].plan == -1)
            x[plusR.at(k)][plusC.at(k)].plan = min;
        else
            x[plusR.at(k)][plusC.at(k)].plan += min;
        x[plusR.at(k)][plusC.at(k)].isVisited = false;
    };
    minusR.clear(); minusC.clear();
    plusR.clear(); plusC.clear();
    u.clear(); v.clear();
}
