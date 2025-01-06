#include "custombutton.h"
#include <QPainter>
#include <QColor>
#include <QStyle>

CustomButton::CustomButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setFlat(true);
    setMinimumHeight(50);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet(
        "QPushButton {"
        "    color: #2B98B1;"  // Teal color
        "    font-size: 20px;"
        "    font-weight: bold;"
        "    background-color: #eae1cc;"
        "    border: none;"
        "    border-radius: 25px;"  // More rounded corners
        "    padding: 10px 30px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #F0F0F0;"
        "}"
        "QPushButton[selected=true] {"
        "    background-color: #E6E6E6;"
        "}"
        );
}

void CustomButton::setSelected(bool selected)
{
    isSelected = selected;
    setProperty("selected", selected);
    if (QStyle *s = this->style()) {  // Use this->style() and check if it's valid
        s->unpolish(this);
        s->polish(this);
    }
    update();  // Force a repaint
}

void CustomButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event); // Call base class implementation
}
