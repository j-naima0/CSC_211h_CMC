#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <stdexcept>
#include "basepage.h"

// Exception classes
class LoginException : public std::runtime_error {
public:
    explicit LoginException(const QString& message)
        : std::runtime_error(message.toStdString()) {}
};

class EmptyFieldException : public LoginException {
public:
    EmptyFieldException()
        : LoginException("Please fill in all fields") {}
};

class InvalidCredentialsException : public LoginException {
public:
    InvalidCredentialsException()
        : LoginException("Invalid username or password") {}
};

class PasswordMismatchException : public LoginException {
public:
    PasswordMismatchException()
        : LoginException("Passwords don't match") {}
};

class UserExistsException : public LoginException {
public:
    UserExistsException()
        : LoginException("Username already exists") {}
};

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

#endif
