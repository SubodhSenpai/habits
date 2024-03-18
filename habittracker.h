#ifndef HABITTRACKER_H
#define HABITTRACKER_H
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QCalendarWidget>
#include <QMap>
#include <QMessageBox>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class habittracker;
}
QT_END_NAMESPACE

class habittracker : public QMainWindow
{
    Q_OBJECT

public:
    habittracker(QWidget *parent = nullptr);
    ~habittracker();

private:
    Ui::habittracker *ui;
    QMap<QString, QStringList> habitsByDate;
    QDate startDate;
    QDate endDate;

private slots:
    // void on_deletehabit_clicked();
    void on_Enterhabit_clicked();
    void on_deletehabit_clicked();
    void updateHabitList();
    void on_habitlist_cellActivated(int row, int column);
    void on_calender_activated(const QDate &date);
    void on_deleteHabitForDate_clicked();
    void on_from_userDateChanged(const QDate &date);
    void on_to_userDateChanged(const QDate &date);
    void on_table_cellActivated(int row, int column);
    void updateHabitsTable();
    void on_changehabit_clicked();
    void on_pushButton_clicked();
};
#endif // HABITTRACKER_H
