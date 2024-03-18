#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "habittracker.h"
#include "admin.h"
#include<QtSql>
#include<QDebug>
#include<QFileInfo>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_loginbutton_clicked();

private:
    Ui::login *ui;
    habittracker *tracker;
    admin *adminwindow;
};

#endif // LOGIN_H
