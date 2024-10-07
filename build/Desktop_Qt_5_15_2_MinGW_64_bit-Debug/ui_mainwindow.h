/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *editId;
    QLabel *labelId;
    QGraphicsView *graphicsView;
    QTabWidget *tabWidget;
    QWidget *tabProperties;
    QTableWidget *tableWidget;
    QWidget *tabEvents;
    QWidget *tabControl;
    QLabel *labelPower;
    QPushButton *createRadioButton;
    QLineEdit *editPower;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1209, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        editId = new QLineEdit(centralwidget);
        editId->setObjectName(QString::fromUtf8("editId"));
        editId->setGeometry(QRect(1030, 90, 113, 22));
        editId->setReadOnly(true);
        labelId = new QLabel(centralwidget);
        labelId->setObjectName(QString::fromUtf8("labelId"));
        labelId->setGeometry(QRect(1000, 90, 21, 16));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 851, 551));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(846, 249, 361, 301));
        tabProperties = new QWidget();
        tabProperties->setObjectName(QString::fromUtf8("tabProperties"));
        tableWidget = new QTableWidget(tabProperties);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 351, 261));
        tableWidget->setAutoScroll(true);
        tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::ContiguousSelection);
        tabWidget->addTab(tabProperties, QString());
        tabEvents = new QWidget();
        tabEvents->setObjectName(QString::fromUtf8("tabEvents"));
        tabWidget->addTab(tabEvents, QString());
        tabControl = new QWidget();
        tabControl->setObjectName(QString::fromUtf8("tabControl"));
        tabWidget->addTab(tabControl, QString());
        labelPower = new QLabel(centralwidget);
        labelPower->setObjectName(QString::fromUtf8("labelPower"));
        labelPower->setGeometry(QRect(960, 50, 71, 20));
        createRadioButton = new QPushButton(centralwidget);
        createRadioButton->setObjectName(QString::fromUtf8("createRadioButton"));
        createRadioButton->setGeometry(QRect(980, 170, 91, 24));
        editPower = new QLineEdit(centralwidget);
        editPower->setObjectName(QString::fromUtf8("editPower"));
        editPower->setGeometry(QRect(1030, 50, 113, 22));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1209, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        editId->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        labelId->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\321\211\320\275\320\276\321\201\321\202\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\241\320\262\321\217\320\267\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabProperties), QCoreApplication::translate("MainWindow", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabEvents), QCoreApplication::translate("MainWindow", "\320\241\320\276\320\261\321\213\321\202\320\270\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabControl), QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        labelPower->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\321\211\320\275\320\276\321\201\321\202\321\214", nullptr));
        createRadioButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 PC", nullptr));
        editPower->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
