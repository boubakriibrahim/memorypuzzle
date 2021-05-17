#include "parametre.h"
#include "ui_parametre.h"
#include "controlleur.h"

Parametre::Parametre(QWidget *parent, QMediaPlayer * m) :
    QDialog(parent), music(m),
    ui(new Ui::Parametre)
{
    ui->setupUi(this);
    setWindowTitle(tr("Paramètres"));

    //stylesheet
    QPixmap bkgnd("C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);

    ui->textBrowser->setStyleSheet("background-color:transparent;");
    ui->textBrowser_2->setStyleSheet("background-color:transparent;");
    ui->pushButton1->setStyleSheet("background-image:url(\"\");");
    ui->pushButton2->setStyleSheet("background-image:url(\"\");");
    ui->groupBox->setStyleSheet("background-image:url(\"\");");
}

Parametre::~Parametre()
{
    delete ui;
}

void Parametre::on_radioButton_clicked()
{
    modeSelect = "histoire";
}

void Parametre::on_radioButton_2_clicked()
{
    modeSelect = "challenge";
}

void Parametre::on_radioButton_3_clicked()
{
    modeSelect = "multijoueur";
}

void Parametre::on_pushButton1_clicked()
{
    if (modeSelect != "")
        mode = modeSelect;
    if (diffSelect != 0)
        difficultee = diffSelect;
    if (themeSelect != "")
        theme = themeSelect;
}


void Parametre::on_radioButton_5_clicked()
{
    //niveau 1
    diffSelect = 1;
}

void Parametre::on_radioButton_6_clicked()
{
    //niveau 2
    diffSelect = 2;
}

void Parametre::on_radioButton_7_clicked()
{
    //niveau 3
    diffSelect = 3;
}

void Parametre::on_radioButton_9_clicked()
{
    //niveau 4
    diffSelect = 4;
}

void Parametre::on_radioButton_10_clicked()
{
    //niveau 5
    diffSelect = 5;
}

void Parametre::on_radioButton_8_clicked()
{
    //niveau 6
    diffSelect = 6;
}


void Parametre::on_radioButton_4_clicked()
{
    //theme objets
    themeSelect = "objets";
}

void Parametre::on_radioButton_11_clicked()
{
    //theme flags
    themeSelect = "flags";
}

void Parametre::on_volume_valueChanged(int value)
{
    music->setVolume(value);
}
