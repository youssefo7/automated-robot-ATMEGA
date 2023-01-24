#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
//#include "moteur.h"

#define s1 0x04
#define s2 0x08
#define s3 0x10
#define s4 0x20
#define s5 0x80

class IR
{
public:
    bool isActive(uint8_t pin);
    uint8_t checkSensors();
    bool isAt90Right();
    bool isAt90Left();
    bool isAtSplit();

    uint8_t broches[5] = {s1, s2, s3, s4, s5};
};