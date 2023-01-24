#include "robot.h"

bool Robot::appuiBouton(uint8_t pinBouton)

{
    if (PIND & (1 << pinBouton))
    {
        _delay_ms(10);
        if (PIND & (1 << pinBouton))
            while (PIND & (1 << pinBouton))
            {
            }
        return true;
    }
    return false;
}
void Robot::clignoterVertDeuxSecondes()
{
    for (int i = 0; i < 8; i++)
    {
        PORTB |= (1 << PORTB1);
        _delay_ms(125);
        PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
        _delay_ms(125);
    }
}

void Robot::clignoterRougeDeuxSecondes()
{
    for (int i = 0; i < 8; i++)
    {
        PORTB |= (1 << PORTB0);
        _delay_ms(125);
        PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
        _delay_ms(125);
    }
}

void Robot::clignoterAmbreDeuxSecondes()
{
    for (int i = 0; i < 8; i++)
    {
        PORTB |= (1 << PORTB0);
        _delay_ms(62);
        PORTB |= (1 << PORTB1);
        _delay_ms(62);
        PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
        _delay_ms(126);
    }
}

void Robot::execution()
{
    while (true)
    {
        changementEtat();
    }
}

// la selection de quel mode
void Robot::changementEtat()
{
    switch (etat){
    case Etat::A:
        _delay_ms(25);
        while (!appuiBouton(PD0))
        {
            del.setCouleurLumiere(Couleur::VERTE);
            if (appuiBouton(PD2))
            {
                clignoterVertDeuxSecondes();
                partieA();
            }
        }
        etat = Etat::B;
        break;
    case Etat::B:
        _delay_ms(25);
        while (!appuiBouton(PD0))
        {
            del.setCouleurLumiere(Couleur::ROUGE);
            if (appuiBouton(PD2))
            {
                clignoterRougeDeuxSecondes();
                partieB();
                couloir();
            }
        }
        etat = Etat::S;
        break;
    case Etat::S:
        _delay_ms(25);
        while (!appuiBouton(PD0))
        {
            del.setCouleurLumiere(Couleur::AMBREE);
            if (appuiBouton(PD2))
            {
                clignoterAmbreDeuxSecondes();
                couloir();
            }
        }
        etat = Etat::A;
        break;
    }
}

void Robot::jouerSon(uint8_t note)
{
    moteur.arret();
    son.jouerNote(note);

    memoire.ecriture(adresseMemoire, note);
    _delay_ms(5);

    _delay_ms(1000);
    son.arret();
    moteur.avancer(50);
    _delay_ms(10);

    adresseMemoire++;
    tailleMemoire++;
    moteur.navigation(50,15);
    _delay_ms(150);
}
void Robot::jouerSonS(uint8_t note)
{
    moteur.arret();
    son.jouerNote(note);
}

uint8_t Robot::obstacle()
{
    return (capteur.lecture(0) >> 2);
}

void Robot::avancerSurLigneHardpartieA()
{
    if (ir.isActive(s2) || ir.isActive(s1))
    {
        moteur.avancer(40);
        _delay_ms(5);
        moteur.navigation(52, 15);
    }
    else if (ir.isActive(s4) || ir.isActive(s5))
    {
        moteur.avancer(40);
        _delay_ms(5);
        moteur.navigation(10, 60);
    }
    else
    {
        moteur.avancer(40);
    }
}

void Robot::avancerSurLigneHard()
{
    if (ir.isActive(s2) || ir.isActive(s1))
    {

        // tourner a gauche
        moteur.navigation(50, 15);
    }
    if (ir.isActive(s4) || ir.isActive(s5))
    {

        // tourner a droite
        moteur.navigation(20, 28);
    }
    if(ir.isActive(s3))
    {
        // avancer
        // moteur.avancer(30);
        moteur.avancer(40);
    }
}

void Robot::avancerSurLigneSoft()
{
    if (ir.isActive(s1))
    {
        // tourner a gauche

        moteur.navigation(45, 0);
    }
    if (ir.isActive(s5))
    {
        // tourner a droite
        moteur.navigation(0, 40);
    }
    if (ir.isActive(s3))
    {
        moteur.avancer(30);
    }
}

void Robot::couloir() // REUSSI A 8.5V
{
    moteur.navigation(57, 50);
    _delay_ms(500);
    for (int i = 0; i < 325; i++)
        avancerSurLigneHard();

    moteur.navigation(25, 35); // droite
    _delay_ms(750);

    int counter = 0;
    while (counter <= 3)
    {
        if (ir.isActive(s5))
        {
            moteur.navigation(45, 10); // gauche
            _delay_ms(1200);
            while (!ir.isActive(s1))
            {
            }
            counter++;
        }

        if (ir.isActive(s1))
        {
            moteur.navigation(20, 35); // droite
            _delay_ms(1200);
            while (!ir.isActive(s5))
            {
            }
            counter++;
        }
    }

    moteur.navigation(50, 10); // gauche
    _delay_ms(200);

    while (ir.isActive(s1) || ir.isActive(s2) || ir.isActive(s3) || ir.isActive(s4) || ir.isActive(s5))
    {
        avancerSurLigneHard();
    }

    stationner();
}

void Robot::stationner() //REUSSI A 8.2V
{
    moteur.arret();
    _delay_ms(2000);
    moteur.reculer(50);
    _delay_ms(850);

    moteur.navigationReculons(10, 40);
    _delay_ms(900);

    moteur.reculer(90);
    _delay_ms(650);
    moteur.arret();
    _delay_ms(1000);

    son.jouerNote(80);
    _delay_ms(1000);
    son.arret();
}

void Robot::flushMemoire()
{
    for (uint8_t i = 0; i < 100; i++)
    {
        memoire.ecriture(i, 0);
        _delay_ms(5);
    }
}

void Robot::partieA()
{
    flushMemoire();
    moteur.navigation(57, 50);
    _delay_ms(1000);
    while (!(ir.checkSensors() == 5))
    {

        avancerSurLigneHard();

        if (obstacle() > 40 && obstacle() < 90) // Loin
        {
            moteur.avancer(40);
            _delay_ms(200);
            if (obstacle() > 40 && obstacle() < 90)
            {
                del.setCouleurLumiere(Couleur::ROUGE);
                jouerSon(45); // Loin
                for (int i = 0; i < 200; i++)
                {
                    avancerSurLigneHard();
                }
            }
            else if (obstacle() > 100 && obstacle() < 180) // Proche
            {

                del.setCouleurLumiere(Couleur::VERTE);
                jouerSon(80); // Proche
                for (int i = 0; i < 200; i++)
                {
                    avancerSurLigneHard();
                }
            }
        }

        if (obstacle() > 100 && obstacle() < 180) // Proche
        {
            moteur.avancer(40);
            _delay_ms(200);
            if (obstacle() > 100 && obstacle() < 180)
            {
                del.setCouleurLumiere(Couleur::VERTE);
                jouerSon(80);
                for (int i = 0; i < 250; i++)
                {
                    avancerSurLigneHard();
                }
            }
        }
        del.setCouleurLumiere(Couleur::ETEINTE);
    }
    moteur.arret();
}
void Robot::turn90Left()
{
    moteur.avancer(50);
    _delay_ms(200);
    moteur.arret();
    _delay_ms(100);
    moteur.navigation(50, 0); // replace with function turnLeft
    _delay_ms(1000);
    while (!(ir.isActive(s1) || ir.isActive(s2)))
        moteur.navigation(40, 0);
    moteur.navigation(10, 45);
    _delay_ms(200);
}

void Robot::turn90Right()
{
    moteur.navigation(50,47);
    _delay_ms(200);
    moteur.arret();
    _delay_ms(100);
    moteur.navigation(0, 45); // replace with function turnRight
    _delay_ms(1000);
    while (!(ir.isActive(s5) || ir.isActive(s4) || ir.isActive(s3)))
        moteur.navigation(0, 40);
    moteur.navigation(55, 10);
    _delay_ms(200);
}

void Robot::partieB()
{
    uint8_t p1;
    uint8_t p2;
    uint8_t p3;
    uint16_t indexMemoireLecture = 0x0000;

    memoire.lecture(indexMemoireLecture++, &p1);
    _delay_ms(5);

    memoire.lecture(indexMemoireLecture++, &p2);
    _delay_ms(5);

    memoire.lecture(indexMemoireLecture++, &p3);
    _delay_ms(5);

    if ((p3 == 80) || (p3 == 45))
    {
        uint8_t temp = p2;
        p2 = p3;
        p3 = temp;
    };
    enum partieB
    {
        virage1,
        split1,
        choreo,
        split2,
        virage2,
        stop
    };

    partieB section = partieB::virage1;
    while (section != partieB::stop)
    {
        switch (section)
        {
        case partieB::virage1:
        {
            moteur.navigation(57, 50);
            _delay_ms(550);
            int counter = 0;
            while (counter != 2)
            {
                if (ir.isAt90Left() && counter != 2)
                {
                    turn90Left();
                    counter++;
                }
                avancerSurLigneHard();
            }
            while (!ir.isAtSplit())
            {
                avancerSurLigneHard();
            }

            section = partieB::split1;
            break;
        }

        case partieB::split1:

            moteur.arret();
            _delay_ms(500);


            // start timer
            if (p2 == 45)
            { // gauche
                moteur.navigation(50, 15);
                _delay_ms(750);
            }
            else
            { // droit
                moteur.navigation(20, 45);
                _delay_ms(750);
            }

            

            for (int i = 0; i < 300; i++)
            {
                avancerSurLigneSoft();
            }

            while (ir.checkSensors() < 3)
            {
                avancerSurLigneHard();
            }

            

            moteur.avancer(50);
            _delay_ms(50);
            for (int i = 0; i < 100; i++)
            {
                avancerSurLigneHard();
            }

            section = partieB::choreo;

            break;

        case partieB::choreo:

            moteur.arret();
            _delay_ms(500);
        
            if (p3 == 45)
            {
                // choreoDroite REUISSI A 8.22V
                moteur.navigation(0,45);
                _delay_ms(500);
                moteur.arret();
                _delay_ms(1000);
                moteur.navigation(55,0);
                _delay_ms(600);
            }
            else if (p3 == 80)
            {
                // choreoGauche REUSSI A 8.2V
                moteur.navigation(55, 0);
                _delay_ms(500);
                moteur.arret();
                _delay_ms(1000);
                moteur.navigation(0,40);
                _delay_ms(600);
            }
            else
            {

                // choreoRecul REUSSI A 8.2V
                moteur.navigationReculons(60,45);
                _delay_ms(750);
                moteur.arret();
            }

            while (!ir.isAtSplit())
            {
                avancerSurLigneHard();
            }
            moteur.arret();
            section = partieB::split2;
            break;

        case partieB::split2:
        {



            moteur.arret();
            _delay_ms(500);


            // start timer
            if (p1 == 45)
            { // gauche
                del.setCouleurLumiere(Couleur::VERTE);
                moteur.navigation(50, 15);
                _delay_ms(750);
            }
            else
            { // droit
                del.setCouleurLumiere(Couleur::ROUGE);
                moteur.navigation(20, 45);
                _delay_ms(750);
            }

        
            for (int i = 0; i < 300; i++)
            {
                avancerSurLigneSoft();
            }

            for(int i = 0; i < 300; i++)
            {
                avancerSurLigneHard();
            }

        


            int counter = 0;
            while (counter != 2)
            {
                if (ir.isAt90Right() && counter != 2)//2 virage
                {
                    turn90Right();
                    counter++;
                }
                avancerSurLigneHard();
            }
            while (!(ir.checkSensors() == 5))//at line
            {
                avancerSurLigneHard();
            }

            





            
            del.setCouleurLumiere(Couleur::VERTE);
            
            moteur.arret();
            _delay_ms(1000);


            section = partieB::stop;
            break;
        }
        case partieB::stop:
            break;
        }
    }
}