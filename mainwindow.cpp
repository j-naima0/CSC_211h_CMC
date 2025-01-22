#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    createConnections();
}


void MainWindow::setupUi()
{

    setWindowTitle("College Mental Health Companion");
    // Create central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Create navigation bar
    QWidget *navBar = new QWidget;
    navBar->setStyleSheet("background-color: white; border-bottom: 1px solid #E3E3E3;");
    QHBoxLayout *navLayout = new QHBoxLayout(navBar);
    navLayout->setSpacing(0);
    navLayout->setContentsMargins(0, 0, 0, 0);

    // Create navigation buttons
    homeButton = new CustomButton("HOME");
    scheduleButton = new CustomButton("SCHEDULE");
    taskButton = new CustomButton("TASK");
    navLayout->addWidget(homeButton);
    navLayout->addWidget(scheduleButton);
    navLayout->addWidget(taskButton);

    // Create stacked widget and pages
    stackedWidget = new QStackedWidget;
    loginPage = new LoginPage(this);
    homePage = new HomePage;
    schedulePage = new SchedulePage;
    taskPage = new TaskPage;

    stackedWidget->addWidget(loginPage);  // Add login page first
    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(schedulePage);
    stackedWidget->addWidget(taskPage);

    // Add widgets to main layout
    mainLayout->addWidget(navBar);
    mainLayout->addWidget(stackedWidget);
    setCentralWidget(centralWidget);
    setMinimumSize(800, 600);

    // Set initial state
    stackedWidget->setCurrentWidget(loginPage);
    homeButton->hide();
    scheduleButton->hide();
    taskButton->hide();
}
void MainWindow::showNavigation() {
    homeButton->show();
    scheduleButton->show();
    taskButton->show();
    homeButton->setSelected(true);
}
void MainWindow::createConnections()
{
    connect(loginPage, &LoginPage::loginSuccessful, this, [this](const QString &username) {
        showNavigation();
        stackedWidget->setCurrentWidget(homePage);
        homePage->setUsername(username);
    });
    connect(homeButton, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(scheduleButton, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(taskButton, &QPushButton::clicked, this, &MainWindow::switchPage);
}

void MainWindow::switchPage()
{
    CustomButton* button = qobject_cast<CustomButton*>(sender());
    if (!button) return;

    updateButtonStates(button);

    if (button == homeButton) {
        stackedWidget->setCurrentWidget(homePage);
    } else if (button == scheduleButton) {
        stackedWidget->setCurrentWidget(schedulePage);
    } else if (button == taskButton) {
        stackedWidget->setCurrentWidget(taskPage);
    }
}

void MainWindow::updateButtonStates(CustomButton* selectedButton)
{
    homeButton->setSelected(selectedButton == homeButton);
    scheduleButton->setSelected(selectedButton == scheduleButton);
    taskButton->setSelected(selectedButton == taskButton);
}
