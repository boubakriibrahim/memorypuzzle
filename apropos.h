#ifndef APROPOS_H
#define APROPOS_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QPixmap>

namespace Ui {
class Apropos;
}

class Apropos : public QDialog
{
    Q_OBJECT

public:
    explicit Apropos(QWidget *parent = nullptr);
    ~Apropos();

private:
    Ui::Apropos *ui;
    QPropertyAnimation * animation;
    QPropertyAnimation * animation2;
    QPropertyAnimation * animation3;
    QPropertyAnimation * animation4;
};

#endif // APROPOS_H
