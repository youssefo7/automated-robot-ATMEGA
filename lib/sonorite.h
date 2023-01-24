#include <avr/io.h>

//Classe son utilise le timer1
class Son
{
public:
    //Constructeur de Son
    Son();
    
    //Methode : jouerNote a un parametre de uint8_t note et ne retourne rien.
    void jouerNote(uint8_t note);
    
    //Methode : arret ne retourne rien
    void arret();

private:
    //Constantes dans une table represente les valeurs de temps actifs - 1 
    //Valeurs obtenues en utilisant la formule de frequence de la documentation
    const uint16_t tempsActif_[37] = {4544, 4289, 4049, 3821, 3607, 3404, 3213, 3033,
                                    2864, 2702, 2550, 2407, 2272, 2144, 2024, 1910, 1803, 1702, 1606, 1516, 1431,
                                    1350, 1275, 1203, 1135, 1072, 1011, 955, 901, 850, 803, 757, 715, 675, 637,
                                    601, 568};

    //Constante utilisee pour arreter le son.
    const uint16_t ARRET_ = 0x0000;
};