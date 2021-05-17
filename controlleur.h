#ifndef CONTROLLEUR_H
#define CONTROLLEUR_H

#include <QMainWindow>
#include <apropos.h>
#include "jeu.h"
#include "parametre.h"
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class Controlleur; }
QT_END_NAMESPACE

class Controlleur : public QMainWindow
{
    Q_OBJECT

public:
    QString mode = "easy";
    Controlleur(QWidget *parent = nullptr);
    ~Controlleur();
private slots:

    void on_pushButton1_clicked();
    void on_pushButton3_clicked();
    void on_pushButton2_clicked();

private:
    Ui::Controlleur *ui;
    Apropos * apropos;
    Jeu * jeu;
    Parametre * parametre;
};
#endif // CONTROLLEUR_H
