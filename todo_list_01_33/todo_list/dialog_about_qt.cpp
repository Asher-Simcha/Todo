#include "dialog_about_qt.h"
#include "ui_dialog_about_qt.h"

Dialog_About_QT::Dialog_About_QT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_About_QT)
{
    ui->setupUi(this);
    ui->pushButton_1->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
}

Dialog_About_QT::~Dialog_About_QT()
{
    delete ui;
}
