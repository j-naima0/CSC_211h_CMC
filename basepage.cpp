#include "basepage.h"
#include <QPalette>
#include <QResizeEvent>

BasePage::BasePage(QWidget *parent) : QWidget(parent)
{
    setupBackground();
}

void BasePage::setupBackground()
{
    // Load and set background image
    QPixmap backgroundImage(":/images/4.png");
    if (!backgroundImage.isNull()) {
        QPalette palette;
        backgroundImage = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Window, backgroundImage);
        this->setAutoFillBackground(true);
        this->setPalette(palette);
    }
}
void BasePage::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    setupBackground();
}
