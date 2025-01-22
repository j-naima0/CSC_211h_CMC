#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "moodwidget.h"
#include "journalviewer.h"  // Add this include

class HomePage : public QWidget {
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = nullptr);

public slots:
    void setUsername(const QString &username);
private:
    void setupUi();
    QString m_username;
    QLabel *greetingLabel;
    MoodWidget *moodWidget;
    JournalViewer *journalViewer;
    QPushButton *counselingBtn;
    QPushButton *appointmentBtn;
    QPushButton *viewJournalsBtn;
    QVBoxLayout *mainLayout;  // Add this

    // Add this to your homepage.h file in the private section:
protected:
    void resizeEvent(QResizeEvent* event) override {
        QWidget::resizeEvent(event);

        // Update background image scaling when window is resized
        QPixmap backgroundImage(":/HOME.jpg");
        if (!backgroundImage.isNull()) {
            QPalette palette;
            backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            palette.setBrush(QPalette::Window, backgroundImage);
            this->setPalette(palette);
        }
    }
};

#endif // HOMEPAGE_H
