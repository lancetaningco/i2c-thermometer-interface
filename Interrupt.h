/********************************/
/*          INTERRUPT.H         */
/********************************/

void Init_Interrupt();                  // The subroutine that initializes interrupts.

void Enable_INT_Interrupt();            // The subroutine that enables Interrupts
//and sets Edge detection to High-to-Low.

                                        // High-priority Interrupt routine
//(At address 0x000008).
void interrupt  high_priority chkisr(void) ;
void INTx_isr(void);                    // The ISR that checks the states of INT0-INT2.
void TIMER1_isr(void);                  // The ISR for TIMER1.
void Reset_Nec_State();                 // The subroutine to reset Nec_State.
