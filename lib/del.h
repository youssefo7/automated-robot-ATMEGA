#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

// Enum class pour avoir une machine a etat
enum class Couleur
{
    ETEINTE,
    ROUGE,
    VERTE,
    AMBREE,
};

class Del
{
public:
    // Nous implementons un Constructeur.
    Del();

    // Methode pour changer la couleur de la DEL : Rouge, Verte, Eteinte ou AMBREE.
    void setCouleurLumiere(Couleur couleur);

private:
    // Constantes majoritairement utilisees dans la methode setCouleurLumiere(Couleur couleur)
    const uint8_t LUMIERE_ETEINTE_ = 0x00;
    const uint8_t LUMIERE_ROUGE_ = (1 << PB0);
    const uint8_t LUMIERE_VERTE_ = (1 << PB1);
};