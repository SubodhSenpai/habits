#ifndef WELCOME_H
#define WELCOME_H
#include <QDialog>
#include <QObject>
#include "ui_welcome.h"
#include "habittracker.h"
#include "login.h"
#include "signup.h"

namespace Ui {
class Welcome;
}

class Welcome : public QDialog
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = nullptr);
    ~Welcome();

private slots:
    void on_login_clicked();

    void on_signup_clicked();

private:
    Ui::Welcome *ui;
    habittracker *tracker;
    login *loginWindow;
    signup *signupwindow;
};

#endif // WELCOME_H
