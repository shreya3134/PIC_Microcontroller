// PIC18F45K22 - LED Blink (GPIO + Config Bits)
// Osc: 8 MHz external HS crystal assumed
#pragma config FOSC = HSH      // HS oscillator, high-speed crystal/resonator
#pragma config WDTEN = OFF     // Watchdog Timer Enable (WDT disabled)
#pragma config LVP = OFF       // Single-Supply ICSP Enable bit (Disabled)
#pragma config PBADEN = OFF    // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)

#include <xc.h>
#define _XTAL_FREQ 8000000UL

void main(void) {
    // LED on RB0
    TRISBbits.TRISB0 = 0; // output
    LATBbits.LATB0 = 0;

    while (1) {
        LATBbits.LATB0 = 1; __delay_ms(500);
        LATBbits.LATB0 = 0; __delay_ms(500);
    }
}
