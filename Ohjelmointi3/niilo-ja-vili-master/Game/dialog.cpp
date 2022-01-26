#include "dialog.hh"
#include "ui_dialog.h"


namespace StudentSide
{


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->pushButton->setDisabled(true);
    this->setGeometry(0,0,400,350);
    this->setWindowTitle("Pandemic Tampere");
    ui->textBrowser->setGeometry(20, 20, 360, 245);
    ui->buttonEasy->setGeometry(80,280,50,20);
    ui->buttonMedium->setGeometry(160, 280, 80, 20);
    ui->buttonHard->setGeometry(260, 280, 70, 20);

    ui->pushButton->setGeometry(160, 310, 80, 25);



    ui->textBrowser->setText("Welcome to Pandemic Tampere!");
    ui->textBrowser->append("");
    ui->textBrowser->append("Select difficulty and then press accept to proceed to the game.");
}

Dialog::~Dialog()
{
    delete ui;
}

//Only one button can be checked at a time
void Dialog::on_buttonEasy_clicked()
{
    difficulty_ = "easy";
    ui->buttonMedium->setChecked(false);
    ui->buttonHard->setChecked(false);
    //Continue button is available only after choosing a difficulty
    ui->pushButton->setDisabled(false);
}

void Dialog::on_buttonMedium_clicked()
{
    difficulty_ = "medium";
    ui->buttonEasy->setChecked(false);
    ui->buttonHard->setChecked(false);
    ui->pushButton->setDisabled(false);
}

void Dialog::on_buttonHard_clicked()
{
    difficulty_ = "hard";
    ui->buttonEasy->setChecked(false);
    ui->buttonMedium->setChecked(false);
    ui->pushButton->setDisabled(false);
}

void Dialog::on_pushButton_clicked()
{
    //Difficulty level is emited and thid Dialog object is deleted
    emit setDifficulty(difficulty_);
    delete this;

}

}
