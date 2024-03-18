#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "login.h"
#include<QtSql>
#include<QDebug>
#include<QFileInfo>

namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_signupbutton_clicked();

private:
    Ui::signup *ui;
    login *loginwindow;
};

#endif // SIGNUP_H
