// PIC18F46K22 - 16x2 LCD (HD44780) in 8-bit mode
// Data lines D0..D7 -> RD0..RD7
// RS -> RB0, EN -> RB1, RW -> GND

#pragma config FOSC = HSHP
#pragma config WDTEN = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF

#include <xc.h>
#define _XTAL_FREQ 8000000UL

#define LCD_RS LATBbits.LATB0
#define LCD_EN LATBbits.LATB1

// Send a command to LCD
void LCD_Command(unsigned char cmd) {
    LCD_RS = 0;        // command mode
    LATD = cmd;        // put command on PORTD
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;
    __delay_ms(2);     // wait for execution
}

// Send a data byte (character) to LCD
void LCD_Data(unsigned char data) {
    LCD_RS = 1;        // data mode
    LATD = data;       // put data on PORTD
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;
    __delay_us(50);
}

// Initialize LCD
void LCD_Init(void) {
    // Configure pins
    TRISBbits.TRISB0 = 0; // RS output
    TRISBbits.TRISB1 = 0; // EN output
    TRISD = 0x00;         // PORTD all outputs

    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
    LATD = 0x00;

    __delay_ms(20);       // LCD power-up delay

    // Initialization commands
    LCD_Command(0x38); // Function set: 8-bit, 2 line, 5x8 dots
    LCD_Command(0x0C); // Display ON, Cursor OFF
    LCD_Command(0x01); // Clear display
    __delay_ms(2);
    LCD_Command(0x06); // Entry mode: Increment cursor
}

// Move cursor to row, col
void LCD_GotoXY(unsigned char row, unsigned char col) {
    unsigned char addr = (row == 0 ? 0x00 : 0x40) + col;
    LCD_Command(0x80 | addr);
}

// Print string
void LCD_Print(const char* s) {
    while (*s) LCD_Data(*s++);
}

// Main program
void main(void) {
    LCD_Init();
    LCD_GotoXY(0, 0);
    LCD_Print("Hello, world!");
    LCD_GotoXY(1, 0);
    LCD_Print("PIC18F46K22");
    while (1) { }
}
