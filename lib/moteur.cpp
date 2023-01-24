#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"

// Constructeur de la classe fait en sorte qu'il determine les PORTB3, PORT5 en sortie pour la roue de droite.
// Determine les PINB4 et PINB6 en sortie pour la roue de gauche.
// Les PINS ont ete determinees apres avoir fait des testes avec les branchements.
// ** Note : Ne pas confondre le enable et direction quand on fait le branchement de a carte et le pond en H **

Moteur::Moteur()
{
    DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);

    TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1) | (1 << COM1A0) | (1 << COM1B0);
    TCCR1B = (1 << CS11);

    OCR1A = 0xff;
    OCR1B = 0xff;
}



uint8_t Moteur::pourcentageToPwm(int pourcentage)
{

    if (pourcentage > 100)
    {
        pourcentage = 100;
    }
    else
    if (pourcentage < 0)
    {
        pourcentage = 0;
    }

    return 255 - ((pourcentage * (uint8_t)255)/100);
}

void Moteur::pulsePwm()
{
    OCR1A = pourcentageToPwm(70);
    OCR1B = 0.75*pourcentageToPwm(70);
    _delay_ms(TEMPS_);
}

// Les methodes suivantes utilisent le Timer0 avec mode PWM, Phase Correcte et Compare on match (ceci peut changer si nous trouvons une meilleur methode)
void Moteur::avancer(uint8_t pourcentagePwm)
{
    PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD7);
    
    OCR1A = pourcentageToPwm(pourcentagePwm);
    OCR1B = 0.85*pourcentageToPwm(pourcentagePwm);
}

// Methode utilisee pour metre le moteur a l'arret.
void Moteur::arret()
{
    OCR1A = ARRET_;
    OCR1B = ARRET_;
}

// Methode utilisee pour renverser la pin de Direction des roues (PB5 et PB6)
// A ameliorer car cela change le comportement du PORTB au complet.
void Moteur::reculer(uint8_t pourcentagePwm)
{
    PORTD |= ~(1 << PD6);
    PORTD |= ~(1 << PD7);
    
    OCR1A = pourcentageToPwm(pourcentagePwm);
    OCR1B = 0.85*pourcentageToPwm(pourcentagePwm);
}

// Methode utilisee pour naviger en AVANT.
// A ameliorer.
void Moteur::navigation(uint8_t pourcentagePwmDroite, uint8_t pourcentagePwmGauche)
{
    PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD7);
    
    OCR1A = pourcentageToPwm(pourcentagePwmDroite);
    OCR1B = 0.85*pourcentageToPwm(pourcentagePwmGauche);
}
void Moteur::navigationReculons(uint8_t pwmDroite, uint8_t pwmGauche)
{
    PORTD |= ~(1 << PD6);
    PORTD |= ~(1 << PD7);
    
    OCR1A = pourcentageToPwm(pwmDroite);
    OCR1B = 0.85*pourcentageToPwm(pwmGauche);
}

// Methode utilisee pour virage 90 degre.
// void Moteur::mouvement(Mouvement mouvement)
// {
//     const uint8_t pwm_1 = 200;
//     const uint8_t pwm_2 = 50;
//     const uint8_t pwm_3 = 180;
//     const uint8_t pwm_4 = 80;
//     const uint8_t pwm_5 = 150;
//     const uint8_t pwm_6 = 100;

//     //tourner 90 degre a droite
//     switch (mouvement)
//     {
//     case Mouvement::VIRAGE_DROITE_90:
//         navigation(pwm_1, pwm_2);
//         break;

//     case Mouvement::VIRAGE_GAUCHE_90:
//         navigation(pwm_2, pwm_1);
//         break;

//     case Mouvement::VIRAGE_DROITE_45:
//         navigation(pwm_3, pwm_4);
//         break;

//     case Mouvement::VIRAGE_GAUCHE_45:
//         navigation(pwm_4, pwm_3);
//         break;

//     case Mouvement::VIRAGE_DROITE_15:
//         navigation(pwm_5, pwm_6);
//         break;

//     case Mouvement::VIRAGE_GAUCHE_15:
//         navigation(pwm_6, pwm_5);
//         break;

//     case Mouvement::LIGNE_DROITE_AVANCER:
//         avancer(200);
//         break;

//     case Mouvement::LIGNE_DROITE_RECULER:
//         reculer(200);
//         break;

//     case Mouvement::ARRET:
//         navigation(0,0);
//         break;

//     default:
//         break;
//     }

// }

void Moteur::routeEGIJ()
{
    navigation(pwm_1, pwm_2);
    _delay_ms(625);

    // avancer(200);
    // _delay_ms(1250);

    // navigation(pwm_2, pwm_1);
    // _delay_ms(1250);

    // avancer(200);
    // _delay_ms(1600);

    //  navigation(pwm_2, pwm_1);
    // _delay_ms(1250);

    // avancer(200);
    // _delay_ms(1250);

    // navigation(pwm_1, pwm_2);
    // _delay_ms(1250);
    arret();
}

void Moteur::routeEFHJ()
{
}

void Moteur::MOP()
{
}

void Moteur::MNP()
{
}

void Moteur::JM()
{
}