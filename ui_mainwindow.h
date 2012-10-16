/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri 5. Oct 19:44:05 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *delCustomer;
    QPushButton *addCustomer;
    QPushButton *addProvider;
    QPushButton *delProvider;
    QPushButton *startButton;
    QTableWidget *tableProvider;
    QTableWidget *table;
    QTableWidget *tableCustomer;
    QTableView *tableU;
    QTableView *tableV;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(480, 440);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        delCustomer = new QPushButton(centralWidget);
        delCustomer->setObjectName(QString::fromUtf8("delCustomer"));
        delCustomer->setGeometry(QRect(170, 10, 75, 23));
        addCustomer = new QPushButton(centralWidget);
        addCustomer->setObjectName(QString::fromUtf8("addCustomer"));
        addCustomer->setGeometry(QRect(90, 10, 75, 23));
        addProvider = new QPushButton(centralWidget);
        addProvider->setObjectName(QString::fromUtf8("addProvider"));
        addProvider->setGeometry(QRect(10, 90, 23, 75));
        delProvider = new QPushButton(centralWidget);
        delProvider->setObjectName(QString::fromUtf8("delProvider"));
        delProvider->setGeometry(QRect(10, 170, 23, 75));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(40, 40, 41, 41));
        tableProvider = new QTableWidget(centralWidget);
        if (tableProvider->columnCount() < 1)
            tableProvider->setColumnCount(1);
        tableProvider->setObjectName(QString::fromUtf8("tableProvider"));
        tableProvider->setGeometry(QRect(40, 90, 45, 151));
        tableProvider->setColumnCount(1);
        tableProvider->horizontalHeader()->setVisible(false);
        tableProvider->horizontalHeader()->setDefaultSectionSize(40);
        tableProvider->verticalHeader()->setVisible(false);
        tableProvider->verticalHeader()->setDefaultSectionSize(40);
        tableProvider->verticalHeader()->setHighlightSections(false);
        table = new QTableWidget(centralWidget);
        table->setObjectName(QString::fromUtf8("table"));
        table->setGeometry(QRect(90, 90, 151, 151));
        table->setRowCount(0);
        table->setColumnCount(0);
        table->horizontalHeader()->setVisible(false);
        table->horizontalHeader()->setDefaultSectionSize(40);
        table->verticalHeader()->setVisible(false);
        table->verticalHeader()->setDefaultSectionSize(40);
        table->verticalHeader()->setHighlightSections(true);
        tableCustomer = new QTableWidget(centralWidget);
        if (tableCustomer->rowCount() < 1)
            tableCustomer->setRowCount(1);
        tableCustomer->setObjectName(QString::fromUtf8("tableCustomer"));
        tableCustomer->setGeometry(QRect(90, 40, 151, 45));
        tableCustomer->setRowCount(1);
        tableCustomer->horizontalHeader()->setVisible(false);
        tableCustomer->horizontalHeader()->setDefaultSectionSize(40);
        tableCustomer->verticalHeader()->setVisible(false);
        tableCustomer->verticalHeader()->setDefaultSectionSize(40);
        tableU = new QTableView(centralWidget);
        tableU->setObjectName(QString::fromUtf8("tableU"));
        tableU->setGeometry(QRect(420, 90, 45, 151));
        tableU->horizontalHeader()->setVisible(false);
        tableU->horizontalHeader()->setDefaultSectionSize(40);
        tableU->verticalHeader()->setVisible(false);
        tableU->verticalHeader()->setDefaultSectionSize(40);
        tableV = new QTableView(centralWidget);
        tableV->setObjectName(QString::fromUtf8("tableV"));
        tableV->setGeometry(QRect(90, 380, 151, 45));
        tableV->horizontalHeader()->setVisible(false);
        tableV->horizontalHeader()->setDefaultSectionSize(40);
        tableV->verticalHeader()->setVisible(false);
        tableV->verticalHeader()->setDefaultSectionSize(40);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        delCustomer->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        addCustomer->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        addProvider->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        delProvider->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
