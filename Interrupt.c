/********************************/
/*          INTERRUPT.C         */
/********************************/

#include <xc.h>                         // Include a generic device-specific header file.
#include <p18f4620.h>                   // Include the header file for the PIC18F4620.
#include "Interrupt.h"                  // Include the header file for interrupts.

unsigned char bit_count;                // Declare an unsigned character for the bit_count variable.
unsigned int Time_Elapsed;              // Declare an unsigned integer for the Time_Elapsed variable.

unsigned long long Nec_code;            // Declare Nec_code to be an unsigned long long variable.
unsigned char Nec_State = 0;            // Initialize the unsigned character variable Nec_State to 0.

extern char Nec_Button;                 // Declare an external character variable Nec_Button.
extern short Nec_OK;                    // Declare an external short variable as Nec_OK.

void Init_Interrupt()
{
    INTCON3bits.INT1IF = 0;             // Clear external interrupt INT1IF
    INTCON2bits.INTEDG1 = 0;            // Edge programming for INT 1 falling edge H to L
    INTCON3bits.INT1IE = 1;             // Enable external interrupt INT1IE

    TMR1H = 0;                          // Reset Timer1
    TMR1L = 0;                          //
    PIR1bits.TMR1IF = 0;                // Clear timer 1 interrupt flag
    PIE1bits.TMR1IE = 1;                // Enable Timer 1 interrupt
    INTCONbits.PEIE = 1;                // Enable Peripheral interrupt
    INTCONbits.GIE = 1;                 // Enable global interrupts
}

void Enable_INT_Interrupt()
{
    INTCON3bits.INT1IE = 1;             // Enable external interrupt
    INTCON2bits.INTEDG1 = 0;            // Edge programming for INT1 falling edge
}    

void interrupt high_priority chkisr()   // High-Priority Interrupt Routine @ 0x000008.
{
                                        // Branch to TIMER1_isr if TMR1IF bit is set to 1.
    if (PIR1bits.TMR1IF == 1) TIMER1_isr();
                                        // Branch to INTx_isr if the INT1IF bit
    //(only interrupt 1 is used) is set to 1.
    if (INTCON3bits.INT1IF == 1) INTx_isr();
}

void TIMER1_isr(void)
{
    Nec_State = 0;                      // Reset decoding process
    INTCON2bits.INTEDG1 = 0;            // Edge programming for INT 1 falling edge
    T1CONbits.TMR1ON = 0;               // Disable T1 Timer
    PIR1bits.TMR1IF = 0;                // Clear interrupt flag
}

void Reset_Nec_State()
{
    Nec_State = 0;                      // Clear Nec_State.
    T1CONbits.TMR1ON = 0;               // Clear TMR1ON bit (turn off TMR1).
}

void INTx_isr(void)
{
    INTCON3bits.INT1IF = 0;             // Clear external interrupt INT2IF
    
    if (Nec_State != 0)                 // Conditional statement that runs the following
    //code if Nec_State does not equal 0.
    {
                                        // Store Timer1 value
        Time_Elapsed = (TMR1H << 8) | TMR1L;
        TMR1H = 0;                      // Reset Timer1
        TMR1L = 0;
    }
    
    switch(Nec_State)                   // Switch statement for Nec_State:
    {
        case 0 :                        // When Nec_State == 0:
        {
            TMR1H = 0;                  // Reset Timer1
            TMR1L = 0;                  //
            PIR1bits.TMR1IF = 0;        // Clear Timer 1 Interrupt Flag.
            T1CON = 0x90;               // Program Timer1 mode with count = 1usec using System clock running at 8Mhz
            T1CONbits.TMR1ON = 1;       // Enable Timer 1
            bit_count = 0;              // Force bit count (bit_count) to 0
            Nec_code = 0;               // Set Nec_code = 0
            Nec_State = 1;              // Set Nec_State to state 1
			PORTE = Nec_State;          // Output Nec_State to PORTE.
            INTCON2bits.INTEDG1 = 1;    // Change Edge interrupt of INT 1 to Low to High.          
            break;
        }
        
        case 1 :                        // When Nec_State == 1:
        {
                                        // Conditional statement runs the following
            //code if the expected time delay is found.
            if (Time_Elapsed > 8500 && Time_Elapsed < 9500)
            {
                Nec_State = 2;          // Set Nec_State to 2.
                PORTE = Nec_State;      // Output the Nec_State value to PORTE.
            }
            else                        // If the delay is not within expected bounds:
            {
                Reset_Nec_State();      // We have an error, reset Nec_State.
            }
            INTCON2bits.INTEDG1 = 0;    // Change Edge interrupt of INT 1 to High to Low.
            break;
        }
        
        case 2 :                        // When Nec_State == 2:
        {
                                        // Conditional statement runs the following
            //code if the expected time delay is found.
            if (Time_Elapsed > 4000 && Time_Elapsed < 5000)
            {
                Nec_State = 3;          // Set Nec_State to 3.
                PORTE = Nec_State;      // Output the Nec_State value to PORTE.
            }
            else                        // If the delay is not within expected bounds:
            {
                Reset_Nec_State();      // We have an error, reset Nec_State.
            }
            INTCON2bits.INTEDG1 = 1;    // Change Edge interrupt of INT 1 to Low to High.
            break;
        }
        
        case 3 :                        // When Nec_State == 3:
        {
                                        // Conditional statement runs the following
            //code if the expected time delay is found.
            if (Time_Elapsed > 400 && Time_Elapsed < 700)
            {
                Nec_State = 4;          // Set Nec_State to 4.
                PORTE = Nec_State;      // Output the Nec_State value to PORTE.
            }
            else                        // If the delay is not within expected bounds:
            {
                Reset_Nec_State();      // We have an error, reset Nec_State.
            }
            INTCON2bits.INTEDG1 = 0;    // Change Edge interrupt of INT 1 to High to Low.
            break;
        }
        
        case 4 :                        // When Nec_State == 4:
        {
                                        // Conditional statement runs the following
            //code if the expected time delay is found.
            if (Time_Elapsed > 400 && Time_Elapsed < 1800)
            {
                                        // Begin by shifting Nec_code to the left by 1.
                Nec_code = Nec_code << 1;
                
                if (Time_Elapsed > 1000)// If the delay is larger than 1000 (1ms).
                {
                    Nec_code++;         // Add 1 to Nec_code (logic 1).
                }                       // Do nothing ifTime_Elapsed < 1000 (logic 0).
                
                bit_count++;            // Increment bit count.
                
                if (bit_count > 31)     // Conditional statement will run the
                //following code if bit_count has reached 32.
                {
                                        // Set the variable Nec_Button to the
                    //shifted-right-by-8 value of Nec_code (non-inverted command byte).
                    Nec_Button = Nec_code >> 8;
                    
                    Nec_State = 0;      // Clear Nec_State.
                    PORTE = Nec_State;  // Output the value of Nec_State to PORTE.
                    Nec_OK = 1;         // Set Nec_OK status flag to 1.
                                        // Disable INT1 interrupt.
                    INTCON3bits.INT1IE = 0;
                }
                else                    // Conditional statement will run the
                //following code if bit_count has yet to reach 32.
                {
                    Nec_State = 3;      // Set Nec_State to 3.
                    PORTE = Nec_State;  // Output the Nec_State value to PORTE.
                } 
            }
            else                        // If the delay is not within expected bounds:
            {
                Reset_Nec_State();      // We have an error, reset Nec_State.
            }
            INTCON2bits.INTEDG1 = 1;    // Change Edge interrupt of INT 1 to Low to High.
            break;
        }
    }
}

