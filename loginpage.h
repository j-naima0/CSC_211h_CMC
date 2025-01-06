#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include "basepage.h"

class LoginPage : public BasePage
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);

signals:
    void loginSuccessful(const QString &username);

private slots:
    void showLoginForm();
    void showRegisterForm();
    void handleLogin();
    void handleRegister();

private:
    void setupUi();
    void setupLoginForm();
    void setupRegisterForm();
    void switchToForm(QWidget* form);

    QWidget *loginForm;
    QWidget *registerForm;
    QWidget *currentForm;

    QLineEdit *loginUsernameEdit;
    QLineEdit *loginPasswordEdit;
    QPushButton *loginButton;
    QPushButton *showRegisterButton;
    QLabel *loginStatusLabel;

    QLineEdit *registerUsernameEdit;
    QLineEdit *registerPasswordEdit;
    QLineEdit *registerConfirmPasswordEdit;
    QPushButton *registerButton;
    QPushButton *showLoginButton;
    QLabel *registerStatusLabel;

    QMap<QString, QString> userCredentials;
};

#endif // LOGINPAGE_H
