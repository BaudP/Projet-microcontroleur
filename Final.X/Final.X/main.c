/*
 * File:   main.c
 * Author: Uza
 *
 * Created on 24 octobre 2018, 09:02
 */


/*
 
 
 THIS PROJECT IS MADE BY :
        - Chloé HUNCK DE BOXTEL
        - Baoudoin PASTRE
        - Uza-Lara KARTHIGESU
 */
#include "main.h"

void delay_500ms()
{
    __delay_ms(90);
    __delay_ms(90);
    __delay_ms(90);
    __delay_ms(90);
    __delay_ms(90);
    __delay_ms(50);
   
}
void main (void)
{
    srand(time(NULL));
    initMyPIC18F();                 //Call the function that will init the PIC
    glcd_Init(GLCD_ON);             //Call the function that will init the GLCD
   
    
    
    /* This part concerns captors */ 
    
    //Variables used to evaluate the activation of a captor  
    float Distance1 = 100.0;
    int Time1;
    float Distance2 = 100.0;
    int Time2;
    
    OSCCON=0x72;/* use internal oscillator with * MHz frequency */
    
    TRISCbits.TRISC7=0;    /* RC7=TRIG=sortie CAPTEUR 1*/
    TRISCbits.TRISC6=1;    /*RC6=ECHO=entree  CAPTEUR 1*/
    
    TRISCbits.TRISC0=0;    /*RC0=TRIG=sortie CAPTEUR 2*/
    TRISCbits.TRISC1=1;    /*RC1=ECHO=entree  CAPTEUR 2*/

    Trigger_Pulse1 = 0;
    T1CON = 0x80;           /* enable 16-bit TMR1 Register,No pre-scale,use internal clock,Timer OFF */
    TMR1IF = 0;             /* make Timer1 Overflow Flag to '0' */
    TMR1=0;                 /* load Timer1 with 0*/
    
    Trigger_Pulse2 = 0;
    T3CON = 0x80;           /* enable 16-bit TMR1 Register,No pre-scale,use internal clock,Timer OFF */
    TMR3IF = 0;             /* make Timer1 Overflow Flag to '0' */
    TMR3=0;                 /* load Timer1 with 0*/
    
    //Variables used to check if a captor was activated to move the bar
    int captor1 = 0;
    int* captor1Activated = &captor1;
    
    int captor2 = 0;
    int* captor2Activated = &captor2;
    
    //Other variables
    int loop = 0;           
    int counterValue = 0;   //Score counter
    int* counter = &counterValue;   //Pointer to the score counter
    int x = 2;              //Position of the bar at the begining
    int* barX = &x;         //Pointer to the position of the bar
    int* ballX = NULL;      //Pointer to the position of the ball in X axis
    int yValue = 2;         //Position Y of the ball at the begining
    int* ballY = &yValue;   //Pointer to the position of the ball in Y axis
    int turn = 0;           //Number of games played by the player
    int* ptTurn = &turn;    //Pointer to the number of games played by the player
    
    displayGameBegining();
    glcd_Image();
    Play_Music(champion, champion_r, 23);
    
    drawBar(x);
    displayScore(counter);

    while(1)
    {      
        if(loop == 0)
        {
            generateDot(ballX, ballY, ptTurn);
            drawDot(ballX, ballY);
            loop++;
            __delay_ms(100);
        }

       if(isBallCatch(ballX, ballY, barX, counter))
        {
            loop = 0;
            __delay_ms(100);
            displayScore(counter);
        }

        else
        {
            eraseDot(ballX, ballY);
            moveDot(ballX, ballY);
            __delay_ms(100);
        }
   
        //To check the activation of the first captor
        Trigger_Pulse_10us1();                /* transmit at least 10 us pulse to HC-SR04 */
        while(PORTCbits.RC6==0);              /* wait for rising edge at Echo pin of HC-SR04 on sensor 1 or 2*/
        TMR1=0x00;                               /* Load Timer1 register with 0 */
        T1CONbits.TMR1ON=1;                   /* turn ON Timer1*/
        while(PORTCbits.RC6==1); /* wait for falling edge at Echo pin of HC-SR04 on sensor 1 or 2*/
        Time1 = TMR1;                         /* copy Time when echo is received from an object */
        T1CONbits.TMR1ON=0;                   /* turn OFF Timer1 */
        Distance1 = ((float)Time1/117.00);    /* distance = (velocity x Time)/2 */

        //To check the activation of the second captor
        Trigger_Pulse_10us2();                /* transmit at least 10 us pulse to HC-SR04 */
        while(PORTCbits.RC1==0);              /* wait for rising edge at Echo pin of HC-SR04 on sensor 1 or 2*/
        TMR3=0x00;                               /* Load Timer2 register with 0 */
        T3CONbits.TMR3ON=1;                   /* turn ON Timer2*/
        while(PORTCbits.RC1==1); /* wait for falling edge at Echo pin of HC-SR04 on sensor 1 or 2*/
        Time2 = TMR3;                         /* copy Time when echo is received from an object */
        T3CONbits.TMR3ON=0;                   /* turn OFF Timer2 */
        Distance2 = ((float)Time2/117.00);    /* distance = (velocity x Time)/2 */

        if(Distance1<4) //If we are close at most 4cm of the captor
        {
            //glcd_PlotPixel( 2, 2, 0xFF);//dessiner un point    
            *captor1Activated = 1; 
            x = move(x, captor1Activated, captor2Activated);
        }
        if(Distance2<4) //If we are close at most 4cm of the captor
        {
            *captor2Activated = 1; 
            x = move(x, captor1Activated, captor2Activated);
        } 
            x = move(x, captor1Activated, captor2Activated);
        }
        
}// end of the main function

// make sure to have an empty LAST line in any *.c file (just hit an Enter)!


