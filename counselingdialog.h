// counselingdialog.h
#ifndef COUNSELINGDIALOG_H
#define COUNSELINGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateTimeEdit>

class CounselingDialog : public QDialog {
    Q_OBJECT
public:
    explicit CounselingDialog(QWidget *parent = nullptr);
    QString getAppointmentDetails() const {
        return QString("%1 - %2")
        .arg(nameEdit->text())
            .arg(typeCombo->currentText());
    }

private slots:
    void submitRequest();

private:
    void setupUi();

    QLineEdit *nameEdit;
    QLineEdit *idEdit;
    QLineEdit *emailEdit;
    QDateTimeEdit *dateTimeEdit;
    QTextEdit *reasonEdit;
    QComboBox *typeCombo;
    QPushButton *submitButton;
};

/*class AppointmentDialog : public QDialog {
    Q_OBJECT
public:
    explicit AppointmentDialog(QWidget *parent = nullptr);

private slots:
    void submitAppointment();

private:
    void setupUi();

    QLineEdit *nameEdit;
    QLineEdit *idEdit;
    QLineEdit *emailEdit;
    QDateTimeEdit *dateTimeEdit;
    QTextEdit *notesEdit;
    QPushButton *submitButton;
};
*/
#endif // COUNSELINGDIALOG_H
