#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
/**
 * main.c
 */
int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;      // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x1F;            // SET PORTF PINS 4 PIN and 0 as digital enable
    GPIO_PORTF_DIR_R  = 0x0E;            // SET PORTF4 PIN AS INPUT USER SWITCH PIN
    GPIO_PORTF_PUR_R  = 0x11;            // PORTF4 and 0 IS PULLED UP

    while (1)
       {
           uint32_t sw1 = GPIO_PORTF_DATA_R & 0x10; // PF4 (SW1)
           uint32_t sw2 = GPIO_PORTF_DATA_R & 0x01; // PF0 (SW2)

           if ((sw1 == 0) && (sw2 == 0)) {
               // Both pressed -> Blue
               GPIO_PORTF_DATA_R = 0x04; // PF2 = Blue LED
           }
           else if (sw1 == 0) {
               // Only SW1 pressed -> Red
               GPIO_PORTF_DATA_R = 0x02; // PF1 = Red LED
           }
           else if (sw2 == 0) {
               // Only SW2 pressed -> Green
               GPIO_PORTF_DATA_R = 0x08; // PF3 = Green LED
           }
           else {
                       // No switch pressed -> all LEDs off
                       GPIO_PORTF_DATA_R = 0x00;
           }
}
}
