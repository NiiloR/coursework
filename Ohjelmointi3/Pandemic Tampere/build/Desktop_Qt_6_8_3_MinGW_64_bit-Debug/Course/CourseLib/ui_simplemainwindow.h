/********************************************************************************
** Form generated from reading UI file 'simplemainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEMAINWINDOW_H
#define UI_SIMPLEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimpleMainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *gameView;
    QPushButton *startButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SimpleMainWindow)
    {
        if (SimpleMainWindow->objectName().isEmpty())
            SimpleMainWindow->setObjectName("SimpleMainWindow");
        SimpleMainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SimpleMainWindow->sizePolicy().hasHeightForWidth());
        SimpleMainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(SimpleMainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        gameView = new QGraphicsView(centralwidget);
        gameView->setObjectName("gameView");
        gameView->setGeometry(QRect(0, 0, 256, 192));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gameView->sizePolicy().hasHeightForWidth());
        gameView->setSizePolicy(sizePolicy2);
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(260, 0, 84, 28));
        SimpleMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SimpleMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        SimpleMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SimpleMainWindow);
        statusbar->setObjectName("statusbar");
        SimpleMainWindow->setStatusBar(statusbar);

        retranslateUi(SimpleMainWindow);

        QMetaObject::connectSlotsByName(SimpleMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SimpleMainWindow)
    {
        SimpleMainWindow->setWindowTitle(QCoreApplication::translate("SimpleMainWindow", "MainWindow", nullptr));
        startButton->setText(QCoreApplication::translate("SimpleMainWindow", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimpleMainWindow: public Ui_SimpleMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEMAINWINDOW_H
