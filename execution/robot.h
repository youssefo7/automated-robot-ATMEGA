#include "del.h"
#include "memoire_24.h"
#include "moteur.h"
#include "Transmission.h"
#include "sonorite.h"
#include "can.h"
#include "IR.h"

#define s1 0x04
#define s2 0x08
#define s3 0x10
#define s4 0x20
#define s5 0x80

enum class Etat
{
    A,
    B,
    S,
};

class Robot
{
public:
    Robot(){};
    void execution();
    void partieA();
    void partieB();
    void clignoterVertDeuxSecondes();
    void clignoterRougeDeuxSecondes();
    void clignoterAmbreDeuxSecondes();
    void parcours(Etat etat);
    void stationner();
    void avancerSurLigneHardpartieA();
    void avancerSurLigneHard();
    void avancerSurLigneSoft();
    void couloir();

private:
    bool appuiBouton(uint8_t pinBouton);
    void changementEtat();
    void jouerSon(uint8_t note);
    void jouerSonS(uint8_t note);
    uint8_t obstacle();
    void turn90Left();
    void turn90Right();
    void flushMemoire();

    Etat etat = Etat::A;

    const uint8_t SON_GRAVE = 45;
    const uint8_t SON_AIGUE = 80;
    uint8_t donneeMemoire;
    uint16_t adresseMemoire = 0x0000;
    uint8_t tailleMemoire = 0x00;
    uint8_t broches[5] = {s1, s2, s3, s4, s5};
    bool wasAtLeft;

    Del del;
    Moteur moteur;
    Son son;
    can capteur;
    RS print;
    Memoire24CXXX memoire;
    IR ir;
};
