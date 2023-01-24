#define F_CPU 8000000UL

#include "robot.h"

uint8_t obstacle()
{
    can can;
    return (can.lecture(0) >> 2);
}

int main()
{

    Robot robot;
    // robot.execution();
    Del del;
    IR ir;
    Moteur moteur;
    RS print;
    Son sonorite;

    // sonorite.jouerNote(45);
    // moteur.avancer(40);
    robot.execution();

    // del.setCouleurLumiere(Couleur::ROUGE);
    // while (true)
    // {
    //     robot.avancerSurLigneHard();
    // }
}