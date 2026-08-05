/********************************/
/*        I2C_SUPPORT.C         */
/********************************/

#include <stdio.h>                      // Include the standard in/out header file.
#include <p18f4620.h>                   // Include the header file for the PIC18F4620.

#include "I2C_Support.h"                // Include the local I2C_Support header file.
#include "I2C.h"                        // Include the local I2C header file.

                                        // Code values for the I2C devices.
#define ACCESS_CFG      0xAC            
#define START_CONV      0xEE
#define READ_TEMP       0xAA
#define CONT_CONV       0x02
#define ACK     1
#define NAK     0

                                        // External variables to be used througout the program.
extern unsigned char second, minute, hour, dow, day, month, year;
extern unsigned char setup_second, setup_minute, setup_hour, setup_day, setup_month, setup_year;
extern unsigned char alarm_second, alarm_minute, alarm_hour, alarm_date;
extern unsigned char setup_alarm_second, setup_alarm_minute, setup_alarm_hour;



unsigned char DS1621_Read_Temp()
{
char Device = 0x48;                 // Define "Device" address as 0x48.
char Cmd = READ_TEMP;               // Define "Cmd" as the pre-defined value for
//Reading Temperature (found on the data sheet).
char Data_Ret;                      // Declare a character variable as the value
//to return.
  I2C_Start();                      // Start I2C protocol
  I2C_Write((Device << 1) | 0);     // Device address
  I2C_Write(Cmd);                   // Send register address
  I2C_ReStart();                    // Restart I2C
  I2C_Write((Device << 1) | 1);     // Initialize data read
  Data_Ret = I2C_Read(NAK);         // Set Data_Ret to the value returned from
  //I2C_Read with NAK (0) as an argument.
  I2C_Stop();                       // Stop the I2C Protocol.
  return Data_Ret;                  // Return the Data_Ret value.
}

unsigned char DS1621_Read_Temp_Bad()
{
char Device = 0x49;                 // Define "Device" address as 0x49 (wrong address).
char Cmd = READ_TEMP;               // Define "Cmd" as the pre-defined value for
//Reading Temperature (found on the data sheet).
char Data_Ret;                      // Declare a character variable as the value
//to return.    
  I2C_Start();                      // Start I2C protocol
  I2C_Write((Device << 1) | 0);     // Device address
  I2C_Write(Cmd);                   // Send register address
  I2C_ReStart();                    // Restart I2C
  I2C_Write((Device << 1) | 1);     // Initialize data read
  Data_Ret = I2C_Read(NAK);         // Set Data_Ret to the value returned from
  //I2C_Read with NAK (0) as an argument.
  I2C_Stop();                       // Stop the I2C Protocol.
  return Data_Ret;                  // Return the Data_Ret value.
}

void DS1621_Init()
{
char Device = 0x48;                 // Define "Device" address as 0x48.
                                    // Call the sub-routine to write data.
    I2C_Write_Cmd_Write_Data (Device, ACCESS_CFG, CONT_CONV);
                                    // Call the sub-routine to write command only.
    I2C_Write_Cmd_Only(Device, START_CONV);
}

void DS3231_Read_Time()
{
char Device = 0x68;                 // Define "Device" address as 0x68.
char Address = 0x00;                // Define "Address" as 0 (location of seconds).
//char Data_Ret;                      // return value not needed for void data type.
  I2C_Start();                      // Start I2C protocol
  I2C_Write((Device << 1) | 0);     // DS3231 address Write mode
  I2C_Write(Address);               // Send register address
  I2C_ReStart();                    // Restart I2C
  I2C_Write((Device << 1) | 1);     // Initialize data read
  second = I2C_Read (ACK);          // Read value stored at 0x00, store into seconds and continue.
  minute = I2C_Read (ACK);          // Read value stored at 0x01, store into minutes and continue.
  hour = I2C_Read (ACK);            // Read value stored at 0x02, store into hours and continue.
  dow = I2C_Read (ACK);             // Read value stored at 0x03, store into dow and continue.
  day = I2C_Read (ACK);             // Read value stored at 0x04, store into day and continue.
  month = I2C_Read (ACK);           // Read value stored at 0x05, store into month and continue.
  year = I2C_Read (NAK);            // Read value stored at 0x06, store into year and end.
  I2C_Stop();                       // Stop the I2C Protocol.       
}

void DS3231_Setup_Time()
{
char Device = 0x68;                 // Define "Device" address as 0x68.
char Address = 0x00;                // Define "Address" as 0 (location of seconds).
                                    // Set pre-determined values for second, minute,
//hour, dow, day, month, and year.
second = 0;                         
minute = 0;
hour = 6;
dow = 1;
day = 4;
month = 0x11;
year = 0x25;
  I2C_Start();                      // Start I2C protocol
  I2C_Write((Device << 1) | 0);     // Device address Write mode
  I2C_Write(Address);               // Send register address
  I2C_Write(second);                // Initialize data read: Write to second (0x00).
  I2C_Write(minute);                // Write to minute (0x01).
  I2C_Write(hour);                  // Write to hour (0x02).
  I2C_Write(dow);                   // Write to dow (0x03).
  I2C_Write(day);                   // Write to day (0x04).
  I2C_Write(month);                 // Write to month (0x05).
  I2C_Write(year);                  // Write to year (0x06).
  I2C_Stop();                       // Stop the I2C Protocol.
}

