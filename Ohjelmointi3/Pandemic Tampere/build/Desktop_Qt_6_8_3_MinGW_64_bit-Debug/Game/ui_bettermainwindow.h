/********************************************************************************
** Form generated from reading UI file 'bettermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BETTERMAINWINDOW_H
#define UI_BETTERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BetterMainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *ikkuna;
    QPushButton *startButton;
    QPushButton *buttonLeft;
    QPushButton *buttonRight;
    QPushButton *buttonUp;
    QPushButton *buttonDown;
    QPushButton *buttonInfect;
    QTextBrowser *textBrowser;
    QTextBrowser *infoScreen;
    QTextBrowser *timeWindow;
    QPushButton *buttonQuit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BetterMainWindow)
    {
        if (BetterMainWindow->objectName().isEmpty())
            BetterMainWindow->setObjectName("BetterMainWindow");
        BetterMainWindow->resize(800, 600);
        centralwidget = new QWidget(BetterMainWindow);
        centralwidget->setObjectName("centralwidget");
        ikkuna = new QGraphicsView(centralwidget);
        ikkuna->setObjectName("ikkuna");
        ikkuna->setGeometry(QRect(240, 160, 256, 192));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(100, 480, 84, 28));
        buttonLeft = new QPushButton(centralwidget);
        buttonLeft->setObjectName("buttonLeft");
        buttonLeft->setGeometry(QRect(220, 460, 84, 28));
        buttonRight = new QPushButton(centralwidget);
        buttonRight->setObjectName("buttonRight");
        buttonRight->setGeometry(QRect(420, 460, 84, 28));
        buttonUp = new QPushButton(centralwidget);
        buttonUp->setObjectName("buttonUp");
        buttonUp->setGeometry(QRect(320, 410, 84, 28));
        buttonDown = new QPushButton(centralwidget);
        buttonDown->setObjectName("buttonDown");
        buttonDown->setGeometry(QRect(320, 460, 84, 28));
        buttonInfect = new QPushButton(centralwidget);
        buttonInfect->setObjectName("buttonInfect");
        buttonInfect->setGeometry(QRect(450, 410, 84, 28));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(240, 50, 141, 41));
        infoScreen = new QTextBrowser(centralwidget);
        infoScreen->setObjectName("infoScreen");
        infoScreen->setGeometry(QRect(575, 451, 201, 61));
        timeWindow = new QTextBrowser(centralwidget);
        timeWindow->setObjectName("timeWindow");
        timeWindow->setGeometry(QRect(30, 441, 111, 31));
        buttonQuit = new QPushButton(centralwidget);
        buttonQuit->setObjectName("buttonQuit");
        buttonQuit->setGeometry(QRect(10, 0, 84, 28));
        BetterMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BetterMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        BetterMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(BetterMainWindow);
        statusbar->setObjectName("statusbar");
        BetterMainWindow->setStatusBar(statusbar);

        retranslateUi(BetterMainWindow);

        QMetaObject::connectSlotsByName(BetterMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BetterMainWindow)
    {
        BetterMainWindow->setWindowTitle(QCoreApplication::translate("BetterMainWindow", "MainWindow", nullptr));
        startButton->setText(QCoreApplication::translate("BetterMainWindow", "Start", nullptr));
        buttonLeft->setText(QCoreApplication::translate("BetterMainWindow", "<-", nullptr));
        buttonRight->setText(QCoreApplication::translate("BetterMainWindow", "->", nullptr));
        buttonUp->setText(QCoreApplication::translate("BetterMainWindow", "Up", nullptr));
        buttonDown->setText(QCoreApplication::translate("BetterMainWindow", "Down", nullptr));
        buttonInfect->setText(QCoreApplication::translate("BetterMainWindow", "Infect", nullptr));
        buttonQuit->setText(QCoreApplication::translate("BetterMainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BetterMainWindow: public Ui_BetterMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BETTERMAINWINDOW_H
