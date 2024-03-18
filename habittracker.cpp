#include "habittracker.h"
#include "ui_habittracker.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include <functional>


class HabitTracker;

habittracker::habittracker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::habittracker)
{
    ui->setupUi(this);
}

habittracker::~habittracker()
{
    delete ui;
}

void habittracker::on_Enterhabit_clicked()
{
    QString habitText = ui->addhabbittext->text();
    if (!habitsByDate.contains(habitText)) {
        habitsByDate[habitText] = QStringList();
        qDebug() << "Habit added: " << habitText;
    } else {
        qDebug() << "Habit already exists: " << habitText;
    }

    updateHabitList();
}

void habittracker::on_deletehabit_clicked()
{
    QString habitToDelete = ui->deletehabittext->text();
    if (habitsByDate.contains(habitToDelete)) {
        habitsByDate.remove(habitToDelete);
        qDebug() << "Habit deleted: " << habitToDelete;
    } else {
        qDebug() << "Habit not found: " << habitToDelete;
    }

    updateHabitList();
}

void habittracker::on_changehabit_clicked()
{
    QString habitToReplace = ui->changefrom->text();
    QString newHabitText = ui->changeto->text();

    if (habitsByDate.contains(habitToReplace)) {
        habitsByDate.remove(habitToReplace);
        habitsByDate[newHabitText] = QStringList();
        qDebug() << "Habit changed from: " << habitToReplace << " to: " << newHabitText;
    } else {
        qDebug() << "Habit not found: " << habitToReplace;
    }

    updateHabitList();
}

void habittracker::updateHabitList()
{
    ui->habitlist->clear();
    ui->habitlist->setColumnCount(1);
    ui->habitlist->setHorizontalHeaderLabels(QStringList() << "Habits");
    ui->habitlist->setRowCount(habitsByDate.size());
    int i = 0;
    for (auto it = habitsByDate.begin(); it != habitsByDate.end(); ++it) {
        QTableWidgetItem* item = new QTableWidgetItem(it.key());
        ui->habitlist->setItem(i, 0, item);
        i++;
    }
}

void habittracker::on_habitlist_cellActivated(int row, int /*column*/)
{
    QString habit = ui->habitlist->item(row, 0)->text();
    qDebug() << "Selected habit: " << habit;
}

void habittracker::on_deleteHabitForDate_clicked()
{
    QString habitToDelete = ui->deletehabittext->text();
    QDate dateToDelete = ui->calender->selectedDate();
    QString dateString = dateToDelete.toString("yyyy-MM-dd");

    if (habitsByDate.contains(habitToDelete)) {
        QStringList &habitsForDate = habitsByDate[habitToDelete];
        int removedCount = habitsForDate.removeAll(dateString);
        if (removedCount > 0) {
            qDebug() << "Habit deleted for date: " << dateString << " - Habit: " << habitToDelete;
        } else {
            qDebug() << "Habit not found for date: " << dateString << " - Habit: " << habitToDelete;
        }
    } else {
        qDebug() << "No habits found for date: " << dateString;
    }
}

void habittracker::on_calender_activated(const QDate &date)
{
    QString habitTextToAdd = ui->addhabbittext->text();
    QString habitTextToDelete = ui->deletehabittext->text();
    QString dateString = date.toString("yyyy-MM-dd");

    if (habitTextToAdd.isEmpty() && habitTextToDelete.isEmpty()) {
        qDebug() << "Both text boxes are empty.";
        return;
    }

    if (!habitTextToAdd.isEmpty()) {
        if (!habitsByDate.contains(habitTextToAdd)) {
            habitsByDate[habitTextToAdd] = QStringList();
        }
        habitsByDate[habitTextToAdd].append(dateString);
        qDebug() << "Habit added for date: " << dateString << " - Habit: " << habitTextToAdd;
    }

    if (!habitTextToDelete.isEmpty()) {
        if (habitsByDate.contains(habitTextToDelete)) {
            int removedCount = habitsByDate[habitTextToDelete].removeAll(dateString);
            if (removedCount > 0) {
                qDebug() << "Habit deleted for date: " << dateString << " - Habit: " << habitTextToDelete;
            } else {
                qDebug() << "Habit not found for date: " << dateString << " - Habit: " << habitTextToDelete;
            }
        } else {
            qDebug() << "No habits found for date: " << dateString;
        }
    }
}

void habittracker::on_from_userDateChanged(const QDate &date)
{
    startDate = date;
    updateHabitsTable();
}

void habittracker::on_to_userDateChanged(const QDate &date)
{
    endDate = date;
    updateHabitsTable();
}

void habittracker::updateHabitsTable()
{
    ui->table->clear();
    ui->table->setRowCount(0);

    ui->table->setHorizontalHeaderLabels(QStringList() << "Habit" << "Count");

    QMap<QString, int> filteredHabits;
    for (auto it = habitsByDate.begin(); it != habitsByDate.end(); ++it) {
        QString habit = it.key();
        QStringList dates = it.value();
        for (const QString& dateString : dates) {
            QDate date = QDate::fromString(dateString, "yyyy-MM-dd");
            if (date >= startDate && date <= endDate) {
                if (filteredHabits.contains(habit)) {
                    filteredHabits[habit]++;
                } else {
                    filteredHabits[habit] = 1;
                }
            }
        }
    }

    QList<QPair<int, QString>> sortedHabits;
    for (auto it = filteredHabits.begin(); it != filteredHabits.end(); ++it) {
        sortedHabits.append(qMakePair(it.value(), it.key()));
    }

    std::sort(sortedHabits.begin(), sortedHabits.end(), std::greater<QPair<int, QString>>());

    int row = 0;
    for (auto it = sortedHabits.begin(); it != sortedHabits.end(); ++it) {
        ui->table->insertRow(row);
        QTableWidgetItem* habitItem = new QTableWidgetItem(it->second);
        QTableWidgetItem* countItem;
        if(it->first == 0) {
            countItem = new QTableWidgetItem("Never");
        } else {
            countItem = new QTableWidgetItem(QString::number(it->first));
        }
        ui->table->setItem(row, 0, habitItem);
        ui->table->setItem(row, 1, countItem);
        qDebug() << "Row: " << row << " - Habit: " << habitItem->text() << " - Count: " << countItem->text();
        row++;
    }
}

void habittracker::on_table_cellActivated(int row, int /*column*/)
{
    QString habit = ui->table->item(row, 0)->text();
    QMessageBox::information(this, "Habit Details", "Selected habit: " + habit);
}

void habittracker::on_pushButton_clicked()
{
    QApplication::quit();
}

