
// Configuration Bits
#pragma config FOSC = HSHP      // High-speed Oscillator
#pragma config WDTEN = OFF      // Watchdog Timer disabled
#pragma config LVP = OFF        // Low-Voltage Programming disabled

#include <xc.h>
#define _XTAL_FREQ 20000000  // 20 MHz Crystal Frequency

void main(void) {
    // Configure PORTD as output for LEDs
    TRISD = 0x00;     // All PORTD pins as output
    LATD = 0x00;      // Initialize LEDs OFF

    // Configure PORTB RB0 as input for Push Button
    TRISBbits.TRISB0 = 1;  // RB0 as input
    ANSELBbits.ANSB0 = 0;  // Disable analog on RB0
    LATBbits.LATB0 = 0;    // Clear output latch (just for safety)

    while(1) {
        // Blink LEDs
        LATD = 0xFF;       // All LEDs ON
        __delay_ms(500);   // 500 ms delay
        LATD = 0x00;       // All LEDs OFF
        __delay_ms(500);   // 500 ms delay

        // Check Push Button
        if(PORTBbits.RB0 == 0) { // Assuming button is active LOW
            LATD = 0xFF;         // Turn all LEDs ON while button pressed
        } else {
            LATD = 0x00;         // Turn all LEDs OFF when button released
        }
    }
}
