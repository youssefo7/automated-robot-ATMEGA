#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
// Constante recquise pour _delay_ms() dans pulsePwm();
const int TEMPS_ = 1;

enum class Mouvement {
    VIRAGE_DROITE_90,
    VIRAGE_GAUCHE_90,
    VIRAGE_DROITE_45, 
    VIRAGE_GAUCHE_45, 
    VIRAGE_DROITE_15, 
    VIRAGE_GAUCHE_15,
    LIGNE_DROITE_AVANCER,
    LIGNE_DROITE_RECULER,
    ARRET,
};
class Moteur
{
public:
    // Constructeur pour Moteur.
    Moteur();

    // Methode pour faire avancer les roues. Prend en parametre une valeur pour PWM.
    void avancer(uint8_t pourcentagePwm);
    // Methode pour fair reculer les roues. Prend en parametre une valeur pour PWM.
    void reculer(uint8_t pourcentagePwm);
    // Methode pour arreter les roues.
    void arret();
    // Methode pour avoir deux valeurs PWM differentes dans les deux roues.
    void navigation(uint8_t pourcentagePwmDroite, uint8_t pourcentagePwmGauche);

    void navigationReculons(uint8_t pwmDroite, uint8_t pwmGauche);

    // Methode pour avoir un pulse avant chaque appel de methode pour faire rouler
    // Cruciale pour contrer les forces de frictions.
    void pulsePwm();

    // Methode virage 90 degre
    void mouvement(Mouvement mouvement);

    void routeEGIJ();
    void routeEFHJ();
    void MOP();
    void MNP();
    void JM();

private:
    // Constantes utilisees dans les methodes publiques et privees.
    
    uint8_t pourcentageToPwm(int pourcentage);
    
    const uint8_t ARRET_ = 255;
    const uint16_t PWMMAX_ = 10;
    const uint8_t pwm_1 = 200;
    const uint8_t pwm_2 = 50;
    const uint8_t pwm_3 = 180;
    const uint8_t pwm_4 = 80;
    const uint8_t pwm_5 = 150;
    const uint8_t pwm_6 = 100;

};