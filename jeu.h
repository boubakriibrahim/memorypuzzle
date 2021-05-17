#ifndef JEU_H
#define JEU_H

#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QTime>
#include <QWidget>
#include <QLabel>
#include <vector>

class Case : public QWidget {

    Q_OBJECT

public:
    enum Apparence {
        MASQUEE,
        ELIMINEE,
        AFFICHEE,
        BONUS
    };

private:
    int x, y;
    int idCase;
    Apparence modeCase;
    QPushButton *buttonCase;
    QString theme="objets";

public:
    Case(int i, int j, int n,QString);
    ~Case();
    int getId() { return idCase; }
    Apparence getMode() { return modeCase; }
    void setMode(Apparence e);

public slots:
    void clicked();

signals:
    void selected(int i, int j, int n);

};

class Joueur {
private:
    QString nom="Joueur";
    unsigned score=0;
    int nbCaseOuvertSuite=0;

public:
    Joueur();
    Joueur(QString);
    ~Joueur();
    unsigned getScore();
    void setScore(unsigned);
    QString getNom();
    void setNom(QString);
    int getNbCaseOuvert();
    void setNbCaseOuvert(int);
};



class Grille : public QWidget {

    Q_OBJECT


private:
    int nbCases;
    int selectX, selectY;
    int selectN;
    QTimer * compteur;
    QTimer *tempsCacher;
    QTimer *tempsEliminer;
    QLabel * textCompteur;
    int s=0;
    int m=0;
    int tempsChallenge=0;
    int s2,m2;
    QString tempsLimite = "00:00";

    QLabel * textNomJoueur1;
    QLabel * textNomJoueur2;
    QLabel * textTour;

    Joueur * premierJoueur;
    Joueur * deuxiemeJoueur = NULL;
    QString tour="joueur1";


public:
    std::vector<std::pair<int,int>> randomBonus;
    std::vector<std::vector<int> > matrix;
    std::vector<int> elementsRestants;


    Grille(int,QString,QString,int,QString,QString);
    ~Grille();
    void gameOver(int,int);
    void afficherBonus();

public slots:
    void caseSelected(int x, int y, int n);
    void cacherCases();
    void eliminerCases();
    void compteurTemps();
    void compteurTempsChallenge();

signals:
    void gameWon(int,QTimer *,Joueur*,Joueur*);
    void gameLose(QTimer *,Joueur*,Joueur*);
    void gameClose(QTimer*);

};

class Jeu : public QMainWindow {

    Q_OBJECT

private:
    int tailleGrille = 3;
    QString mode = "histoire";
    QString theme = "objets";
    int tempsChallenge = 9;

public:
    Jeu(QString,int,QString,QString,QString);
    ~Jeu();

public slots:
    void newGame(QString,QString,QString,QString);
    void gameWon(int,QTimer *,Joueur*,Joueur*);
    void gameLose(QTimer *,Joueur*,Joueur*);
    void gameClose(QTimer *);
};

#endif
