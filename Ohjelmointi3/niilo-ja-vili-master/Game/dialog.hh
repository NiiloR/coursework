#ifndef DIALOG_HH
#define DIALOG_HH

#include <QDialog>
#include <QtGlobal>
#include <QMainWindow>
#include <QGraphicsScene>
#include "bettermainwindow.hh"



namespace Ui {
class Dialog;
}

namespace StudentSide {

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    /**
     * @brief setDifficulty emits the chosen difficulty level
     * @param difficulty level chosen by the palyer
     */
    void setDifficulty(std::string difficulty);

private slots:

    /**
     * @brief on_buttonEasy_clicked sets the difficulty as EASY
     */
    void on_buttonEasy_clicked();

    /**
     * @brief on_buttonMedium_clicked sets the difficulty as MEDIUM
     */
    void on_buttonMedium_clicked();

    /**
     * @brief on_buttonHard_clicked sets the difficulty as HARD
     */
    void on_buttonHard_clicked();

    /**
     * @brief on_pushButton_clicked emits the difficulty signal and closes the dialog
     */
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;

    //Used to store the selected difficulty level
    std::string difficulty_;


};

}


#endif // DIALOG_HH
