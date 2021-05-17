#include "jeu.h"

#include <QApplication>
#include <QAction>
#include <QActionGroup>
#include <QDialog>
#include <QGridLayout>
#include <QLocale>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <vector>
#include <time.h>
#include <bits/stdc++.h>

#include <QDebug>

Jeu::Jeu(QString mode2,int diff,QString theme2,QString joueur1,QString joueur2)
  : mode(mode2),theme(theme2)
{
    setWindowTitle(tr("Jeu"));


    //selection niveau
    if (diff == 1){
        tailleGrille = 3;
        tempsChallenge = 9;
    }
    if (diff == 2){
        tailleGrille = 4;
        tempsChallenge = 20;
    }
    if (diff == 3){
        tailleGrille = 5;
        tempsChallenge = 40;
    }
    if (diff == 4){
        tailleGrille = 6;
        tempsChallenge = 78;
    }
    if (diff == 5){
        tailleGrille = 7;
        tempsChallenge = 112;
    }
    if (diff == 6){
        tailleGrille = 8;
        tempsChallenge = 152;
    }


    if (mode2 == "histoire"){
        newGame(theme,mode2,joueur1,"");
    }
    else if (mode2 == "challenge"){
        newGame(theme,mode2,joueur1,"");
    }
    else if (mode2 == "multijoueur"){
        newGame(theme,mode2,joueur1,joueur2);
    }

    //set backround
    QPixmap bkgnd("C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);
    show();
}

Jeu::~Jeu(){
}

void Jeu::newGame(QString theme2, QString mode2,QString joueur1,QString joueur2)
{
    Grille *game = new Grille(tailleGrille,theme2,mode2,tempsChallenge,joueur1,joueur2);
    connect(game, SIGNAL(gameWon(int,QTimer*,Joueur*,Joueur*)), this, SLOT(gameWon(int,QTimer*,Joueur*,Joueur*)));
    connect(game, SIGNAL(gameLose(QTimer*,Joueur*,Joueur*)), this, SLOT(gameLose(QTimer*,Joueur*,Joueur*)));
    connect(game, SIGNAL(gameClose(QTimer*)), this, SLOT(gameClose(QTimer*)));
    setCentralWidget(game);
    resize(350 + 90 * tailleGrille, 250 + 160 * (tailleGrille-1));
}


void Jeu::gameWon(int time,QTimer * temps,Joueur * premierJoueur,Joueur * deuxiemeJoueur)
{
    temps->stop();


        QMessageBox msgBox;
        if (premierJoueur != NULL && deuxiemeJoueur != NULL){
            unsigned score1 = premierJoueur->getScore();
            unsigned score2 = deuxiemeJoueur->getScore();
            qDebug() << score1 << score2;


        if (premierJoueur->getScore() == deuxiemeJoueur ->getScore()){
            msgBox.setWindowTitle("Egalité");
            msgBox.setText(premierJoueur->getNom()+" : "+QString::number(premierJoueur->getScore())+"\n"
                            +deuxiemeJoueur->getNom()+" : "+QString::number(deuxiemeJoueur->getScore())
                                +"\nVous êtes les deux gagnants.");
        }
        else if (premierJoueur->getScore() > deuxiemeJoueur ->getScore()){
            msgBox.setWindowTitle("Gagnant");
            msgBox.setText(premierJoueur->getNom()+" : "+QString::number(premierJoueur->getScore())+"\n"
                            +deuxiemeJoueur->getNom()+" : "+QString::number(deuxiemeJoueur->getScore())
                                +"\n"+premierJoueur->getNom()+" à gagnée la partie.");
        }
        else{
            msgBox.setWindowTitle("Gagnant");
            msgBox.setText(deuxiemeJoueur->getNom()+" : "+QString::number(deuxiemeJoueur->getScore())+"\n"
                           +premierJoueur->getNom()+" : "+QString::number(premierJoueur->getScore())+"\n"
                                +"\n"+deuxiemeJoueur->getNom()+" à gagnée la partie.");
        }
        msgBox.setInformativeText("Souhaitez-vous redémarrer le jeu?");
        msgBox.setStyleSheet("font-size: 50px;");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        QAbstractButton * buttonOui = msgBox.button(QMessageBox::Yes);
        buttonOui->setText("Oui");
        QAbstractButton * buttonNon = msgBox.button(QMessageBox::No);
        buttonNon->setText("Non");
        msgBox.exec();
        if (msgBox.clickedButton()==buttonOui){
            newGame(theme,mode,premierJoueur->getNom(),deuxiemeJoueur->getNom());
        }
        if (msgBox.clickedButton()==buttonNon)
            close();
        return;
        }



        QMessageBox::information(this, tr("Victoire"),
            tr("Vous avez gagné la partie en %1 seconds.").arg(time));

}


void Jeu::gameClose(QTimer * temps)
{
    temps->stop();

}


void Jeu::gameLose(QTimer * temps,Joueur* premierJoueur,Joueur* deuxiemeJoueur)
{
    temps->stop();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over");
    msgBox.setText("Vous avez perdu la partie.");
    msgBox.setInformativeText("Souhaitez-vous redémarrer le jeu?");
    msgBox.setStyleSheet("font-size: 50px;");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    QAbstractButton * buttonOui = msgBox.button(QMessageBox::Yes);
    buttonOui->setText("Oui");
    QAbstractButton * buttonNon = msgBox.button(QMessageBox::No);
    buttonNon->setText("Non");
    msgBox.exec();
    if (msgBox.clickedButton()==buttonOui){
        if (mode == "histoire"){
            newGame(theme,mode,premierJoueur->getNom(),"");
        }
        else if (mode == "challenge"){
            newGame(theme,mode,premierJoueur->getNom(),"");
        }
        else if (mode == "multijoueur"){
            newGame(theme,mode,premierJoueur->getNom(),deuxiemeJoueur->getNom());
        }
    }
    if (msgBox.clickedButton()==buttonNon)
        close();

}


Grille::Grille(int size,QString theme,QString mode, int tempsCha,QString j1,QString j2)
  : nbCases(size), selectX(-1), selectY(0), tempsChallenge(tempsCha)
{

    qDebug() << mode;

    premierJoueur = new Joueur();
    premierJoueur->setNom(j1);
    premierJoueur->setScore(0);
    if (j2 != ""){
        deuxiemeJoueur = new Joueur();
        deuxiemeJoueur->setNom(j2);
        deuxiemeJoueur->setScore(0);
    }

    QGridLayout *layout = new QGridLayout;
    setLayout(layout);
    int n;

    //allocation memoire matrice des cartes
    matrix.resize(8);
    for (int i=0;i<8 ;i++ ) {
        matrix[i].resize(9);
    }

    for(n = 0; n < size*(size-1); n++)
    {
        // choisir position aléatoires des cartes
        int r = (int)( ((double)rand()) / RAND_MAX * (size*(size-1)-n) );

        // Chercher la r-ième case vide
        int p = 0;

        while(r >= 0)
        {
            if(layout->itemAtPosition(p/size, p%size) == NULL)
            {
                r--;
                if(r < 0)
                {
                    matrix[p/size][p%size] = n/2;
                    Case *c = new Case(p/size, p%size, n/2,theme);
                    connect(c, SIGNAL(selected(int,int,int)),
                        this, SLOT(caseSelected(int,int,int)));
                    layout->addWidget(c, p/size, p%size);

                }
            }
            p++;
        }

    }


    //Bonus
    int nbCartes = (nbCases*(nbCases-1))/2;
    for (int num=0;num<nbCartes ; num++ ) {
        elementsRestants.push_back(num);
    }

    //temps de cacher chaque case
    tempsCacher = new QTimer;
    tempsCacher->setSingleShot(true);
    connect(tempsCacher, SIGNAL(timeout()), this, SLOT(cacherCases()));


    //temps d'eliminer chaque case
    tempsEliminer = new QTimer;
    tempsEliminer->setSingleShot(true);
    connect(tempsEliminer, SIGNAL(timeout()), this, SLOT(eliminerCases()));


    //début compteur
    compteur = new QTimer;


    textCompteur = new QLabel();
    textNomJoueur1 = new QLabel();

    if (mode == "histoire"){
        connect(compteur, SIGNAL(timeout()), this, SLOT(compteurTemps()));
        //text compteur
        textCompteur->setText("00:00");


        //text joueur
        textNomJoueur1->setText(premierJoueur->getNom()+"\nScore: "+QString::number(premierJoueur->getScore()));
        textNomJoueur1->setStyleSheet("font-size: 40px;font-family  : Showcard Gothic;color : white;");
        layout->addWidget(textNomJoueur1,1,10);
    }
    else if (mode == "challenge"){
        connect(compteur, SIGNAL(timeout()), this, SLOT(compteurTempsChallenge()));
        s2 = tempsChallenge % 60;
        m2 = tempsChallenge / 60;

        if (m2==0){
            if (s2<10)
               tempsLimite = "00:0"+QString::number(s2);
            else
               tempsLimite = "00:"+QString::number(s2);
        }
        else
            if (m2<10){
                if (s2<10)
                   tempsLimite = "0"+QString::number(m2)+":0"+QString::number(s2);
                else
                   tempsLimite = "0"+QString::number(m2)+":"+QString::number(s2);
            }

        else
            {
                if (s2<10)
                   tempsLimite = QString::number(m2)+":0"+QString::number(s2);
                else
                   tempsLimite = QString::number(m2)+":"+QString::number(s2);
            }


        textCompteur->setText("00:00\n-------\n"+tempsLimite);


        //text joueur
        textNomJoueur1->setText(premierJoueur->getNom()+"\nScore: "+QString::number(premierJoueur->getScore()));
        textNomJoueur1->setStyleSheet("font-size: 40px;font-family  : Showcard Gothic;color : white;");
        layout->addWidget(textNomJoueur1,1,10);
    }
    else if (mode == "multijoueur"){

        // ajouter temps de chaque tour
        connect(compteur, SIGNAL(timeout()), this, SLOT(compteurTemps()));
        //text compteur
        textCompteur->setText("00:00");



        textNomJoueur2 = new QLabel();

        //text joueur1
        textNomJoueur1->setText(premierJoueur->getNom()+"\nScore: "+QString::number(premierJoueur->getScore()));
        textNomJoueur1->setStyleSheet("font-size: 40px;font-family  : Showcard Gothic;");
        layout->addWidget(textNomJoueur1,0,10);

        //text joueur2
        if (deuxiemeJoueur!= NULL){
        textNomJoueur2->setText(deuxiemeJoueur->getNom()+"\nScore: "+QString::number(deuxiemeJoueur->getScore()));
        textNomJoueur2->setStyleSheet("font-size: 40px;font-family  : Showcard Gothic;");
        layout->addWidget(textNomJoueur2,1,10);
        }

        textTour = new QLabel();
        textTour->setText("Tour de :\n"+premierJoueur->getNom());
        textTour->setStyleSheet("font-size: 40px;color : white;font-family  : Showcard Gothic;");
        layout->addWidget(textTour,2,10);
    }

    compteur->start(1000);

    //afficher le compteur

    if (mode == "multijoueur"){
        textCompteur->setStyleSheet("font-size: 40px;font-family  : Showcard Gothic;color : red;");
        layout->addWidget(textCompteur,3,10);
    }
    else{
        textCompteur->setStyleSheet("font-size: 40px;font-family  : Showcard Gothic;");
        layout->addWidget(textCompteur,0,10);
    }
}


Grille::~Grille(){
    delete compteur;
    delete tempsCacher;
    delete tempsEliminer;
    delete textCompteur;
    delete textNomJoueur1;
    delete textNomJoueur2;
    delete textTour;
    delete premierJoueur;
    delete deuxiemeJoueur;
}

void Grille::compteurTemps()
{
    s++;
    if (s%60==0){
        m++;
        s=0;
    }
    if (s<10){
        if (m<10)
            textCompteur->setText("0"+QString::number(m)+":0"+QString::number(s));
    }
    else
        if (m<10)
            textCompteur->setText("0"+QString::number(m)+":"+QString::number(s));
    else
        textCompteur->setText(QString::number(m)+":"+QString::number(s));

    if (deuxiemeJoueur != NULL){
        if (s==10){
            if (tour == "joueur1"){
                tour = "joueur2";
                textTour->setText("Tour de :\n"+deuxiemeJoueur->getNom());
            }
            else{
                tour = "joueur1";
                textTour->setText("Tour de :\n"+premierJoueur->getNom());
            }
            s=0;
        }

    }

}

void Grille::compteurTempsChallenge()
{


    s++;
    if (s%60==0){
        m++;
        s=0;
    }
    if (s<10){
        if (m<10)
            textCompteur->setText("0"+QString::number(m)+":0"+QString::number(s)+"\n-------\n"+tempsLimite);
    }
    else
        if (m<10)
            textCompteur->setText("0"+QString::number(m)+":"+QString::number(s)+"\n-------\n"+tempsLimite);
    else
        textCompteur->setText(QString::number(m)+":"+QString::number(s)+"\n-------\n"+tempsLimite);
    gameOver(s,m);
}

void Grille::gameOver(int s, int m){
    if (!parentWidget()->isActiveWindow()){
        emit gameClose(compteur);
        return;
    }
    if ((s+(m*60))==tempsChallenge){
         emit gameLose(compteur,premierJoueur,deuxiemeJoueur);
    }
}

#define GET_CASE(i, j) static_cast<Case*>(grid->itemAtPosition((i), (j))  \
                        ->widget())

void Grille::caseSelected(int x, int y, int n)
{
    qDebug() <<"x= "<< x <<" y= "<< y <<" n= " << n;
    if(tempsCacher->isActive())
        return ;
    if(tempsEliminer->isActive())
        return ;





    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    GET_CASE(x, y)->setMode(Case::AFFICHEE);

    if(selectX == -1)
    {
        // si il n'y a aucune case selectionée
        selectX = x;
        selectY = y;
    }
    else
    {
         // la case selectionée est comme l'autre
        if(GET_CASE(selectX, selectY)->getId() == n)
        {
            // ajouter score
            if (deuxiemeJoueur != NULL ){
                if (tour == "joueur1"){
                    premierJoueur->setScore(premierJoueur->getScore()+1);
                }
                else {
                    deuxiemeJoueur->setScore(deuxiemeJoueur->getScore()+1);
                }
            }

            // Bonus
            if (deuxiemeJoueur != NULL ){
              if (tour == "joueur2"){
                  int n = deuxiemeJoueur->getNbCaseOuvert();
                  deuxiemeJoueur->setNbCaseOuvert(n+1);
                }
              else {
                  int n = premierJoueur->getNbCaseOuvert();
                  premierJoueur->setNbCaseOuvert(n+1);
              }
            } else {
                int n = premierJoueur->getNbCaseOuvert();
                premierJoueur->setNbCaseOuvert(n+1);
            }



            // éliminer deux cartes
            selectN = n;
            tempsEliminer->start(1000);

            // désectionner la case
            selectX = -1;

            //si il reste une case masquée on quitte la boucle
            int i, j;
            for(i = 0; i < nbCases-1; i++)
            {
                for(j = 0; j < nbCases; j++)
                {
                    if(GET_CASE(i, j)->getMode() == Case::MASQUEE || GET_CASE(i, j)->getMode() == Case::BONUS)
                        return ;
                }
            }

            // si il n'y a pas de case masquée le jeu est fini
            emit gameWon(m*60+s,compteur,premierJoueur,deuxiemeJoueur);

        }
        else
        {
            // la case selectionée n'est pas comme l'autre
            selectX = -1;
            if (deuxiemeJoueur != NULL ){
            if (tour == "joueur1"){
                tour = "joueur2";
                textTour->setText("Tour de :\n"+deuxiemeJoueur->getNom());
            }
            else{
                tour = "joueur1";
                textTour->setText("Tour de :\n"+premierJoueur->getNom());
            }
            s=0;
            }
            // Bonus
            if (deuxiemeJoueur != NULL ){
              if (tour == "joueur2"){
                 deuxiemeJoueur->setNbCaseOuvert(0);
                }
              else {

                 premierJoueur->setNbCaseOuvert(0);
              }
            } else {
                premierJoueur->setNbCaseOuvert(0);
            }
            tempsCacher->start(1000);
        }
    }
}

void Grille::afficherBonus()
{


    srand (time(NULL));
    int n1 = elementsRestants.size();
    if (n1 ==0)
        return;
    int bonus = rand() % n1;
    int bonus2 = rand() % n1;
    while (bonus2 == bonus ){
        if (n1==1)
            break;
        bonus2 = rand() % n1;
    }
    bonus = elementsRestants[bonus];
    bonus2 = elementsRestants[bonus2];

    qDebug() << "vous avez " << n1 << " elements, le nombre est "<<bonus;
    qDebug() << "vous avez " << n1 << " elements, le nombre est "<<bonus2;

    randomBonus.clear();
    for(int i = 0; i < nbCases-1; ++i) {
         for(int j = 0; j < nbCases; ++j) {
            qDebug() <<"matrix[" << i << "]["<<j<<"]="<<matrix[i][j]<<"\n";
            if (matrix[i][j] == bonus || matrix[i][j] == bonus2){
                qDebug() << "ses index sont "<< i <<" "<< j << "\n";
                randomBonus.push_back({i,j});
            }
        }
    }

    for (int i=0;i<4;i++)
        qDebug() << randomBonus[i].first<<"-"<<randomBonus[i].second<<"nombres elements :"<<n1;


    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    int i, j;
    for(i = 0; i < nbCases-1; i++)
    {
        for(j = 0; j < nbCases; j++)
        {
            for(int it=0;it<3;it++) {
                if (randomBonus[it].first == i && randomBonus[it].second == j){
                    qDebug() <<"BONUS is "<<i <<j;
                    if (GET_CASE(i, j)->getMode() == Case::MASQUEE){
                        GET_CASE(i, j)->setMode(Case::BONUS);
                    }
                }
            }
        }
    }
}

void Grille::cacherCases()
{
    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    int i, j;
    for(i = 0; i < nbCases-1; i++)
    {
        for(j = 0; j < nbCases; j++)
        {
            if(GET_CASE(i, j)->getMode() == Case::AFFICHEE)
                GET_CASE(i, j)->setMode(Case::MASQUEE);
            if(GET_CASE(i, j)->getMode() == Case::BONUS)
                GET_CASE(i, j)->setMode(Case::MASQUEE);
        }
    }
}

void Grille::eliminerCases()
{
    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    int i, j;
    for(i = 0; i < nbCases-1; i++)
    {
        for(j = 0; j < nbCases; j++)
        {
            if(GET_CASE(i, j)->getMode() == Case::AFFICHEE)
                GET_CASE(i, j)->setMode(Case::ELIMINEE);
            if(GET_CASE(i, j)->getMode() == Case::BONUS)
                GET_CASE(i, j)->setMode(Case::MASQUEE);
        }
    }
    // ajouter score
    if (deuxiemeJoueur != NULL ){
        if (tour == "joueur1"){
            textNomJoueur1->setText(premierJoueur->getNom()+"\nScore: "+QString::number(premierJoueur->getScore()));
        }
        else {
            textNomJoueur2->setText(deuxiemeJoueur->getNom()+"\nScore: "+QString::number(deuxiemeJoueur->getScore()));
        }
        s=0;
    }
    else {
        premierJoueur->setScore(premierJoueur->getScore()+1);
        textNomJoueur1->setText(premierJoueur->getNom()+"\nScore: "+QString::number(premierJoueur->getScore()));
    }


    //Bonus
    std::remove(elementsRestants.begin(),elementsRestants.end(),selectN);
    elementsRestants.resize(elementsRestants.size()-1);

    if (deuxiemeJoueur != NULL ){
      if (tour == "joueur2"){
          if (deuxiemeJoueur->getNbCaseOuvert()>=2){
                afficherBonus();
          }
        }
      else {

          if (premierJoueur->getNbCaseOuvert()>=2){
              afficherBonus();
          }
      }
    } else {
        if (premierJoueur->getNbCaseOuvert()>=2){
            afficherBonus();
        }
    }
}


Case::Case(int i, int j, int n,QString theme)
  : x(i), y(j), idCase(n), modeCase(Case::MASQUEE), theme(theme)
{
    buttonCase = new QPushButton("", this);
    buttonCase->setStyleSheet("background-image:url(\"C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/backcase.png\"); background-repeat: no-repeat;margin:5px;padding: 135px 55px 0px 0px;background-position: center;");
    connect(buttonCase, SIGNAL(clicked()),
        this, SLOT(clicked()));
}

Case::~Case(){
    delete buttonCase;
}

void Case::clicked()
{
    if(modeCase == Case::MASQUEE || modeCase == Case::BONUS)
        emit selected(x, y, idCase);
}

void Case::setMode(Apparence e)
{
    modeCase = e;
    switch(e)
    {
    case Case::MASQUEE:
        buttonCase->setStyleSheet("background-image:url(\"C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/backcase.png\"); background-repeat: no-repeat;margin:5px;padding: 50px 10px 50px 50px;background-position: center;");
        break;
    case Case::BONUS:
        buttonCase->setStyleSheet("background-image:url(\"C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/backcasebonus.png\"); background-repeat: no-repeat;margin:5px;padding: 50px 10px 50px 50px;background-position: center;");
        break;
    case Case::ELIMINEE:
        buttonCase->setStyleSheet("background-image:url(\"\");background-color:transparent; background-repeat: no-repeat;margin:5px;padding: 50px 10px 50px 50px;background-position: center;");
        break;
    case Case::AFFICHEE:
        QString string;
        string = "background-image:url(\"C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/" + QString::number(idCase)+ ".bmp\"); background-repeat: no-repeat;margin:5px;padding: 50px 10px 50px 50px;background-position: center;";
        if (theme == "objets")
            string = "background-image:url(\"C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/" + QString::number(idCase)+ ".bmp\"); background-repeat: no-repeat;margin:5px;padding: 50px 10px 50px 50px;background-position: center;";
        if (theme == "flags")
            string = "background-image:url(\"C:/Users/Ibrahim/Desktop/qt/memoryPuzzle/images/flags/" + QString::number(idCase)+ ".png\"); background-repeat: no-repeat;margin:5px;padding: 50px 10px 50px 50px;background-position: center;";
        buttonCase->setStyleSheet(string);
        break;
    }
}


Joueur::Joueur() : nom("Joueur"), score(0)
{}

Joueur::Joueur(QString n) : nom(n), score(0)
{}

Joueur::~Joueur(){}

unsigned Joueur::getScore(){
    return score;
}

void Joueur::setScore(unsigned s){
    score = s;
}

QString Joueur::getNom(){
    return nom;
}

void Joueur::setNom(QString n){
    nom = n;
}

int Joueur::getNbCaseOuvert(){
    return nbCaseOuvertSuite;
}

void Joueur::setNbCaseOuvert(int n){
    nbCaseOuvertSuite = n;
}
