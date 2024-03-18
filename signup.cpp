#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>
#include "login.h"


signup::signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);
    QSqlDatabase habits=QSqlDatabase::addDatabase("QSQLITE");
    habits.setDatabaseName("C:/Program Files/SQLiteStudio/habits");
    if(!habits.open()){
        ui->label->setText("Failed to open the database");
    }
    else{
        ui->label->setText("Connected....");
    }
}

signup::~signup()
{
    delete ui;
}

void signup::on_signupbutton_clicked()
{
        QString name = ui->username->text();
        QString password = ui->password->text();
        QString confirmPassword = ui->confirmpassword->text();

        if(password != confirmPassword){
            QMessageBox::critical(this, "Signup Failed", "Passwords do not match. Please try again.");
            return;
        }

        QSqlDatabase habits = QSqlDatabase::database();
        QSqlQuery query(habits);

        query.prepare("INSERT INTO Users (name, password, role) VALUES (:name, :password, :role)");
        query.bindValue(":name", name);
        query.bindValue(":password", password);
        query.bindValue(":role", "user");

        if(query.exec()){
            QMessageBox msgBox;
            msgBox.setText("User created");
            msgBox.setStandardButtons(QMessageBox::Ok);
            int ret = msgBox.exec();

            if(ret == QMessageBox::Ok) {
                this->close();
                login *loginwindow = new login;
                loginwindow->setAttribute(Qt::WA_DeleteOnClose);
                loginwindow->show();
            }
        } else {
            QMessageBox::critical(this, "Signup Failed", "Failed to sign up. Please try again.");
        }

        habits.close();
}

