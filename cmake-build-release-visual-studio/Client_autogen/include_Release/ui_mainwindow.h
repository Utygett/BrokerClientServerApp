/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_9;
    QLabel *lbCurrCourse;
    QLabel *label_6;
    QLineEdit *lineBuyPrice;
    QLabel *label_4;
    QLineEdit *lineBuyAmount;
    QPushButton *pbBuy;
    QLabel *label_7;
    QLineEdit *lineSellPrice;
    QLabel *label_8;
    QLineEdit *lineSellAmount;
    QPushButton *pbSell;
    QLabel *lbFirstCurrName;
    QLabel *lbFirstCurrencyCount;
    QLabel *lbSecondCurrencyName;
    QLabel *lbSecondCurrencyCount;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QComboBox *currencyComboBox;
    QLabel *label;
    QTextBrowser *tbActiveDeals;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTextBrowser *tbBuyOrders;
    QLabel *label_3;
    QTextBrowser *tbSellOrders;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 40, -1, 40);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout->addWidget(label_9);

        lbCurrCourse = new QLabel(centralwidget);
        lbCurrCourse->setObjectName(QString::fromUtf8("lbCurrCourse"));

        verticalLayout->addWidget(lbCurrCourse);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        lineBuyPrice = new QLineEdit(centralwidget);
        lineBuyPrice->setObjectName(QString::fromUtf8("lineBuyPrice"));
        lineBuyPrice->setMinimumSize(QSize(1, 0));

        verticalLayout->addWidget(lineBuyPrice);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        lineBuyAmount = new QLineEdit(centralwidget);
        lineBuyAmount->setObjectName(QString::fromUtf8("lineBuyAmount"));

        verticalLayout->addWidget(lineBuyAmount);

        pbBuy = new QPushButton(centralwidget);
        pbBuy->setObjectName(QString::fromUtf8("pbBuy"));

        verticalLayout->addWidget(pbBuy);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout->addWidget(label_7);

        lineSellPrice = new QLineEdit(centralwidget);
        lineSellPrice->setObjectName(QString::fromUtf8("lineSellPrice"));

        verticalLayout->addWidget(lineSellPrice);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        lineSellAmount = new QLineEdit(centralwidget);
        lineSellAmount->setObjectName(QString::fromUtf8("lineSellAmount"));

        verticalLayout->addWidget(lineSellAmount);

        pbSell = new QPushButton(centralwidget);
        pbSell->setObjectName(QString::fromUtf8("pbSell"));

        verticalLayout->addWidget(pbSell);

        lbFirstCurrName = new QLabel(centralwidget);
        lbFirstCurrName->setObjectName(QString::fromUtf8("lbFirstCurrName"));

        verticalLayout->addWidget(lbFirstCurrName);

        lbFirstCurrencyCount = new QLabel(centralwidget);
        lbFirstCurrencyCount->setObjectName(QString::fromUtf8("lbFirstCurrencyCount"));

        verticalLayout->addWidget(lbFirstCurrencyCount);

        lbSecondCurrencyName = new QLabel(centralwidget);
        lbSecondCurrencyName->setObjectName(QString::fromUtf8("lbSecondCurrencyName"));

        verticalLayout->addWidget(lbSecondCurrencyName);

        lbSecondCurrencyCount = new QLabel(centralwidget);
        lbSecondCurrencyCount->setObjectName(QString::fromUtf8("lbSecondCurrencyCount"));

        verticalLayout->addWidget(lbSecondCurrencyCount);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(40, -1, 40, -1);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_3->addWidget(label_5);

        currencyComboBox = new QComboBox(centralwidget);
        currencyComboBox->setObjectName(QString::fromUtf8("currencyComboBox"));

        verticalLayout_3->addWidget(currencyComboBox);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        tbActiveDeals = new QTextBrowser(centralwidget);
        tbActiveDeals->setObjectName(QString::fromUtf8("tbActiveDeals"));

        verticalLayout_3->addWidget(tbActiveDeals);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        tbBuyOrders = new QTextBrowser(centralwidget);
        tbBuyOrders->setObjectName(QString::fromUtf8("tbBuyOrders"));

        verticalLayout_2->addWidget(tbBuyOrders);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        tbSellOrders = new QTextBrowser(centralwidget);
        tbSellOrders->setObjectName(QString::fromUtf8("tbSellOrders"));

        verticalLayout_2->addWidget(tbSellOrders);


        gridLayout->addLayout(verticalLayout_2, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \320\272\321\203\321\200\321\201", nullptr));
        lbCurrCourse->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\246\320\265\320\275\320\260", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        pbBuy->setText(QApplication::translate("MainWindow", "\320\232\321\203\320\277\320\270\321\202\321\214", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\320\246\320\265\320\275\320\260", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        pbSell->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\264\320\260\321\202\321\214", nullptr));
        lbFirstCurrName->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lbFirstCurrencyCount->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lbSecondCurrencyName->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lbSecondCurrencyCount->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \320\262\321\213\320\273\321\216\321\202\321\203", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\222\320\260\321\210\320\270 \320\260\320\272\321\202\320\270\320\262\320\275\321\213\320\265 \321\201\320\264\320\265\320\273\320\272\320\270", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270 \320\275\320\260 \320\277\320\276\320\272\321\203\320\277\320\272\321\203", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270 \320\275\320\260 \320\277\321\200\320\276\320\264\320\260\320\266\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
