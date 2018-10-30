
#include "game.h"
#include "sound.h"

//Display the introduction to the game
void displayGameBegining()
{
    glcd_SetCursor(18,3);
    glcd_WriteString("CATCH THE BALL",'a',1);
    __delay_ms(2000);
    glcd_FillScreen(0);
}

// Function to move the bar
int move(int x, int* captor1, int* captor2)
{
    //If the captor 1 is activated, the bar move to the right ...
    if( ((*captor1) == 1) && (x+BAR_WIDTH < 60))
    {
        (*captor1) = 0;
        eraseBar(x);
        x = x+5;
        drawBar(x);
    }
    
    //If the captor 2 is activated, the bar move to the left ...
    else if(((*captor2) == 1) && (x >= 5))
    {
        (*captor2) = 0;
        eraseBar(x);
        x = x-5;
        drawBar(x);
    }

    //If no captor is activated, then the bar doesn not move and we juste displey the bar.
    else
    {
        drawBar(x);
    }
    return x;
}

//Function to display the bar on screen
void drawBar(int x)
{
    int i, j;
    for(i=0; i<BAR_WIDTH; i++)
    {
        for(j=0; j<BAR_LENGTH; j++)
        {
            glcd_PlotPixel( i+x, j+Y, 0xFF);
        }
    }
}

//Function to erase the bar on screen before moving it
void eraseBar(int x)
{
    int i, j;
    for(i=0; i<BAR_WIDTH; i++)
    {
        for(j=0; j<BAR_LENGTH; j++)
        {
            glcd_PlotPixel( i+x, j+Y, 0x00);
        }
    }
}

//Function to generate the ball randomly on the screen
void generateDot(int* x, int* y, int* turn)
{
    (*turn) ++;
    glcd_PlotPixel( *x = rand()%64, *y, 0xFF);
            
}

//Function to display the ball
void drawDot(int *x, int* y)
{
    int i, j;
    for(i=0; i<BALL_WIDTH; i++)
    {
        for(j=0; j<BALL_LENGHT; j++)
        {
            glcd_PlotPixel( (*x)+i, (*y)+j, 0xFF);
        }
    }
}

//Function to erase the ball on the screen
void eraseDot(int *x, int* y)
{
    int i, j;
    for(i=0; i<BALL_WIDTH; i++)
    {
        for(j=0; j<BALL_LENGHT; j++)
        {
            glcd_PlotPixel( (*x)+i, (*y)+j, 0x00);
        }
    }
}

//Function to move the dot on screen
void moveDot(int* x, int* y)
{
    (*y) ++;
    drawDot(x, y);
}

//Function score to count the number of balls caught
void scoreCounter(int* counter)
{
    int value = *counter;
    value ++;
    *counter = value;
}

//Function to display the score on screen
void displayScore(int* counter)
{
    char score[10];
    
    sprintf(score,"%d", *counter);
    glcd_FillScreen(0);
    glcd_SetCursor(70,3);
    glcd_WriteString("SCORE:",'a',1);
    glcd_SetCursor(70,30);
    glcd_WriteString(score,'a',1);
    
    __delay_ms(500);
 
}

//Function to initialize the game when the player lost the game 
void initGame(int *x, int* y, int* barX, int* counter)
{
    
    eraseDot(x, y);
    x = NULL;
    *y = 2;
    __delay_ms(40);
}

//Functions to generate pulses
void Trigger_Pulse_10us1()
{
    Trigger_Pulse1 =1;
    __delay_us(10);
    Trigger_Pulse1 =0;
}

void Trigger_Pulse_10us2()
{
    Trigger_Pulse2 =1;
    __delay_us(10);
    Trigger_Pulse2 =0;
}

//Function that check if a ball has been caught or not
int isBallCatch(int *x, int* y, int* barX, int* counter)
{
    int barBeginX = *barX;
    int barEndX = (*barX) + BAR_WIDTH;
    int ballBeginX = *x;
    int ballEndX = (*x) + BAR_LENGTH;
    int ballEndY = (*y) + BAR_LENGTH;
    
    if(ballEndY == 60)                  //If the ball is on the ground, there are 2 possibilities ...
    {
        glcd_PlotPixel( 120, 25, 0xFF);
        
        // 1st possibility : the ball has been caught ...
        if((barBeginX <= ballBeginX) && (barEndX >= ballEndX))
        {
            scoreCounter(counter);       //We increment the score
            initGame(x, y, barX, counter);  
        }
        
        else
        {
            // We erase the screen
            glcd_FillScreen(0);
            glcd_SetCursor(18,3);
            *counter = 0;
            
            //We display a message and a music
            glcd_WriteString("PERDU ... :( ",'a',1);
            Play_Music(baseball, baseball_r, 7);
            
            int i =0;
            for (i=0; i<40 ; i++)
            __delay_ms(90);
            glcd_FillScreen(0);
            displayScore(counter);

            //We initialize the game for the next game
            initGame(x, y, barX, counter);   
        }
        return 1;
    }
   return 0; 
}

