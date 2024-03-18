#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

private slots:
    void on_changerolebutton_clicked();

    void on_deleteuserbutton_clicked();

    void populateUserTable();

    void on_usertable_clicked();

    void on_logout_clicked();

private:
    Ui::admin *ui;
};

#endif // ADMIN_H
