// moodwidget.cpp
// moodwidget.cpp
#include "moodwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

MoodWidget::MoodWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
}
void MoodWidget::setupUi()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(20);

    struct MoodInfo {
        QString text;
        QString emoji;
        QString color;
    };

    QVector<MoodInfo> moods = {
        {"Great", "😊", "#4CAF50"},  // Green
        {"Good", "😐", "#2196F3"},   // Blue
        {"Okay", "🙂", "#FF9800"},   // Orange
        {"Not Great", "☹️", "#FF5722"}, // Deep Orange
        {"Struggling", "😔", "#F44336"} // Red
    };

    for (const auto &mood : moods) {
        QWidget *moodContainer = new QWidget;
        QVBoxLayout *moodLayout = new QVBoxLayout(moodContainer);

        // Emoji label
        QLabel *emojiLabel = new QLabel(mood.emoji);
        emojiLabel->setAlignment(Qt::AlignCenter);
        emojiLabel->setStyleSheet("font-size: 32px;");

        // Mood button
        QPushButton *btn = new QPushButton(mood.text);
        btn->setStyleSheet(QString(
                               "QPushButton {"
                               "    color: white;"
                               "    border: none;"
                               "    border-radius: 15px;"
                               "    padding: 8px 16px;"
                               "    font-weight: bold;"
                               "    background: %1;"
                               "}"
                               "QPushButton:hover {"
                               "    background: %2;"
                               "}"
                               ).arg(mood.color, mood.color));
        btn->setCheckable(true);

        moodLayout->addWidget(emojiLabel);
        moodLayout->addWidget(btn);

        layout->addWidget(moodContainer);

        connect(btn, &QPushButton::clicked, this, &MoodWidget::moodSelected);
        moodButtons.append(btn);
    }
}


void MoodWidget::moodSelected()
{
    QPushButton *selectedBtn = qobject_cast<QPushButton*>(sender());
    if (!selectedBtn) return;

    currentMood = selectedBtn->text();  // Save the current mood

    for (QPushButton *btn : moodButtons) {
        if (btn != selectedBtn) {
            btn->setChecked(false);
        }
    }

    MoodInfoDialog *dialog = new MoodInfoDialog(currentMood, this);
    connect(dialog, &MoodInfoDialog::journalSaved,
            this, &MoodWidget::onJournalSaved);
    dialog->show();
}

void MoodWidget::onJournalSaved(const QString& mood, const QString& entry)
{
    emit journalSaved(mood, entry);  // Forward the signal
}

void MoodWidget::showMoodInfo(const QString& mood)
{
    MoodInfoDialog *dialog = new MoodInfoDialog(mood, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose); // Auto delete when closed
    dialog->show();
}
