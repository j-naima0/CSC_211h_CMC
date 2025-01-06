#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QWidget>

class BasePage : public QWidget {
    Q_OBJECT
public:
    explicit BasePage(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void setupBackground();
};

#endif // BASEPAGE_H
