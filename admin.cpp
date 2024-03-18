#include "admin.h"
#include "ui_admin.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTableView>

admin::admin(QWidget *parent) : QDialog(parent), ui(new Ui::admin) {
    ui->setupUi(this);
    QSqlDatabase habits = QSqlDatabase::addDatabase("QSQLITE");
    habits.setDatabaseName("C:/Program Files/SQLiteStudio/habits");

    if (!habits.open()) {
        ui->label->setText("Failed to open the database");
    } else {
        ui->label->setText("Connected....");
    }

    populateUserTable();
}

admin::~admin() {
    delete ui;
}

void admin::on_changerolebutton_clicked() {
    QString name = ui->changeusertext->text();

    QSqlDatabase habits = QSqlDatabase::database();
    QSqlQuery query(habits);

    query.prepare("UPDATE Users SET role = 'admin' WHERE name = :name AND role = 'user'");
    query.bindValue(":name", name);

    if (query.exec()) {
        QMessageBox::information(this, "Role Changed", "The user's role has been changed to admin.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to change the user's role.");
    }

    on_usertable_clicked();
}

void admin::on_deleteuserbutton_clicked() {
    QString name = ui->deleteusertext->text();

    QSqlDatabase habits = QSqlDatabase::database();
    QSqlQuery query(habits);

    query.prepare("DELETE FROM Users WHERE name = :name");
    query.bindValue(":name", name);

    if (query.exec()) {
        QMessageBox::information(this, "User Deleted", "The user has been deleted successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete the user.");
    }

    on_usertable_clicked();
}

void admin::populateUserTable() {
    QSqlTableModel *model = new QSqlTableModel(this, QSqlDatabase::database());
    model->setTable("Users");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->removeColumn(0);
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Email"));
    model->setHeaderData(2, Qt::Horizontal, tr("Phone No"));
    model->setHeaderData(3, Qt::Horizontal, tr("Password"));
    model->setHeaderData(4, Qt::Horizontal, tr("Role"));
    ui->usertable->setModel(model);
}

void admin::on_usertable_clicked() {
    populateUserTable();
}

void admin::on_logout_clicked()
{
    QApplication::quit();
}

