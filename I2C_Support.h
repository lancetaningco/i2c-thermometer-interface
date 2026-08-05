/********************************/
/*        I2C_SUPPORT.H         */
/********************************/

void DS1621_Init(void);                 // Sub-routine that initializes the
//Temperature Sensor.
void DS3231_Read_Time(void);            // Sub-routine that reads time from the
//External Clock.
void DS3231_Setup_Time(void);           // Sub-routine that loads pre-defined time and date
//values into the External Clock.
unsigned char DS1621_Read_Temp(void);   // Sub-routine that reads temperature from
//the Temperature Sensor.
