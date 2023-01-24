#include "IR.h"
#define DELAI_REBOND 25
// using PORT/PIN A
bool IR::isActive(uint8_t pin)
{
    if (PINA & pin)
    {
        _delay_ms(DELAI_REBOND);
        if (PINA & pin)
        {
            return true;
        }
        return false;
    }
}

uint8_t IR::checkSensors()
{
    int count = 0;
    for (int i = 0; i < 5; i++)
    { // 5 sensors
        if (isActive(broches[i]))
        {
            count++;
        }
    }
    return count;
}

bool IR::isAt90Left()
{
    return isActive(s1) && isActive(s2) && isActive(s3);
}

bool IR::isAt90Right()
{
    return isActive(s3) && isActive(s4) && isActive(s5);
}

bool IR::isAtSplit()
{
    return isActive(s2) && isActive(s3) && isActive(s4);
}
