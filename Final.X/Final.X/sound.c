#include "sound.h"

void buzz(uint16_t delay)
{
	buzzer_delay = delay;
	BUZZER_ON;
}

void init_buzzer()
{
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

	buzz(BUZZER_DELAY_XS); // stop automatically (interrupt on TMR2)
	__delay_ms(500);
    
}

void Play_Music(uint8_t tab[], uint8_t r[], uint8_t size)
{
	uint8_t i = 0;	
	uint16_t delay = 0;
	for (i=0;i<size;i++)
	{
		delay = r[i] * 100;     //duration of a note
		PR2 = tab[i];
		buzz(BUZZER_DELAY_XS); // stop automatically (interrupt on TMR2)
		unsigned int j;
        for(j=0;j<delay;j++) __delay_ms(1);
		PR2 = B;
		buzz(BUZZER_DELAY_XS); // stop automatically (interrupt on TMR2)
		
	}
}

