#ifndef TASKPAGE_H
#define TASKPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QDateTime>
#include <QComboBox>
#include "basepage.h"


class TaskPage : public BasePage
{
    Q_OBJECT

public:
    explicit TaskPage(QWidget *parent = nullptr);

private slots:
    void addNewTask();
    void switchList(int index);

private:
    void setupUi();
    void createTaskItem(const QString &text, const QDateTime &deadline);

    QPushButton *addButton;
    QComboBox *taskTypeCombo;
    QListWidget *upcomingList;
    QListWidget *completedList;
    QStackedWidget *listStack;
};

#endif
