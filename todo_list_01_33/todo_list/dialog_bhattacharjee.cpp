#include "dialog_bhattacharjee.h"
#include "ui_dialog_bhattacharjee.h"

Dialog_Bhattacharjee::Dialog_Bhattacharjee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Bhattacharjee)
{
    ui->setupUi(this);
    ui->pushButton_1->setVisible(false);
    ui->pushButton_2->setVisible(false);
}

Dialog_Bhattacharjee::~Dialog_Bhattacharjee()
{
    delete ui;
}
