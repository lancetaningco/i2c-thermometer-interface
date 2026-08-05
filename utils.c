/********************************/
/*           UTILS.C            */
/********************************/

#include <stdio.h>                      // Include the standard in/out header file.
#include <stdlib.h>                     // Include the standard library header file.
#include <xc.h>                         // Include a generic device-specific header file.
#include <p18f4620.h>                   // Include the header file for the PIC18F4620.

#include "utils.h"                      // Include the utilities header file.
#include "Main_Screen.h"                // Include the local Main_Screen header file
//for the LCD display.
#include "main.h"                       // Include the local main header file.
#include "ST7735_TFT.h"                 // Include the header file for the LCD display.

extern char found;                      // 
extern char Nec_code1;                  // 
extern short nec_ok;                    // 
extern char array1[21];                 // 
extern char duty_cycle;                 // 


void Init_ADC()
{
    ADCON0 = 0x01;                      // Turn ON the ADC module.
    ADCON1 = 0x0E;                      // Set AN0 to be the only analog pin.
    ADCON2 = 0xA9;                      // 
}

void Init_UART(void)
{
                                        // Initialize the UART module.
    OpenUSART (USART_TX_INT_OFF & USART_RX_INT_OFF &
    USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX &
    USART_BRGH_HIGH, 25);
    OSCCON = 0x70;                      // 
}

void putch (char c)
{
    while (!TRMT);                      // While the program is not terminated:
    TXREG = c;                          // Set the transmission register to character "c".
}

void Wait_One_Sec()                     //creates one second delay and blinking asterisk
{
    Wait_Half_Second();                 // Wait for half second (or 500 msec)
    Wait_Half_Second();                 // Wait for half second (or 500 msec)

}
void Do_Beep(void)
{
    Activate_Buzzer();                  // Call the subroutine that activates the buzzer.
    Wait_One_Sec();                     // Call the subroutine that delays the program
    //by 1 second.
    Deactivate_Buzzer();                // Call the subroutine that deactivates the buzzer.
    Wait_One_Sec();                     // Call the subroutine that delays the program
    //by 1 second.
}


void Do_Beep_Good(void)
{
										// to be added in later lab

}

void Do_Beep_Bad(void)
{
										// to be added in later lab

}

void Activate_Buzzer(void)
{
    PR2 = 0b11111001 ;                  // Set PR2 register to 0xF9
    T2CON = 0b00000101 ;                // Set T2CON register to 0x05
    CCPR2L = 0b01001010 ;               // Set CCPR2L register to 0x4A
    CCP2CON = 0b00111100 ;              // Set CCP2CON register to 0x3C
}

void Activate_Buzzer_500Hz(void)
{
										// to be added in later lab
}

void Activate_Buzzer_2KHz(void)
{
										// to be added in later lab
}

void Activate_Buzzer_4KHz(void)
{
										// to be added in later lab
}

void Deactivate_Buzzer(void)
{
    CCP2CON = 0x0;                      // Clear the CCP2CON register.
	PORTCbits.RC1 = 0;                  // Clear Port C bit 1.
}

  
void Wait_Half_Second()
{
    T0CON = 0x03;                       // Timer 0, 16-bit mode, prescaler 1:16.
    TMR0L = 0xDB;                       // set the lower byte of TMR.
    TMR0H = 0x0B;                       // set the upper byte of TMR.
    INTCONbits.TMR0IF = 0;              // clear the Timer 0 flag.
    T0CONbits.TMR0ON = 1;               // Turn on the Timer 0.
    while (INTCONbits.TMR0IF == 0);     // wait for the Timer Flag to be 1 for done.
    T0CONbits.TMR0ON = 0;               // turn off the Timer 0.
}


void Wait_One_Sec_Soft(void)
{
    for (int k=0;k<0xffff;k++);         // Delay with a "for" loop.
}

void do_update_pwm(char duty_cycle) 
{ 
                                        // to be added in later lab
}

void Set_RGB_Color(char color)
{
                                        // to be added in later lab
}

float Read_Volt(char ADC_Channel)
{
	ADCON0 = ADC_Channel * 4 + 1;       // Turn on the ADC module and set the pin of
    //the channel that needs to read from.
	int nStep = get_full_ADC();         // Place the result of the ADC module into an
    //integer variable.
    float volt = nStep * 5 /1024.0;     // Calculate the voltage at the selected channel.
	return (volt);                      // Return the floating point value for the voltage.
}

unsigned int get_full_ADC(void)
{
unsigned int result;                    // Declare a variable to place the result into.
   ADCON0bits.GO=1;                     // Start Conversion.
   while(ADCON0bits.DONE==1);           // Wait for conversion to be completed.
   result = (ADRESH * 0x100) + ADRESL;  // Combine upper byte and lower byte
   //into result.
   return result;                       // return the result.
}

char check_for_button_input(void)
{ 
										// to be added in later lab
}

char bcd_2_dec (char bcd)
{
    int dec;                            // Declare an integer variable for decimal value.
                                        // Mask the lower 4 bits of the BCD value
    //and add the result to 10 x (BCD value / 16).
    dec = ((bcd >> 4) * 10) + (bcd & 0x0f);
    return dec;                         // Return the resulting decimal value.
}

int dec_2_bcd (char dec)
{
    int bcd;                            // Declare an integer variable for BCD value.
                                        // Take Modulo 10 of the decimal value and
    //add the result to 16 x (Decimal value / 10).
    bcd = ((dec / 10) << 4) + (dec % 10);
    return bcd;                         // Return the resulting BCD value.
}

