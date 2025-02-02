#ifndef SCHEDULEPAGE_H
#define SCHEDULEPAGE_H


#include <QCalendarWidget>
#include <QPushButton>
#include <QListWidget>
#include <QStackedWidget>
#include "counselingdialog.h"
#include "basepage.h"


class SchedulePage : public BasePage {
    Q_OBJECT
public:
    explicit SchedulePage(QWidget *parent = nullptr);

private slots:
    void showCounselingRequest();
    //void dateSelected(const QDate &date);
    void switchList(int index);  // New slot for handling list switching

private:
    void setupUi();
    void addUpcomingAppointment(const QString &details);
    //QCalendarWidget *calendar;
    QPushButton *counselingBtn;
    QComboBox *appointmentTypeCombo;  // Dropdown menu
    QStackedWidget *listStack;        // Stack for upcoming/completed lists
    QListWidget *upcomingList;
    QListWidget *completedList;
};

#endif // SCHEDULEPAGE_H
