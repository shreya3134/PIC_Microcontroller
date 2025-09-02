// PIC18F45K22 - External Interrupt INT0 on RB0 toggles LED (RD0)
#pragma config FOSC = HSH
#pragma config WDTEN = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF

#include <xc.h>
#define _XTAL_FREQ 8000000UL

void __interrupt() isr(void) {
    if (INTCONbits.INT0IF) {
        LATDbits.LATD0 ^= 1;    // toggle LED
        INTCONbits.INT0IF = 0;  // clear flag
    }
}

void main(void) {
    // LED on RD0
    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0 = 0;

    // RB0 as input for INT0, enable pull-up for active-low button
    TRISBbits.TRISB0 = 1;
    INTCON2bits.RBPU = 0; // enable pull-ups
    WPUBbits.WPUB0 = 1;

    // Interrupt edge: falling edge (button press pulls low)
    INTCON2bits.INTEDG0 = 0; // interrupt on falling edge

    // Enable INT0
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0IE = 1;
    // Enable global interrupts
    RCONbits.IPEN = 0;       // use legacy (single priority) mode
    INTCONbits.GIE = 1;

    while (1) {
        // idle
    }
}
