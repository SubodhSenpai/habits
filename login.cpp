#include "login.h"
#include "ui_login.h"
#include "habittracker.h"
#include "admin.h"


login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
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

login::~login()
{
    delete ui;
}

void login::on_loginbutton_clicked()
{
    QString name = ui->username->text();
    QString password = ui->password->text();

    QSqlDatabase habits = QSqlDatabase::database();
    QSqlQuery query(habits);

    query.prepare("SELECT * FROM Users WHERE name = :name AND password = :password");
    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if(query.exec() && query.next()){
        QString role = query.value("role").toString();

        if(role == "admin") {

            admin *adminwindow = new admin;
            adminwindow->setAttribute(Qt::WA_DeleteOnClose);
            adminwindow->show();
        } else if(role == "user") {

            habittracker *tracker = new habittracker;
            tracker->setAttribute(Qt::WA_DeleteOnClose);
            tracker->show();
        }

        this->close();
    } else {
        QMessageBox::critical(this, "Login Failed", "Failed to login. Please check your username and password.");
    }
    habits.close();
}

