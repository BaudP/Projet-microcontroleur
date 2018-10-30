/* 
 * File:   sound.h
 * Author: Uza
 *
 * Created on 23 octobre 2018, 22:21
 */
#ifndef SOUND_H
#define	SOUND_H

/* Description:
*/

#define BUTTON 		PORTBbits.RB4
#define LINE_TAG 	PORTBbits.RB5
#define GREEN_LED 	LATD6
#define RED_LED 	LATD7
#define BUZZER_ON	T2CON|=0b00000100

#include <string.h>
#include <htc.h>
#define _XTAL_FREQ 8000000

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

extern void DelayMs(unsigned int delay);
extern void DelayUs(unsigned int delay);
extern void convert_hex_to_ascii(uint8_t ascii, uint8_t tab[2]);

enum{
		BUZZER_DELAY_XS=65280,
		BUZZER_DELAY_S=65025,
		BUZZER_DELAY_M=64770,
		BUZZER_DELAY_L=64515,
		BUZZER_DELAY_XL=64260,
		BUZZER_DELAY_XXL=61710,
		
		
};	

#define B 			0
#define DO4 		236
#define DO4_DIESE	225
#define RE4 		210
#define RE4_DIESE 	201
#define MI4 		189
#define FA4 		179
#define FA4_DIESE 	169
#define SOL4 		160
#define SOL4_DIESE 	150
#define LA4 		142
#define LA4_DIESE 	134
#define SI4 		127 // limite
#define DO5 		119 // hors freq du buzzer

#define DOUBLE_CROCHE	1
#define CROCHE			(2*DOUBLE_CROCHE)
#define NOIR			(4*DOUBLE_CROCHE)
#define BLANCHE			(8*DOUBLE_CROCHE)
#define RONDE			(16*DOUBLE_CROCHE)

// Variables
uint16_t buzzer_delay = 0;

// melody of a baseball homerun played after each goal
uint8_t baseball[7]={
    B,SOL4,DO4,MI4,SOL4, MI4, SOL4
};
//duration of each note
uint8_t baseball_r[7] = {
	DOUBLE_CROCHE,CROCHE,CROCHE,CROCHE,
	CROCHE,DOUBLE_CROCHE,BLANCHE
};

// extract of 'We are the Champions' by Queen played when someone reaches 5 goals
uint8_t champion[23]= {
    B,FA4,MI4,FA4,MI4,DO4,LA4,RE4,LA4,LA4_DIESE,DO4,FA4,SOL4,LA4,DO4,LA4,RE4,
    MI4,RE4
    
};
//duration of each note
uint8_t champion_r[23]= {
    DOUBLE_CROCHE,BLANCHE,CROCHE,CROCHE,NOIR,BLANCHE,CROCHE,CROCHE,
    BLANCHE,BLANCHE,BLANCHE,BLANCHE,CROCHE,CROCHE,NOIR,BLANCHE,CROCHE,
    CROCHE,BLANCHE

    
};

// Functions declarations
extern void init_board();
extern void buzz(uint16_t delay);
void init_buzzer();
extern void Play_Music(uint8_t tab[], uint8_t r[], uint8_t size);

#endif	/* SOUND_H */

