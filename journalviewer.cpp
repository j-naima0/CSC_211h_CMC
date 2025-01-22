// journalviewer.cpp
#include "journalviewer.h"
#include <QMessageBox>

JournalViewer::JournalViewer(QWidget *parent) : QDialog(parent)
{
    setupUi();
}

void JournalViewer::setupUi()
{
    setWindowTitle("Your Journal Entries");
    setMinimumSize(500, 400);

    // Set the background color for the dialog
    this->setStyleSheet(
        "QDialog {"
        "    background-image: url(':/images/4.png');"  // Replace with your image path
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    background-size: cover;"  // Scales the image to cover the dialog
        "}"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Title
    QLabel *titleLabel = new QLabel("Your Journal History");
    titleLabel->setStyleSheet(
        "font-family: 'Akaya Kanadaka';"
        "font-size: 30px;"
        "color: #003366;"
        "background-color: white;"
        );
    titleLabel->setAlignment(Qt::AlignCenter);

    // Journal List
    journalList = new QListWidget;
    journalList->setStyleSheet(
        "QListWidget {"
        "    background-color: #eae1cc;"
        "    border-radius: 8px;"
        "    padding: 5px;"
        "}"
        "QListWidget::item {"
        "    color: black;"
        "    padding: 10px;"
        "    border-bottom: 1px solid #555;"
        "    background-color: #eae1cc;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #d8d2c2;"
        "}"
        );

    // Clear Button
    clearButton = new QPushButton("Clear All Entries");
    clearButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #e18e8e;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #d32f2f;"
        "}"
        );

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(journalList);
    mainLayout->addWidget(clearButton);

    connect(clearButton, &QPushButton::clicked, this, &JournalViewer::clearJournals);
    connect(journalList, &QListWidget::itemDoubleClicked, this, &JournalViewer::viewJournalDetail);
}

void JournalViewer::addJournalEntry(const QString& mood, const QString& entry)
{
    QString dateTime = QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm AP");
    QString displayText = QString("[%1] Mood: %2\n%3").arg(dateTime, mood, entry);

    QListWidgetItem *item = new QListWidgetItem(displayText);
    item->setData(Qt::UserRole, entry);
    journalList->insertItem(0, item);  // Add at top of list
}
void JournalViewer::clearJournals()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Clear Journals",
                                  "Are you sure you want to clear all journal entries?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        journalList->clear();
    }
}

void JournalViewer::viewJournalDetail(QListWidgetItem *item)
{
    QString entry = item->data(Qt::UserRole).toString();
    QMessageBox::information(this, "Journal Entry", entry);
}
