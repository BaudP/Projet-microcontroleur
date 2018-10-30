#include "init.h"

//Init the PIC18F device
void initMyPIC18F(void)
{
	// PORTA digital
	ADCON1 = 0x0F ;
	ADCON0 = 0;

	// set all ports as OUTPUTS
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
	TRISE = 0b00000011;

	// set port by port on "all zeros"
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
// make sure to have an empty LAST line in any *.c file (just hit an Enter)!

	PORTE = 0b00000011;

    ADCON1 = 0x0F;
    TRISC=0xFF;
    // Init the buzzer
	// Init PWM for buzzer (on RC2)
	TRISC2 = 0;
	TMR2IF = 0;
	TMR2 = 0;
	TMR2IE = 1;

	CCPR1L = 0x3C; // Buzzer power
	CCP1CON = 0b00001100;
	PR2 = 0xFF;
	T2CON = 0b00000011;
}
// make sure to have an empty LAST line in any *.c file (just hit an Enter)!


