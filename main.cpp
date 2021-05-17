#include "controlleur.h"

#include <QApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controlleur w;
    w.show();
    return a.exec();
}
