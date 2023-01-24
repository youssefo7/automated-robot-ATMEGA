#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "del.h"

// Variables globales (constantes)
const uint8_t DELAY_AMBREE = 10; // Choix Arbitraire du delai pour avoir une lumiere ambree

// Constructeur de la classe determine donc les deux PORT0 et PORTB1 en sortie respectivement.
// A cause des bug, nous avons decider de garder ce format au lieu de DDRB = 0xFF ou DDRB |= 0xFF car le constructeur de la classe Moteur determine aussi des PIN en sortie.
Del::Del()
{
    DDRB |= (1 << PB0) | (1 << PB1);
}

// Une methode pour changer la couleur de la DEL par rapport  a une machine a etat, Couleur.
// Pour le mode AMBREE, il n'est pas operationel car cela depend dans quel contexte il faut l'utiliser. (ex: pour un nombre de fois, nous utilisons explicitement une boucle dans le main.)
// Clairification pour AMBREE : Nous appelons la methode del.setCouleurLumiere(Couleur::AMBREE) dans une boucle.
void Del::setCouleurLumiere(Couleur couleur)
{

    switch (couleur)
    {
    case Couleur::ETEINTE:
        PORTB &= ~(1 << PB0) & ~(1 << PB1);
        PORTB |= LUMIERE_ETEINTE_;
        break;

    case Couleur::VERTE:
        PORTB &= ~(1 << PB0) & ~(1 << PB1);
        PORTB |= LUMIERE_VERTE_;
        break;

    case Couleur::ROUGE:
        PORTB &= ~(1 << PB0) & ~(1 << PB1);
        PORTB |= LUMIERE_ROUGE_;
        break;

    case Couleur::AMBREE:
        PORTB &= ~(1 << PB0) & ~(1 << PB1);
        PORTB = LUMIERE_VERTE_;
        _delay_ms(DELAY_AMBREE);
        PORTB &= ~(1 << PB0) & ~(1 << PB1);
        PORTB = LUMIERE_ROUGE_;
        _delay_ms(DELAY_AMBREE);
        break;
    }
}
