// custombutton.h
#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>

class CustomButton : public QPushButton {
    Q_OBJECT
public:
    explicit CustomButton(const QString &text, QWidget *parent = nullptr);
    void setSelected(bool selected);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool isSelected = false;
};

#endif // CUSTOMBUTTON_H
