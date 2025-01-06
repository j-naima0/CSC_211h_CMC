// journalviewer.h
#ifndef JOURNALVIEWER_H
#define JOURNALVIEWER_H

#include <QDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>

class JournalViewer : public QDialog {
    Q_OBJECT

public:
    explicit JournalViewer(QWidget *parent = nullptr);
    void addJournalEntry(const QString& mood, const QString& entry);

private:
    void setupUi();
    QListWidget *journalList;
    QPushButton *clearButton;

private slots:
    void clearJournals();
    void viewJournalDetail(QListWidgetItem *item);
};

#endif // JOURNALVIEWER_H
