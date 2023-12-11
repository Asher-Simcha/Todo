#ifndef DIALOG_ABOUT_QT_H
#define DIALOG_ABOUT_QT_H

#include <QDialog>

namespace Ui {
class Dialog_About_QT;
}

class Dialog_About_QT : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_About_QT(QWidget *parent = nullptr);
    ~Dialog_About_QT();

private:
    Ui::Dialog_About_QT *ui;
};

#endif // DIALOG_ABOUT_QT_H
