/*#include "taskpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QDialogButtonBox>
#include <QCalendarWidget>
#include <QComboBox>

TaskItem::TaskItem(const QString &text, const QDateTime &deadline, QWidget *parent)
    : QWidget(parent), m_text(text), m_deadline(deadline)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 5, 10, 5);
    layout->setSpacing(10);

    QVBoxLayout *textLayout = new QVBoxLayout();

    QLabel *taskLabel = new QLabel(text);
    taskLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    taskLabel->setWordWrap(true);

    QString deadlineStr = deadline.toString("MM/dd/yyyy hh:mm AP");
    QLabel *deadlineLabel = new QLabel("Due: " + deadlineStr);
    deadlineLabel->setStyleSheet("color: #666666; font-size: 12px;");

    textLayout->addWidget(taskLabel);
    textLayout->addWidget(deadlineLabel);

    QPushButton *completeBtn = new QPushButton("Complete");
    completeBtn->setFixedWidth(100);
    completeBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1976D2;"
        "}"
        );

    QPushButton *deleteBtn = new QPushButton("Delete");
    deleteBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #f44336;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #d32f2f;"
        "}"
        );

    layout->addLayout(textLayout, 1);
    layout->addWidget(completeBtn);
    layout->addWidget(deleteBtn);

    connect(completeBtn, &QPushButton::clicked, this, &TaskItem::completeClicked);
    connect(deleteBtn, &QPushButton::clicked, this, &TaskItem::deleteClicked);
}

TaskPage::TaskPage(QWidget *parent) : BasePage(parent)
{
    setupUi();
}


void TaskPage::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);

    // Title
    QLabel *titleLabel = new QLabel("Task Planner");
    titleLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 28px;"
        "    color: #003366;"
        "    font-weight: bold;"
        "}"
        );
    titleLabel->setAlignment(Qt::AlignCenter);

    // Add Task Button
    addButton = new QPushButton("Add Task");
    addButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4ca181;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    // Task Type Combo Box (Upcoming/Completed)
    QComboBox *taskTypeCombo = new QComboBox;
    taskTypeCombo->addItems({"Upcoming", "Completed"});
    taskTypeCombo->setStyleSheet(
        "QComboBox {"
        "    background-color: #a1d67f;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 15px;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "}"
        "QComboBox:hover {"
        "    background-color: #e18e8e;"
        "}"
        "QComboBox::drop-down {"
        "    border: none;"
        "    padding-right: 10px;"
        "}"
        );

    listStack = new QStackedWidget;
    upcomingList = new QListWidget;
    completedList = new QListWidget;

    QString listStyle =
        "QListWidget {"
        "    background-color: #eae1cc;"
        "    border-radius: 8px;"
        "    padding: 5px;"
        "}"
        "QListWidget::item {"
        "    color: black;"
        "    padding: 10px;"
        "    border-bottom: 1px solid #555;"
        "    background-color: transparent;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: transparent;"
        "}";

    upcomingList->setStyleSheet(listStyle);
    completedList->setStyleSheet(listStyle);

    upcomingList->setWordWrap(true);
    upcomingList->setTextElideMode(Qt::ElideNone);
    completedList->setWordWrap(true);
    completedList->setTextElideMode(Qt::ElideNone);

    listStack->addWidget(upcomingList);
    listStack->addWidget(completedList);

    // Layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(taskTypeCombo);
    mainLayout->addWidget(listStack);

    // Connections
    connect(addButton, &QPushButton::clicked, this, &TaskPage::addNewTask);
    connect(taskTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            listStack, &QStackedWidget::setCurrentIndex);

    setStyleSheet("background-color: #eae1cc;");
}

void TaskPage::addNewTask()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add Task");
    dialog.setStyleSheet(
        "QDialog {"
        "    background-color: #eae1cc;"
        "}"
        );
    dialog.setMinimumWidth(400);
    dialog.setMinimumHeight(300);  // Reduced height

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->setSpacing(10);  // Reduced spacing
    layout->setContentsMargins(20, 20, 20, 20);

    // Task description
    QLabel *descLabel = new QLabel("Task description");
    descLabel->setStyleSheet(
        "QLabel {"
        "    background-color: transparent;"
        "    color: #333333;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        );

    QLineEdit *descEdit = new QLineEdit();
    descEdit->setStyleSheet(
        "QLineEdit {"
        "    color: #333333;"
        "    padding: 8px;"
        "    border: 1px solid #cccccc;"
        "    border-radius: 6px;"
        "    background-color: transparent;"
        "    font-size: 14px;"
        "}"
        "QLineEdit:focus {"
        "    border: 2px solid #2196F3;"
        "}"
        );
    descEdit->setPlaceholderText("Enter task description");

    // Deadline
    QLabel *deadlineLabel = new QLabel("Deadline");
    deadlineLabel->setStyleSheet(
        "QLabel {"
        "    background-color: transparent;"
        "    color: #333333;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        );

    QDateTimeEdit *deadlineEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    deadlineEdit->setCalendarPopup(true);
    deadlineEdit->setStyleSheet(
        "QDateTimeEdit {"
        "    color: #333333;"
        "    padding: 8px;"
        "    border: 1px solid #cccccc;"
        "    border-radius: 6px;"
        "    background-color: transparent;"
        "    font-size: 14px;"
        "}"
        "QDateTimeEdit:focus {"
        "    border: 2px solid #2196F3;"
        "}"
        "QDateTimeEdit::drop-down {"
        "    border: none;"
        "    width: 20px;"
        "}"
        "QCalendarWidget {"
        "    background-color: white;"
        "    color: black;"
        "}"
        "QCalendarWidget QToolButton {"
        "    color: black;"
        "    background-color: transparent;"
        "    margin: 2px;"
        "    border-radius: 4px;"
        "}"
        "QCalendarWidget QMenu {"
        "    background-color: white;"
        "    color: black;"
        "}"
        "QCalendarWidget QSpinBox {"
        "    color: black;"
        "    background-color: white;"
        "    selection-background-color: #2196F3;"
        "}"
        "QCalendarWidget QTableView {"
        "    background-color: white;"
        "    selection-background-color: #2196F3;"
        "    selection-color: white;"
        "}"
        "QCalendarWidget QAbstractItemView:enabled {"
        "    color: black;"
        "    background-color: white;"
        "    selection-background-color: #2196F3;"
        "    selection-color: white;"
        "}"
        "QCalendarWidget QWidget {"
        "    alternate-background-color: #f5f5f5;"
        "}"
        );

    // Buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    QPushButton *addButton = new QPushButton("Add");
    QPushButton *cancelButton = new QPushButton("Cancel");

    buttonBox->addButton(addButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    addButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 6px;"
        "    padding: 8px 24px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    cancelButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #f44336;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 6px;"
        "    padding: 8px 24px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #d32f2f;"
        "}"
        );

    layout->addWidget(descLabel);
    layout->addWidget(descEdit);
    layout->addWidget(deadlineLabel);
    layout->addWidget(deadlineEdit);
    layout->addSpacing(10);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted && !descEdit->text().isEmpty()) {
        TaskItem *taskItem = createTaskItem(descEdit->text(), deadlineEdit->dateTime());
        QListWidgetItem *item = new QListWidgetItem(upcomingList);
        item->setSizeHint(taskItem->sizeHint());
        upcomingList->setItemWidget(item, taskItem);
    }
}


TaskItem* TaskPage::createTaskItem(const QString &text, const QDateTime &deadline)
{
    QListWidgetItem *item = new QListWidgetItem;

    // Create widget for the item
    QWidget *itemWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(itemWidget);
    layout->setContentsMargins(10, 5, 10, 5);

    // Task text and deadline
    QString taskDetails = QString("%1 (Due: %2)")
                              .arg(text)
                              .arg(deadline.toString("MMM d, yyyy at h:mm AP"));

    QLabel *label = new QLabel(taskDetails);
    label->setWordWrap(true);
    label->setStyleSheet(
        "QLabel {"
        "    color: black;"
        "    font-size: 16px;"
        "    background: transparent;"
        "    padding: 5px;"
        "}"
        );

    QPushButton *completeBtn = new QPushButton("Complete");
    completeBtn->setFixedWidth(100);
    completeBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 5px 10px;"
        "    font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1976D2;"
        "}"
        );

    QPushButton *deleteBtn = new QPushButton("Delete");
    deleteBtn->setFixedWidth(100);
    deleteBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #f44336;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 5px 10px;"
        "    font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #d32f2f;"
        "}"
        );

    layout->addWidget(label, 1);
    layout->addWidget(completeBtn);
    layout->addWidget(deleteBtn);

    item->setSizeHint(itemWidget->sizeHint());

    // Connect buttons
    connect(completeBtn, &QPushButton::clicked, [=]() {
        int row = upcomingList->row(item);
        if (row != -1) {
            upcomingList->takeItem(row);
            QString completedText = QString("%1 (Completed: %2)\nOriginal Due Date: %3")
                                        .arg(text)
                                        .arg(QDateTime::currentDateTime().toString("MMM d, yyyy at h:mm AP"))
                                        .arg(deadline.toString("MMM d, yyyy at h:mm AP"));

            QListWidgetItem *completedItem = new QListWidgetItem;
            QLabel *completedLabel = new QLabel(completedText);
            completedLabel->setWordWrap(true);
            completedLabel->setStyleSheet(
                "QLabel {"
                "    color: black;"
                "    font-size: 16px;"
                "    background: transparent;"
                "    padding: 5px;"
                "}"
                );

            QWidget *completedWidget = new QWidget;
            QHBoxLayout *completedLayout = new QHBoxLayout(completedWidget);
            completedLayout->addWidget(completedLabel);

            completedItem->setSizeHint(completedWidget->sizeHint());
            completedList->addItem(completedItem);
            completedList->setItemWidget(completedItem, completedWidget);
        }
    });

    connect(deleteBtn, &QPushButton::clicked, [=]() {
        int row = upcomingList->row(item);
        if (row != -1) {
            delete upcomingList->takeItem(row);
        }
    });

    upcomingList->addItem(item);
    upcomingList->setItemWidget(item, itemWidget);

    return nullptr; // Since we're handling everything in this function
}

void TaskPage::switchTab(bool showCompleted)
{
    upcomingTab->setChecked(!showCompleted);
    completedTab->setChecked(showCompleted);
    listStack->setCurrentIndex(showCompleted ? 1 : 0);
}

void TaskPage::deleteTask()
{
    QPushButton *deleteBtn = qobject_cast<QPushButton*>(sender());
    if (!deleteBtn) return;

    QWidget *taskWidget = deleteBtn->parentWidget();
    for (int i = 0; i < upcomingList->count(); ++i) {
        if (upcomingList->itemWidget(upcomingList->item(i)) == taskWidget) {
            delete upcomingList->takeItem(i);
            break;
        }
    }
}
*/
#include "taskpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QDialogButtonBox>
#include <QCalendarWidget>

TaskPage::TaskPage(QWidget *parent) : BasePage(parent)
{
    setupUi();
}

void TaskPage::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);

    // Title
    QLabel *titleLabel = new QLabel("Task Planner");
    titleLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 28px;"
        "    color: #003366;"
        "    font-weight: bold;"
        "}"
        );
    titleLabel->setAlignment(Qt::AlignCenter);

    // Add Task Button
    addButton = new QPushButton("Add Task");
    addButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4ca181;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    // Task Type Combo Box (Upcoming/Completed)
    taskTypeCombo = new QComboBox;
    taskTypeCombo->addItems({"Upcoming", "Completed"});
    taskTypeCombo->setStyleSheet(
        "QComboBox {"
        "    background-color: #a1d67f;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 15px;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "}"
        "QComboBox:hover {"
        "    background-color: #e18e8e;"
        "}"
        "QComboBox::drop-down {"
        "    border: none;"
        "    padding-right: 10px;"
        "}"
        );

    listStack = new QStackedWidget;
    upcomingList = new QListWidget;
    completedList = new QListWidget;

    QString listStyle =
        "QListWidget {"
        "    background-color: #eae1cc;"
        "    border-radius: 8px;"
        "    padding: 5px;"
        "}"
        "QListWidget::item {"
        "    color: black;"
        "    padding: 10px;"
        "    border-bottom: 1px solid #555;"
        "    background-color: transparent;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: transparent;"
        "}";

    upcomingList->setStyleSheet(listStyle);
    completedList->setStyleSheet(listStyle);

    upcomingList->setWordWrap(true);
    upcomingList->setTextElideMode(Qt::ElideNone);
    completedList->setWordWrap(true);
    completedList->setTextElideMode(Qt::ElideNone);

    listStack->addWidget(upcomingList);
    listStack->addWidget(completedList);

    // Layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(taskTypeCombo);
    mainLayout->addWidget(listStack);

    // Connections
    connect(addButton, &QPushButton::clicked, this, &TaskPage::addNewTask);
    connect(taskTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TaskPage::switchList);

    setStyleSheet("background-color: #eae1cc;");
}

void TaskPage::addNewTask()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add Task");
    dialog.setStyleSheet("background-color: #eae1cc;");
    dialog.setMinimumWidth(400);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);

    // Task description
    QLabel *descLabel = new QLabel("Task description");
    descLabel->setStyleSheet(
        "QLabel {"
        "    background-color: transparent;"
        "    color: #333333;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        );

    QLineEdit *descEdit = new QLineEdit();
    descEdit->setStyleSheet(
        "QLineEdit {"
        "    color: #333333;"
        "    padding: 8px;"
        "    border: 1px solid #cccccc;"
        "    border-radius: 6px;"
        "    background-color: transparent;"
        "    font-size: 14px;"
        "}"
        "QLineEdit:focus {"
        "    border-bottom: 2px solid #2196F3;"
        "}"
        );
    descEdit->setPlaceholderText("Enter task description");

    // Deadline
    QLabel *deadlineLabel = new QLabel("Deadline");
    deadlineLabel->setStyleSheet(
        "QLabel {"
        "    background-color: transparent;"
        "    color: #333333;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        );

    QHBoxLayout *deadlineLayout = new QHBoxLayout();

    QDateTimeEdit *deadlineEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    deadlineEdit->setCalendarPopup(true);
    deadlineEdit->setStyleSheet(
        "QDateTimeEdit {"
        "    color: #333333;"
        "    padding: 8px;"
        "    border: 1px solid #cccccc;"
        "    border-radius: 6px;"
        "    background-color: transparent;"
        "    font-size: 14px;"
        "}"
        "QDateTimeEdit:focus {"
        "    border: 2px solid #2196F3;"
        "}"
        "QDateTimeEdit::drop-down {"
        "    border: none;"
        "    width: 20px;"
        "}"
        "QCalendarWidget {"
        "    background-color: white;"
        "    color: black;"
        "}"
        "QCalendarWidget QToolButton {"
        "    color: black;"
        "    background-color: transparent;"
        "    margin: 2px;"
        "    border-radius: 4px;"
        "}"
        "QCalendarWidget QMenu {"
        "    background-color: white;"
        "    color: black;"
        "}"
        "QCalendarWidget QSpinBox {"
        "    color: black;"
        "    background-color: white;"
        "    selection-background-color: #2196F3;"
        "}"
        "QCalendarWidget QTableView {"
        "    background-color: white;"
        "    selection-background-color: #2196F3;"
        "    selection-color: white;"
        "}"
        "QCalendarWidget QAbstractItemView:enabled {"
        "    color: black;"
        "    background-color: white;"
        "    selection-background-color: #2196F3;"
        "    selection-color: white;"
        "}"
        "QCalendarWidget QWidget {"
        "    alternate-background-color: #f5f5f5;"
        "}"
        );
    QPushButton *calendarButton = new QPushButton("📅");
    calendarButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: #666666;"
        "    font-size: 16px;"
        "    padding: 4px 8px;"
        "}"
        "QPushButton:hover {"
        "    color: #333333;"
        "}"
        );
    calendarButton->setCursor(Qt::PointingHandCursor);

    deadlineLayout->addWidget(deadlineEdit);
    deadlineLayout->addWidget(calendarButton);
    deadlineLayout->addStretch();


    // Buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    QPushButton *addButton = new QPushButton("Add");
    QPushButton *cancelButton = new QPushButton("Cancel");

    buttonBox->addButton(addButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    addButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 8px 24px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    cancelButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #f44336;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 8px 24px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #d32f2f;"
        "}"
        );

    layout->addWidget(descLabel);
    layout->addWidget(descEdit);
    layout->addSpacing(15);
    layout->addWidget(deadlineLabel);
    layout->addLayout(deadlineLayout);
    layout->addSpacing(20);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted && !descEdit->text().isEmpty()) {
        createTaskItem(descEdit->text(), deadlineEdit->dateTime());
    }
}


void TaskPage::createTaskItem(const QString &text, const QDateTime &deadline)
{
    QListWidgetItem *item = new QListWidgetItem;

    QWidget *itemWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(itemWidget);
    layout->setContentsMargins(10, 5, 10, 5);

    QString taskDetails = QString("%1 (Due: %2)")
                              .arg(text)
                              .arg(deadline.toString("MMM d, yyyy at h:mm AP"));

    QLabel *label = new QLabel(taskDetails);
    label->setWordWrap(true);
    label->setStyleSheet(
        "QLabel {"
        "    color: black;"
        "    font-size: 16px;"
        "    background: transparent;"
        "    padding: 5px;"
        "}"
        );

    QPushButton *completeBtn = new QPushButton("Complete");
    completeBtn->setFixedWidth(100);
    completeBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 5px 10px;"
        "    font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1976D2;"
        "}"
        );

    layout->addWidget(label, 1);
    layout->addWidget(completeBtn);

    item->setSizeHint(itemWidget->sizeHint());

    connect(completeBtn, &QPushButton::clicked, [=]() {
        int row = upcomingList->row(item);
        if (row != -1) {
            upcomingList->takeItem(row);
            QString completedText = QString("%1\nCompleted: %2\nOriginal Due Date: %3")
                                        .arg(text)
                                        .arg(QDateTime::currentDateTime().toString("MMM d, yyyy at h:mm AP"))
                                        .arg(deadline.toString("MMM d, yyyy at h:mm AP"));

            QListWidgetItem *completedItem = new QListWidgetItem;
            QLabel *completedLabel = new QLabel(completedText);
            completedLabel->setWordWrap(true);
            completedLabel->setStyleSheet(
                "QLabel {"
                "    color: black;"
                "    font-size: 16px;"
                "    background: transparent;"
                "    padding: 5px;"
                "}"
                );

            QWidget *completedWidget = new QWidget;
            QHBoxLayout *completedLayout = new QHBoxLayout(completedWidget);
            completedLayout->addWidget(completedLabel);

            completedItem->setSizeHint(completedWidget->sizeHint());
            completedList->addItem(completedItem);
            completedList->setItemWidget(completedItem, completedWidget);

            taskTypeCombo->setCurrentIndex(1);  // Switch to completed tab
        }
    });

    upcomingList->addItem(item);
    upcomingList->setItemWidget(item, itemWidget);
}

void TaskPage::switchList(int index)
{
    listStack->setCurrentIndex(index);
}
