/********************************/
/*        MAIN_SCREEN.C         */
/********************************/

#include <stdio.h>                      // Include the standard in/out header file.
#include <stdlib.h>                     // Include the standard library header file.
#include <xc.h>                         // Include a generic device-specific header file.
#include <math.h>                       // Include the standard math header file.
#include <p18f4620.h>                   // Include the header file for the PIC18F4620.
#include <string.h>                     // Include the header file to manipulate strings.

#include "utils.h"                      // Include the utilities header file.
#include "Main_Screen.h"                // Include the local Main_Screen header file
//for the LCD display.
#include "main.h"                       // Include the local main header file.
#include "ST7735_TFT.h"                 // Include the header file for the LCD display.


char buffer[31];                        // general buffer for display purpose.
char *nbr;                              // general pointer used for buffer.
char *txt;                              // general pointer used for text.
char Timing_Txt[] = "SP24/1/01";        // Initialize Timing_Txt.



void Initialize_LCD_Screen(void)        // The sub-routine to initialize the screen.
{
    LCD_Reset();                        // Call the sub-routine to Reset the LCD screen.
    TFT_GreenTab_Initialize();          // Initialize the LCD with the GreenTab option.
    fillScreen(ST7735_BLACK);           // Fill the screen with the color Black.
  
    /* TOP HEADER FIELD */
    txt = buffer;                       // Place the buffer array into "txt".

    strcpy(txt, "LAB 11 ");             // Copy the string "LAB 11 " into the array
    //which txt is holding.
                                        // Call the subroutine that will draw text
    //onto the LEC display.
    drawtext(50, 2, txt, ST7735_WHITE, ST7735_BLACK, TS_1);

    if (Semester == 0)                  // Set the first two characters to SP for Spring.
     {
        Timing_Txt[0] = 'S';  
        Timing_Txt[1] = 'P';         
     }
    else                               // Or Set the first two characters to FA for Fall.
     {
        Timing_Txt[0] = 'F';   
        Timing_Txt[1] = 'A';       
     }
                                        // Set other characters to Year,
    //Session number, and table number.
     Timing_Txt[2] = Year/10 + '0';
     Timing_Txt[3] = Year%10 + '0';
     Timing_Txt[5] = Session_Number%10 + '0';  
     Timing_Txt[7] = Table_Number/10 + '0';
     Timing_Txt[8] = Table_Number%10 + '0'; 
                                        // Display the Timing_Txt characters onto
     //the LCD screen.
     drawtext(1, Flash_Y, Timing_Txt, ST7735_WHITE, ST7735_BLACK, TS_1);
}


