#ifndef PARAMETRE_H
#define PARAMETRE_H

#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class Parametre;
}

class Parametre : public QDialog
{
    Q_OBJECT


public:
    explicit Parametre(QWidget *parent = nullptr,QMediaPlayer * music = NULL);
    ~Parametre();
    int difficultee=1;
    int diffSelect=0;
    QString mode="histoire";
    QString modeSelect="";
    QString theme="objets";
    QString themeSelect="";
    QMediaPlayer * music;

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_10_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_11_clicked();

    void on_volume_valueChanged(int value);



private:
    Ui::Parametre *ui;
};

#endif // PARAMETRE_H
