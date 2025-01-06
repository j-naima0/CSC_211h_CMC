/*#ifndef TASKPAGE_H
#define TASKPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QDateTime>
#include "basepage.h"

class TaskItem : public QWidget
{
    Q_OBJECT

public:
    TaskItem(const QString &text, const QDateTime &deadline, QWidget *parent = nullptr);
    QString text() const { return m_text; }
    QDateTime deadline() const { return m_deadline; }

signals:
    void completeClicked();
    void deleteClicked();

private:
    QString m_text;
    QDateTime m_deadline;
};
class TaskPage : public BasePage
{
    Q_OBJECT

public:
    explicit TaskPage(QWidget *parent = nullptr);

private slots:
    void addNewTask();
    void deleteTask();
    void switchTab(bool showCompleted);

private:
    void setupUi();
    TaskItem* createTaskItem(const QString &text, const QDateTime &deadline);

    QPushButton *addButton;
    QPushButton *upcomingTab;
    QPushButton *completedTab;
    QListWidget *upcomingList;
    QListWidget *completedList;
    QStackedWidget *listStack;
};

#endif // TASKPAGE_H
*/
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
