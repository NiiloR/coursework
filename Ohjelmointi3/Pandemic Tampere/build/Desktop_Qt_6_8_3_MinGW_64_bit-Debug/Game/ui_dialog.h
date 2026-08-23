/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTextBrowser *textBrowser;
    QRadioButton *buttonEasy;
    QRadioButton *buttonMedium;
    QRadioButton *buttonHard;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(289, 300);
        textBrowser = new QTextBrowser(Dialog);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(10, 10, 256, 192));
        buttonEasy = new QRadioButton(Dialog);
        buttonEasy->setObjectName("buttonEasy");
        buttonEasy->setGeometry(QRect(20, 220, 106, 26));
        buttonMedium = new QRadioButton(Dialog);
        buttonMedium->setObjectName("buttonMedium");
        buttonMedium->setGeometry(QRect(100, 220, 106, 26));
        buttonHard = new QRadioButton(Dialog);
        buttonHard->setObjectName("buttonHard");
        buttonHard->setGeometry(QRect(200, 220, 106, 26));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(90, 260, 84, 28));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        buttonEasy->setText(QCoreApplication::translate("Dialog", "Easy", nullptr));
        buttonMedium->setText(QCoreApplication::translate("Dialog", "Medium", nullptr));
        buttonHard->setText(QCoreApplication::translate("Dialog", "Hard", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "Continue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
