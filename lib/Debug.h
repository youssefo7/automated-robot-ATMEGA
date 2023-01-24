#define F_CPU 8000000UL
#include "Transmission.h"
#include <stdio.h>

//#define DEBUG // a commenter ou non au besoin

#ifdef DEBUG

#define DEBUG_PRINT(x) RS::transmissionUART(x)

#else

#define DEBUG_PRINT(x) do{} while (0)

#endif

