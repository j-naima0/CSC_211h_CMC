#include "loginpage.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QMessageBox>
#include <QFontDatabase>

LoginPage::LoginPage(QWidget *parent) : BasePage(parent)
{
    setupUi();
    userCredentials["test"] = "test";
}

void LoginPage::setupUi()
{
    // Add in constructor
    QFontDatabase::addApplicationFont(":/fonts/Akaya_Kanadaka/AkayaKanadaka-Regular.ttf");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);

    // Create and setup forms
    loginForm = new QWidget;
    registerForm = new QWidget;

    setupLoginForm();
    setupRegisterForm();

    // Add forms to layout
    mainLayout->addWidget(loginForm);
    mainLayout->addWidget(registerForm);

    loginForm->show();
    registerForm->hide();
    currentForm = loginForm;
}

void LoginPage::setupLoginForm()
{
    QVBoxLayout *layout = new QVBoxLayout(loginForm);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Your Companion for a Healthy Mind and College Life!");
    titleLabel->setStyleSheet(
        "QLabel {"
        "    font-family: 'Akaya Kanadaka';"
        "    font-size: 28px;"
        "    color: #003366;"
        "    font-weight: bold;"
        "}"
        );
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel *usernameLabel = new QLabel("Username");
    usernameLabel->setStyleSheet("color: gray; font-family: 'Akaya Kanadaka'; font-size: 18px; font-weight: bold;");
    loginUsernameEdit = new QLineEdit;
    loginUsernameEdit->setStyleSheet(
        "QLineEdit {"
        "    padding: 12px;"
        "    border: none;"
        "    border-bottom: 1px solid #cccccc;"
        "    background-color: white;"
        "    color: #333333;"
        "    font-family: 'Akaya Kanadaka';"
        "    font-size: 20px;"
        "    min-height: 30px;"
        "}"
        );
    QLabel *passwordLabel = new QLabel("Password");
    passwordLabel->setStyleSheet("color: gray; font-family: 'Akaya Kanadaka'; font-size: 18px; font-weight: bold;");
    loginPasswordEdit = new QLineEdit;
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    loginPasswordEdit->setStyleSheet(loginUsernameEdit->styleSheet());

    loginButton = new QPushButton("Login");
    loginButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #e18e8e;"
        "    color: white;"
        "    font-family: 'Akaya Kanadaka';"
        "    border: none;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    showRegisterButton = new QPushButton("Don't have an account? Register");
    showRegisterButton->setStyleSheet(
        "QPushButton {"
        "    background: none;"
        "    border: none;"
        "    color: #2196F3;"
        "    font-family: 'Akaya Kanadaka';"
        "    font-size: 18px;"
        "    text-decoration: underline;"
        "}"
        "QPushButton:hover {"
        "    color: #1976D2;"
        "}"
        );

    loginStatusLabel = new QLabel();
    loginStatusLabel->setStyleSheet("color: red;");
    loginStatusLabel->setAlignment(Qt::AlignCenter);

    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addSpacing(40);
    layout->addWidget(usernameLabel);
    layout->addWidget(loginUsernameEdit);
    layout->addSpacing(10);
    layout->addWidget(passwordLabel);
    layout->addWidget(loginPasswordEdit);
    layout->addSpacing(20);
    layout->addWidget(loginButton);
    layout->addWidget(loginStatusLabel);
    layout->addSpacing(20);
    layout->addWidget(showRegisterButton);
    layout->addStretch();

    connect(loginButton, &QPushButton::clicked, this, &LoginPage::handleLogin);
    connect(showRegisterButton, &QPushButton::clicked, this, &LoginPage::showRegisterForm);
}

void LoginPage::setupRegisterForm()
{
    QVBoxLayout *layout = new QVBoxLayout(registerForm);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Create An Account");
    titleLabel->setStyleSheet(
        "QLabel {"
        "    font-family: 'Akaya Kanadaka';"
        "    font-size: 38px;"
        "    color: #003366;"
        "    font-weight: bold;"
        "}"
        );
    titleLabel->setAlignment(Qt::AlignCenter);
    QLabel *usernameLabel = new QLabel("Username");
    usernameLabel->setStyleSheet("color: gray; font-size: 18px; font-weight: bold;");
    registerUsernameEdit = new QLineEdit;
    registerUsernameEdit->setStyleSheet(
        "QLineEdit {"
        "    padding: 12px;"
        "    border: none;"
        "    border-bottom: 1px solid #cccccc;"
        "    background-color: white;"
        "    color: #333333;"
        "    font-family: 'Akaya Kanadaka';"
        "    font-size: 20px;"
        "    min-height: 30px;"
        "}"
        );
    QLabel *passwordLabel = new QLabel("Password");
    passwordLabel->setStyleSheet("color: gray; font-size: 18px; font-weight: bold;");
    registerPasswordEdit = new QLineEdit;
    registerPasswordEdit->setEchoMode(QLineEdit::Password);
    registerPasswordEdit->setStyleSheet(registerUsernameEdit->styleSheet());

    QLabel *confirmPasswordLabel = new QLabel("Confirm Password");
    confirmPasswordLabel->setStyleSheet("color: gray; font-size: 18px; font-weight: bold;");
    registerConfirmPasswordEdit = new QLineEdit;
    registerConfirmPasswordEdit->setEchoMode(QLineEdit::Password);
    registerConfirmPasswordEdit->setStyleSheet(registerUsernameEdit->styleSheet());

    registerButton = new QPushButton("Register");
    registerButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #e18e8e;"
        "    color: white;"
        "    font-family: 'Akaya Kanadaka';"
        "    border: none;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    showLoginButton = new QPushButton("Already have an account? Login");
    showLoginButton->setStyleSheet(
        "QPushButton {"
        "    background: none;"
        "    border: none;"
        "    color: #2196F3;"
        "    font-family: 'Akaya Kanadaka';"
        "    font-size: 18px;"
        "    text-decoration: underline;"
        "}"
        "QPushButton:hover {"
        "    color: #1976D2;"
        "}"
        );
    registerStatusLabel = new QLabel();
    registerStatusLabel->setStyleSheet("color: red;");
    registerStatusLabel->setAlignment(Qt::AlignCenter);

    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addSpacing(40);
    layout->addWidget(usernameLabel);
    layout->addWidget(registerUsernameEdit);
    layout->addSpacing(10);
    layout->addWidget(passwordLabel);
    layout->addWidget(registerPasswordEdit);
    layout->addSpacing(10);
    layout->addWidget(confirmPasswordLabel);
    layout->addWidget(registerConfirmPasswordEdit);
    layout->addSpacing(20);
    layout->addWidget(registerButton);
    layout->addWidget(registerStatusLabel);
    layout->addSpacing(20);
    layout->addWidget(showLoginButton);
    layout->addStretch();
    connect(registerButton, &QPushButton::clicked, this, &LoginPage::handleRegister);
    connect(showLoginButton, &QPushButton::clicked, this, &LoginPage::showLoginForm);
}

void LoginPage::showLoginForm()
{
    if (currentForm != loginForm) {
        currentForm->hide();
        loginForm->show();
        currentForm = loginForm;
    }
    loginStatusLabel->clear();
    loginUsernameEdit->clear();
    loginPasswordEdit->clear();
}

void LoginPage::showRegisterForm()
{
    if (currentForm != registerForm) {
        currentForm->hide();
        registerForm->show();
        currentForm = registerForm;
    }
    registerStatusLabel->clear();
    registerUsernameEdit->clear();
    registerPasswordEdit->clear();
    registerConfirmPasswordEdit->clear();
}

void LoginPage::handleLogin()
{
    try {
        QString username = loginUsernameEdit->text();
        QString password = loginPasswordEdit->text();

        if (username.isEmpty() || password.isEmpty()) {
            throw EmptyFieldException();
        }

        if (!userCredentials.contains(username) || userCredentials[username] != password) {
            throw InvalidCredentialsException();
        }

        emit loginSuccessful(username);
    }
    catch (const LoginException& e) {
        loginStatusLabel->setText(QString::fromStdString(e.what()));
    }
    catch (const std::exception& e) {
        loginStatusLabel->setText("An unexpected error occurred");
        qDebug() << "Login error:" << e.what();
    }
}

void LoginPage::handleRegister()
{
    try {
        QString username = registerUsernameEdit->text();
        QString password = registerPasswordEdit->text();
        QString confirmPassword = registerConfirmPasswordEdit->text();

        if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
            throw EmptyFieldException();
        }

        if (password != confirmPassword) {
            throw PasswordMismatchException();
        }

        if (userCredentials.contains(username)) {
            throw UserExistsException();
        }

        userCredentials[username] = password;
        QMessageBox::information(this, "Success", "Registration successful! Please login.");
        showLoginForm();
    }
    catch (const LoginException& e) {
        registerStatusLabel->setText(QString::fromStdString(e.what()));
    }
    catch (const std::exception& e) {
        registerStatusLabel->setText("An unexpected error occurred");
        qDebug() << "Registration error:" << e.what();
    }
}
