#include "homepage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

HomePage::HomePage(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void HomePage::setupUi()
{
    // Load and set background image
    QPixmap backgroundImage(":/images/4.png");
    if (!backgroundImage.isNull()) {
        QPalette palette;
        backgroundImage = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Window, backgroundImage);
        this->setAutoFillBackground(true);
        this->setPalette(palette);
    }

    // Create main layout without the overlay
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);

    // Create greeting label first
    greetingLabel = new QLabel("");
    greetingLabel->setStyleSheet(
        "font-size: 40px;"
        "font-weight: bold;"
        "color: #003366;"
        );


    moodWidget = new MoodWidget;
    journalViewer = new JournalViewer(this);

    viewJournalsBtn = new QPushButton("View Your Journals");
    viewJournalsBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #e18e8e;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-family: 'Akaya Kanadaka';"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1976D2;"
        "}"
        );

    // Connections
    connect(moodWidget, &MoodWidget::journalSaved,
            journalViewer, &JournalViewer::addJournalEntry);
    connect(viewJournalsBtn, &QPushButton::clicked, [this]() {
        journalViewer->show();
    });

    // Add widgets to layout
    mainLayout->addWidget(greetingLabel);
    mainLayout->addWidget(moodWidget);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(viewJournalsBtn);
    mainLayout->addStretch();
}
void HomePage::setUsername(const QString &username)
{
    m_username = username;
    greetingLabel->setText("Hi " + username + ", How are you feeling today?");
}
