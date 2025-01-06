#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "custombutton.h"
#include "homepage.h"
#include "journalviewer.h"
#include "schedulepage.h"
#include "taskpage.h"
#include "loginpage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void switchPage();
    void showNavigation();

private:
    void setupUi();
    void createConnections();
    void updateButtonStates(CustomButton* selectedButton);

    LoginPage *loginPage;
    QStackedWidget *stackedWidget;
    CustomButton *homeButton;
    CustomButton *scheduleButton;
    CustomButton *taskButton;
    HomePage *homePage;
    SchedulePage *schedulePage;
    TaskPage *taskPage;
};

#endif // MAINWINDOW_H
