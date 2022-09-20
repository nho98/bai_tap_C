#include <stdio.h>

uint16_t PORT_A = 0x0000;

typedef enum{
    GPIO_PIN_0 = 0x0001,
    GPIO_PIN_1 = 0x0002,
    GPIO_PIN_2 = 0x0004,
    GPIO_PIN_3 = 0x0008,
    GPIO_PIN_4 = 0x0010,
    GPIO_PIN_5 = 0x0020,
    GPIO_PIN_6 = 0x0040,
    GPIO_PIN_7 = 0x0080,
    GPIO_PIN_8 = 0x0100,
    GPIO_PIN_9 = 0x0200,
    GPIO_PIN_10 = 0x0400,
    GPIO_PIN_11 = 0x0800,
    GPIO_PIN_12 = 0x1000,
    GPIO_PIN_13 = 0x2000,
    GPIO_PIN_14 = 0x4000,
    GPIO_PIN_15 = 0x8000
} GPIO_PIN; 

typedef enum{
    LOW = 0,
    HIGH = 1
} STATUS;

void digitalWrite(GPIO_PIN PIN, STATUS STATE){
    if (STATE)
    {
        PORT_A |= PIN;
    }
    else
    {
        PORT_A &= ~PIN;
    }
}

void blinkLED (GPIO_PIN PIN)
{
    for (int i = 0; i < 1000; i ++)
    {
        PORT_A |= PIN;

    }  
    for (int i = 0; i < 1000; i++)
    {
        PORT_A &= ~PIN;
    }
}

int main(int argc, char const *argv[])
{
    GPIO_PIN PIN;
    STATUS STATE;
    digitalWrite(GPIO_PIN_3, HIGH);
    blinkLED(GPIO_PIN_3);
    return 0;
}