#define F_CPU 8000000UL
#include "Transmission.h"

RS::RS()
{
    initialisationUART();
}
void RS::initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    //UCSR0A |= (1 << RXC0) | (1 << TXC0);

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// Du USART vers le PC
void RS::transmissionUART(uint8_t donnee)
{

    while (!(UCSR0A & (1 << UDRE0)))
        ;

    UDR0 = donnee;
}
void RS::transmissionUART16Bit(uint16_t donnee)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    UDR0 = donnee;
}

//Transmet une chaine de charactere, necessite de specifier la taille de la chaine.
void RS::transmissionUARTChaine(uint8_t *chaineDonnee, int taille)
{
    for (int i = 0; i < taille; i++)
        transmissionUART(chaineDonnee[i]);
}

//Recevoir des donnee en un octet
uint8_t RS::donneeRecue()
{
    while (!(UCSR0A & (1 << RXC0)))
        ;

    return UDR0;
}
