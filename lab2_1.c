#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int main(void)
{
    SYSCTL_RCGC2_R |= 0x00000020;        // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // ALLOW CHANGES TO PF0-4
    GPIO_PORTF_DEN_R  = 0x1F;            // DIGITAL ENABLE
    GPIO_PORTF_DIR_R  = 0x0E;            // PF1-3 outputs (LEDs), PF0 & PF4 inputs (switches)
    GPIO_PORTF_PUR_R  = 0x11;            // Enable pull-ups on PF0 & PF4

    int count = 0;
    uint32_t prev_sw1 = 0x10;  // Previous state of SW1 (unpressed = 1)

    while (1)
    {
        uint32_t sw1 = GPIO_PORTF_DATA_R & 0x10; // Read PF4 (SW1)

        // Detect press event: previous high -> now low
        if ((prev_sw1 != 0) && (sw1 == 0))
        {
            if (count == 0) {
                GPIO_PORTF_DATA_R = 0x02; // Red
                count = 1;
            }
            else if (count == 1) {
                GPIO_PORTF_DATA_R = 0x04; // Blue
                count = 2;
            }
            else if (count == 2) {
                GPIO_PORTF_DATA_R = 0x08; // Green
                count = 0;               // Back to start
            }
        }

        prev_sw1 = sw1; // Update previous state
    }
}
