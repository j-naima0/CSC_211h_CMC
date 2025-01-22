#include "schedulepage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QFontDatabase>
#include <QApplication>

SchedulePage::SchedulePage(QWidget *parent)
    : BasePage(parent)
{
    setupUi();
}

void SchedulePage::setupUi()
{
    // At the beginning of setupUi()
    QFontDatabase::addApplicationFont(":/fonts/Akaya_Kanadaka/AkayaKanadaka-Regular.ttf");
    QFont customFont("Akaya Kanadaka", 12);
    QApplication::setFont(customFont);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);

    // Title
    QLabel *title = new QLabel("PERSONAL/ACADEMIC COUNSELING");
    title->setStyleSheet("font-style: 'Akaya Kanadaka'; font-size: 28px; color: #003366; font-weight: bold;");
    title->setAlignment(Qt::AlignCenter);


    // Counseling Button
    counselingBtn = new QPushButton("REQUEST AN APPOINTMENT");
    counselingBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #4ca181;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-style: Akaya Kanadaka;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

// Appointment Type Dropdown
appointmentTypeCombo = new QComboBox;
appointmentTypeCombo->addItems({"Upcoming", "Completed"});
appointmentTypeCombo->setStyleSheet(
    "QComboBox {"
    "    background-color: #a1d67f;"
    "    color: white;"
    "    border: none;"
    "    border-radius: 5px;"
    "    padding: 8px 15px;"
    "    font-family: 'Akaya Kanadaka';"
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
    "QComboBox::down-arrow {"
    "    image: url(:/down-arrow.png);"
    "    width: 12px;"
    "    height: 12px;"
    "}"
    "QComboBox QAbstractItemView {"
    "    background-color: gray;"
    "    border: 1px solid #ddd;"
    "    selection-background-color: #2196F3;"
    "    selection-color: black;"
    "    font-family: 'Akaya Kanadaka';"
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

// Make the lists handle word wrapping better
upcomingList->setWordWrap(true);
upcomingList->setTextElideMode(Qt::ElideNone);
completedList->setWordWrap(true);
completedList->setTextElideMode(Qt::ElideNone);

listStack->addWidget(upcomingList);
listStack->addWidget(completedList);

    // Layout
    mainLayout->addWidget(title);
    //mainLayout->addWidget(calendar);
    mainLayout->addWidget(counselingBtn);
    mainLayout->addWidget(appointmentTypeCombo);
    mainLayout->addWidget(listStack);

    // Connections
    connect(counselingBtn, &QPushButton::clicked, this, &SchedulePage::showCounselingRequest);
    connect(appointmentTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SchedulePage::switchList);

    setStyleSheet("background-color: #eae1cc;");
}


void SchedulePage::addUpcomingAppointment(const QString &details)
{
    QListWidgetItem *item = new QListWidgetItem;

    // Create a single widget for the item
    QWidget *itemWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(itemWidget);
    layout->setContentsMargins(10, 5, 10, 5);

    // Create label with better text formatting
    QLabel *label = new QLabel(details);
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
    completeBtn->setFixedWidth(100);  // Fixed width for consistency
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

    // Add widgets to layout
    layout->addWidget(label, 1);  // Give label stretch factor
    layout->addWidget(completeBtn);

    // Set item properties
    item->setSizeHint(itemWidget->sizeHint());

    // Style the list widget
    upcomingList->setStyleSheet(
        "QListWidget {"
        "    background-color: transparent;"
        "    border-radius: 8px;"
        "}"
        "QListWidget::item {"
        "    background-color: black;"
        "    border-radius: 4px;"
        "    margin: 5px 10px;"
        "    min-height: 40px;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #484848;"
        "}"
        );

    // Connect complete button
    connect(completeBtn, &QPushButton::clicked, [=]() {
        int row = upcomingList->row(item);
        if (row != -1) {
            upcomingList->takeItem(row);
            QString completedText = details + " - (Completed)";
            QListWidgetItem *completedItem = new QListWidgetItem(completedText);
            completedItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            completedList->addItem(completedItem);
        }
    });

    upcomingList->addItem(item);
    upcomingList->setItemWidget(item, itemWidget);
}
void SchedulePage::showCounselingRequest()
{
    CounselingDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString appointmentDetails = QString("%1 (%2)")
        .arg(dialog.getAppointmentDetails())
            .arg(QDateTime::currentDateTime().toString("MMM d, yyyy at h:mm AP"));

        addUpcomingAppointment(appointmentDetails);

        // Switch to upcoming view
        appointmentTypeCombo->setCurrentIndex(0);
    }
}

void SchedulePage::switchList(int index)
{
    listStack->setCurrentIndex(index);
}
