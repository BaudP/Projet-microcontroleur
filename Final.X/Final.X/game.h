/* 
 * File:   game.h
 * Author: Uza
 *
 * Created on 24 octobre 2018, 09:06
 */

#ifndef GAME_H
#define	GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "glcd.h"

#define Y 60
#define BALL_LENGHT 3           // Lenght of the ball
#define BALL_WIDTH 3
#define BAR_WIDTH 15
#define BAR_LENGTH 2

#define Trigger_Pulse1 LATC7     /* PORTC7 pin is connected to Trig pin of HC-SR04 */
#define Trigger_Pulse2 LATC0     /* PORTC0 pin is connected to Trig pin of HC-SR04 */

int move(int x, int* captor1, int* captor2);
void drawBar(int x);
void eraseBar(int x);
void generateDot(int* x, int* y, int* turn);
void eraseDot(int *x, int* y);
void drawDot(int *x, int* y);
void moveDot(int *x, int* y);
void scoreCounter(int* counter);
int isBallCatch(int *x, int* y, int* barX, int* counter);
void displayScore(int* counter);
void displayGameBegining();
void initGame(int *x, int* y, int* barX, int* counter);
void Trigger_Pulse_10us1();
void Trigger_Pulse_10us2();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* GAME_H */

