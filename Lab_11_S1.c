/*************************************************/
/*                MAIN SOURCE FILE               */
/*************************************************/

#include <stdio.h>                      // Include the standard in/out header file.
#include <stdlib.h>                     // Include the standard library header file.
#include <xc.h>                         // Include a generic device-specific header file.
#include <math.h>                       // Include the standard math header file.
#include <p18f4620.h>                   // Include the header file for the PIC18F4620.
#include <usart.h>                      // Include the USART header file to output
//to Terra Term.
#include <string.h>                     // Include the header file to manipulate strings.

#include "main.h"                       // Include the local main header file.
#include "ST7735_TFT.h"                 // Include the header file for the LCD display.
#include "Interrupt.h"                  // Include the header file for interrupts.
#include "utils.h"                      // Include the utilities header file.
#include "Main_Screen.h"                // Include the local Main_Screen header file
//for the LCD display.
#include "I2C.h"                        // Include the local header file for the I2C bus.
#include "I2C_Support.h"                // Include the local header file for I2C support.

char tempSecond = 0xff;                 // Define a char variable "tempSecond" as 0xFF.
char second = 0x00;                     // Initialize second to 0.
char minute = 0x00;                     // Initialize minute to 0.
char hour = 0x00;                       // Initialize hour to 0.
char dow = 0x00;                        // Initialize dow to 0.
char day = 0x00;                        // Initialize day to 0.
char month = 0x00;                      // Initialize month to 0.
char year = 0x00;                       // Initialize year to 0.
                                        // Declaring variables for setup.
char setup_second, setup_minute, setup_hour, setup_day, setup_month, setup_year;
                                        // Declaring variables for alarm.
char alarm_second, alarm_minute, alarm_hour, alarm_date;
                                        // Declaring variables for setup_alarm.
char setup_alarm_second, setup_alarm_minute, setup_alarm_hour;
                                        

#pragma config OSC = INTIO67            // Set RA6 and RA7 to general purpose I/O pins.
#pragma config WDT = OFF                // Turn off the Watchdog Timer.
#pragma config LVP = OFF                // Turnm off Low-Voltage Programming.
#pragma config BOREN = OFF              // Turn off the Brown-Out Reset option.


#define _XTAL_FREQ  8000000             // Set operation for 8 Mhz


short Nec_OK = 0;                       // Declare a short variable for Nec_OK (status flag).
char Nec_Button;                        // Declare a character variable for Nec_Button (Command Byte).
extern unsigned long long Nec_code;     // 
                                        // The array that contains the command
//codes for the buttons.
char array1[21]={0xa2, 0x62, 0xe2,
                0x22, 0x2, 0xc2,
                0xe0, 0xa8, 0x90,
                0x68, 0x98, 0xb0,
                0x30, 0x18, 0x7a,
                0x10, 0x38, 0x5a,
                0x42, 0x4a, 0x52};
                                        // The array that contains the controller
//button characters.
char txt1[21][4] =  {"CH-\0"," CH\0","CH+\0",
                     "|<<\0",">>|\0",">||\0",
                     " - \0"," + \0"," EQ\0",
                     " 0 \0","100\0","200\0",
                     " 1 \0"," 2 \0"," 3 \0",
                     " 4 \0"," 5 \0"," 6 \0",
                     " 7 \0"," 8 \0"," 9 \0"};
                                        // The array that contains the different
//colors to be used by the LCD display.
char color[21]={RD,RD,RD,CY,CY,GR,BU,BU,MA,WH,WH,WH,WH,WH,WH,WH,WH,WH,WH,WH,WH};

                                        // Define the list of variables as numbers
//starting at OFF = 0.
typedef enum {OFF,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE};
                                        // The array that contains the enumerated
//color names to output to the LEDs.
char color2[21] =  {RED, RED, RED,
                    CYAN, CYAN, GREEN,
                    BLUE, BLUE, MAGENTA,
                    WHITE, WHITE, WHITE,
                    WHITE, WHITE, WHITE,
                    WHITE, WHITE, WHITE,
                    WHITE, WHITE, WHITE};

                                        // The array for the KEY_PRESSED LED.
char nums[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void main()                             // The main routine.
{
    Init_UART();                        // Initialize the UART module.
    OSCCON = 0x70;                      // 8 Mhz
    nRBPU = 0;                          // Enable PORTB internal pull up resistor
    TRISA = 0;                          // PORTA as output
    TRISB = 0x02;                       // Set bit 1 of PORTB as input, the rest as output.
    TRISC = 0x00;                       // PORTC as output
    TRISD = 0x00;                       // PORTD as output
    TRISE = 0x00;                       // PORTE as output
    ADCON1 = 0x0F;                      // Set all AN pins to Digital
 
    PORTA = 0x00;                       // Clear Ports A, B, and C.
    PORTB = 0x00;
    PORTC = 0x00;
    
    Initialize_LCD_Screen();            // Initialize the LCD screen by calling
    //the function that does this.
    I2C_Init(100000);                   // Initialize the I2C interface.
    DS1621_Init();                      // Initialize the Temperature sensor (DS1621).
    Init_Interrupt();                   // Initialize interrupts.

    Nec_code = 0x0;                     // Initialize Nec_code to 0.
/*      PART 3      */
//    DS3231_Setup_Time();                  // Initialize the external clock values.
/********************/
   
    while(1)                            // Forever Loop.
    {
/*      PART 1      */
//                                          // Calculate ambient temperature in Celsius.                                            
//    signed char tempC = DS1621_Read_Temp();
//                                          // Call a function that will send a
//     //request to an address that does not match with the temperature sensor.
//    signed char tempC1 = DS1621_Read_Temp_Bad();
//                                          // Convert Celsius Temperature to Fahrenheit.
//    signed char tempF = (tempC * 9 / 5) + 32;
//                                          // Output Temperature in C and F to UART module.
//    printf (" Temperature = %d degreesC = %d degreesF\r\n", tempC, tempF); 
//    Wait_One_Sec_Soft();                  // Delay for one second (not using external clock).
/********************/
    
/*      PART 2      */
    
    DS3231_Read_Time();                 // Call a command to send a read request
    //to the external clock, updating the variables for second, minute, etc.
    if(tempSecond != second)            // Conditional statement to update
    //the UART output every second using the external clock.
    { 
        tempSecond = second;            // Redefine the tempSecond variable
        //with the updated value of second.
        char tempC = DS1621_Read_Temp();// Calculate ambient temperature in Celsius.
                                        // Convert Temperature from Celsius to Fahrenheit.
        char tempF = (tempC * 9 / 5) + 32;
                                        // Output Time/Day/Month/Year to UART module.
        printf ("%02x:%02x:%02x %02x/%02x/%02x",hour,minute,second,month,day,year);
                                        // Output Temperature in C and F to UART module. 
        printf (" Temperature = %d degreesC = %d degreesF\r\n", tempC, tempF);
    } 
/********************/

         if (Nec_OK == 1)               // If the button press sequence matches
         //the expected sequence:
        {
            Nec_OK = 0;                 // Clear the OK status flag.
            Enable_INT_Interrupt();     // Call the function to enable interrupts
            //and set the edge detection to High-to-Low.
                                        // Output the Nec_Button value to UART module.
            printf ("NEC_Button = %x \r\n", Nec_Button);

            char found = 0xff;          // Initialize "found" variable to 0xFF.
            
                                        // Conditional statement to assign an index
            //value to "found" depending on the value of Nec_Button.
            for (char i = 0; i < 21; i++)
            {
                if (array1[i] == Nec_Button)
                {
                    found = i;          // Set "found" equal to the index of array1
                    //if Nec_Button is equal to a set command byte.
                }
            }
            
/*      PART 4      */
            // Check button pressed 
            if (found == 7)             // Check for a specific button (+) and
            //run the enclosed code if the button is pressed.
            {                           
                DS3231_Setup_Time();    // Reset time by calling the setup function.
            }
/********************/
            
            if (found != 0xff)          // Conditional statement to check for a unique
            //"found" value (0 - 20).
            {
                                        // Output the Key location to UART module.
				printf ("Key Location = %d \r\n\n", found);
                                        // Fills a colored circle on the LCD Screen.
                fillCircle(Circle_X, Circle_Y, Circle_Size, color[found]);
                                        // Draws a white circle as a border.
                drawCircle(Circle_X, Circle_Y, Circle_Size, ST7735_WHITE);
                                        // Draws the button text onto the LCD screen in black.
                drawtext(Text_X, Text_Y, txt1[found], ST7735_WHITE, ST7735_BLACK,TS_1);
   
			// add code to output color for the RGB LEDS
                PORTA = 0;              // Clears LEDs D1, D2, and D3
                PORTB = 0;
                                        // Sets the KEY_PRESSED LED based on "found"
                PORTCbits.RC0 = nums[found];
                
                char LED_num;           // Place the LED number in a character variable
                                        // Create Mask arrays for Port A depending
                //on the LED_num value.
                char PORTA_maskArray[3] = {0x00,0x07,0x38};
                
                                        // Create Mask arrays for Port B depending
                //on the LED_num value.
                char PORTB_maskArray[3] = {0x38,0x00,0x00};
                
                                        // Determine "LED_num" based on "found".
                if (found >= 0 && found <= 2)
                {
                    LED_num = 0;        // Set LED_num to 0 for buttons 1-3.
                }
                else if (found >= 3 && found <= 8)
                {
                    LED_num = 1;        // Set LED_num to 1 for buttons 4-9.
                }
                else
                {
                   LED_num = 2;         // Set LED_num to 2 for buttons 10-21.
                }
                char PortA_Color;       // Declare a character variable to store
                //the value to set PORTA to.
                char PortB_Color;       // Declare a character variable to store
                //the value to set PORTB to.
                
                if (LED_num == 0)       // D1 is at Port B bits 3-5
                {
                                        // Define PortA_Colors as a direct translation.
                PortA_Color = color2[found];
                                        // PortB_Colors must be shifted by 3 places for D1.
                PortB_Color = color2[found]<<3;
                }
                else if (LED_num == 1)  // D2 is at Port A bits 0-2
                {
                                        // Define PortA_Colors as a direct translation.
                PortA_Color = color2[found];
                                        // Define PortB_Colors as a direct translation.
                PortB_Color = color2[found];
                }
                else                    // D3 is at Port A bits 3-5
                {
                                        // PortA_Colors must be shifted by 3 places for D3.
                PortA_Color = color2[found]<<3;
                                        // Define PortB_Colors as a direct translation.
                PortB_Color = color2[found];
                }
                
                                        // Set Ports A and B to the specified number
                //based on the color and LED number.
                PORTA = PORTA_maskArray[LED_num] & PortA_Color;
                PORTB = PORTB_maskArray[LED_num] & PortB_Color;
                
			// add code to handle the KEY_PRESSED LED and do the buzzer sound
                KEY_PRESSED = 1;        // Activate the KEY_PRESSED LED.
                Activate_Buzzer();      // Activate the buzzer.
                Wait_One_Sec();         // Wait for one second.
                Deactivate_Buzzer();    // Deactivate the buzzer.
                KEY_PRESSED = 0;        // Turn off the KEY_PRESSED LED.
            }
        }
    }
}
