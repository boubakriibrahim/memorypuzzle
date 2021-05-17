#include "apropos.h"
#include "ui_apropos.h"

Apropos::Apropos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Apropos)
{
    ui->setupUi(this);
    setWindowTitle(tr("A propos"));

    //stylesheet
    ui->textBrowser->setStyleSheet("background-color:transparent;");

    QPixmap bkgnd("C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);



    //photos
    QPixmap pix("C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/ibrahim.JPG");
    ui->ibrahim->setPixmap(pix);
    QPixmap pix2("C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/mahmoud.JPG");
    ui->mahmoud->setPixmap(pix2);
    QPixmap pix3("C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/adem.png");
    ui->adem->setPixmap(pix3);


    //animation
    animation = new QPropertyAnimation(ui->textBrowser,"geometry");
    animation->setDuration(15000);
    animation->setStartValue(QRect(180, 800, 1200, 500));
    animation->setEndValue(QRect(180, -600, 1200, 500));
    animation->start();

    animation2 = new QPropertyAnimation(ui->ibrahim,"geometry");
    animation2->setDuration(15000);
    animation2->setStartValue(QRect(250, 1000, 300, 280));
    animation2->setEndValue(QRect(250, -400, 300, 280));
    animation2->start();

    animation3 = new QPropertyAnimation(ui->mahmoud,"geometry");
    animation3->setDuration(15000);
    animation3->setStartValue(QRect(650, 1000, 300, 280));
    animation3->setEndValue(QRect(650, -400, 300, 280));
    animation3->start();

    animation4 = new QPropertyAnimation(ui->adem,"geometry");
    animation4->setDuration(15000);
    animation4->setStartValue(QRect(1050, 1000, 300, 280));
    animation4->setEndValue(QRect(1050, -400, 300, 280));
    animation4->start();
}

Apropos::~Apropos()
{
    delete ui;
}
