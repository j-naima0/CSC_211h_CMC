#include "counselingdialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCalendarWidget>
#include <QLabel>

CounselingDialog::CounselingDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Counseling Request");
    setModal(true);
    setMinimumWidth(400);
    setupUi();
}

void CounselingDialog::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;

    // Set form layout properties
    formLayout->setSpacing(10);
    formLayout->setLabelAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    formLayout->setFormAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    // Common styles
    QString formStyle =
        "QLabel {"
        "    color: black;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    background-color: transparent;"
        "}"
        "QLineEdit, QTextEdit, QComboBox {"
        "    background-color: white;"
        "    border: 1px solid #ddd;"
        "    border-radius: 5px;"
        "    padding: 8px;"
        "    min-height: 20px;"
        "    color: #333333;"
        "    font-size: 14px;"
        "}"
        "QComboBox::drop-down {"
        "    border: none;"
        "}";

    setStyleSheet(formStyle);

    // Create form fields
    nameEdit = new QLineEdit;
    nameEdit->setPlaceholderText("Enter your full name");

    idEdit = new QLineEdit;
    idEdit->setPlaceholderText("Enter your student ID");

    emailEdit = new QLineEdit;
    emailEdit->setPlaceholderText("Enter your email address");


        // Style for the date/time editor and calendar
        QString dateTimeStyle =
            "QDateTimeEdit {"
            "    background-color: white;"
            "    border: 1px solid #ddd;"
            "    border-radius: 5px;"
            "    padding: 8px;"
            "    color: black;"
            "    font-size: 14px;"
            "}"
            "QCalendarWidget {"
            "    background-color: white;"
            "}"
            "QCalendarWidget QToolButton {"
            "    color: black;"
            "    background-color: white;"
            "    border: none;"
            "    border-radius: 4px;"
            "    padding: 4px;"
            "}"
            "QCalendarWidget QMenu {"
            "    background-color: white;"
            "    color: black;"
            "    border: 1px solid #ddd;"
            "}"
            "QCalendarWidget QSpinBox {"
            "    background-color: white;"
            "    color: black;"
            "    border: 1px solid #ddd;"
            "}"
            "QCalendarWidget QTableView {"
            "    background-color: white;"
            "    selection-background-color: #2196F3;"
            "    selection-color: white;"
            "}"
            "QCalendarWidget QTableView:enabled {"
            "    color: black;"
            "}"
            "QCalendarWidget QTableView:disabled {"
            "    color: #999999;"
            "}";

        dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
        dateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
        dateTimeEdit->setCalendarPopup(true);
        dateTimeEdit->setStyleSheet(dateTimeStyle);
        dateTimeEdit->calendarWidget()->setStyleSheet(dateTimeStyle);  // Apply style to popup calendar



    typeCombo = new QComboBox;
    typeCombo->addItems({"Personal Counseling", "Academic Counseling", "Career Counseling"});

    reasonEdit = new QTextEdit;
    reasonEdit->setPlaceholderText("Please describe your reason for seeking counseling...");
    reasonEdit->setMinimumHeight(100);

    submitButton = new QPushButton("Submit Request");
    submitButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 10px 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    // Add fields to form
    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Student ID:", idEdit);
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Preferred Date/Time:", dateTimeEdit);
    formLayout->addRow("Type:", typeCombo);
    formLayout->addRow("Reason:", reasonEdit);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &CounselingDialog::submitRequest);
}

void CounselingDialog::submitRequest()
{
    if (nameEdit->text().isEmpty() || idEdit->text().isEmpty() ||
        emailEdit->text().isEmpty() || reasonEdit->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Incomplete Form", "Please fill in all fields.");
        return;
    }

    QString appointmentDetails = QString("Name: %1\nID: %2\nDate/Time: %3\nType: %4")
                                     .arg(nameEdit->text())
                                     .arg(idEdit->text())
                                     .arg(dateTimeEdit->dateTime().toString("MMM d, yyyy at h:mm AP"))
                                     .arg(typeCombo->currentText());


    QMessageBox::information(this, "Success",
                             "Your counseling request has been submitted.\nWe will contact you shortly at " + emailEdit->text());
    accept();
}
