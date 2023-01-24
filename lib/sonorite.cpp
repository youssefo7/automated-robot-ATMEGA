#include "sonorite.h"

// Constructeur de son met les Port D5 et D4 en entreer sans affecter les autres
Son::Son()
{
    DDRB |= (1 << PB3);
    TCCR0A |= (1 << COM0A0) | (1 << WGM01); // prescaler N = 8 // CTC Mode
    TCCR0B |=  (1 << CS02) ;             // On compare match
}

// jouerNote initalise le timer1 en utilisant le mode CTC avec prescaler 8
// OCR1A prend la valeur a la position note - 45 de la table tempsActif_.
// Cela permet de facilement identifier quelle note appartient a quelle valeur devrait prendre OCR1A
void Son::jouerNote(uint8_t note)
{
    PORTB |= (1<<PB2);
    OCR0A = tempsActif_[note-45];
}

// Mettre OCR1A a 0 permet d'arreter la sonorite
void Son::arret()
{
    OCR0A = ARRET_;
}
