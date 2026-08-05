/********************************/
/*           UTILS.H            */
/********************************/

void Init_ADC(void);                    // Sub-routine that initializes the ADC module.
void Init_UART(void);                   // Sub-routine that 
void Do_Beep(void);                     // Sub-routine that sounds a buzzer for 1 second
//then disables to buzzer for one second.
void Do_Beep_Good(void);
void Do_Beep_Bad(void);
void Activate_Buzzer(void);             // Sub-routine that activates the buzzer.
void Activate_Buzzer_4KHz(void);
void Activate_Buzzer_2KHz(void);
void Activate_Buzzer_500Hz(void);
void Deactivate_Buzzer(void);           // Sub-routine that deactivates the buzzer.
void Wait_Half_Second();                // Sub-routine that causes a 500ms delay.
void Wait_One_Sec();                    // Sub-routine that causes a 1 second delay.

void Wait_One_Sec_Soft(void);           // Sub-routine that uses internal clock to delay 1 sec.
void do_update_pwm(char);               // Sub-routine that updates the PWM module.
void Set_RGB_Color(char);               // Sub-routine that sets RGB color.
void Prog_ADCON0(char ch);              // Sub-routine that programs ADCON0.

void putch (char);                      // Sub-routine that must be included with the UART.
float Read_Volt(char);                  // Sub-routine that reads AN channel voltage.
unsigned int get_full_ADC();            // Sub-routine that uses ADC module.
char check_for_button_input();          // Sub-routine that checks for button input.
char bcd_2_dec (char);                  // Sub-routine that converts BCD to Decimal.
int  dec_2_bcd (char);                  // Sub-routine that converts Decimal to BCD.
