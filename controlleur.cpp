#include "controlleur.h"
#include "ui_controlleur.h"
#include <QMediaPlayer>

Controlleur::Controlleur(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Controlleur)
{
    ui->setupUi(this);
    setWindowTitle(tr("Memory Puzzle"));

    //stylesheet
    QPixmap bkgnd("C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);


    ui->textBrowser->setStyleSheet("background-color:transparent;");
    //ui->graphicsView->setStyleSheet("background-image:url(\"C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/logonew.png\");width: 100px; background-repeat: no-repeat;");
    QPixmap pix("C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/logo.png");

    // get label dimensions
    int w = ui->logo->width();
    int h = ui->logo->height();

    // set a scaled pixmap to a w x h window keeping its aspect ratio
    ui->logo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


    //music
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/music.mp3"));
    music->play();
    music->setVolume(20);
    parametre = new Parametre(this,music);
}

Controlleur::~Controlleur()
{
    delete ui;
}



void Controlleur::on_pushButton1_clicked()
{
    //hide();
    QString joueur1 = ui->joueur1->toPlainText();
    QString joueur2 = ui->joueur2->toPlainText();
    jeu = new Jeu(parametre->mode,parametre->difficultee,parametre->theme,joueur1,joueur2);
    jeu->show();

}
void Controlleur::on_pushButton3_clicked()
{
    //hide();
    apropos = new Apropos(this);
    apropos->show();
}

void Controlleur::on_pushButton2_clicked()
{
    parametre->show();
}
