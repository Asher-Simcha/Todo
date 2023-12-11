#ifndef DIALOG_BHATTACHARJEE_H
#define DIALOG_BHATTACHARJEE_H

#include <QDialog>

namespace Ui {
class Dialog_Bhattacharjee;
}

class Dialog_Bhattacharjee : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Bhattacharjee(QWidget *parent = nullptr);
    ~Dialog_Bhattacharjee();

private:
    Ui::Dialog_Bhattacharjee *ui;
};

#endif // DIALOG_BHATTACHARJEE_H
