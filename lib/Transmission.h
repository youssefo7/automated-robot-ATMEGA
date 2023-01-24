#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/eeprom.h>

class RS
{
public:
    RS();
    void initialisationUART();
    void transmissionUART(uint8_t donnee);
    void transmissionUARTChaine(uint8_t *chaineDonnee, int taille);

    void transmissionUART16Bit(uint16_t donnee);
    uint8_t donneeRecue();
};