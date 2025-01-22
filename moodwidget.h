#ifndef MOODWIDGET_H
#define MOODWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "moodinfodialog.h"

class MoodWidget : public QWidget {
    Q_OBJECT
public:
    explicit MoodWidget(QWidget *parent = nullptr);

signals:
    void journalSaved(const QString& mood, const QString& entry);  // Add this signal

private slots:
    void moodSelected();
    void onJournalSaved(const QString& mood, const QString& entry); // Add this


private:
    void setupUi();
    QList<QPushButton*> moodButtons;
    QString currentMood;
    void showMoodInfo(const QString& mood);
};

#endif
