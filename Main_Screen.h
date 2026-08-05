/********************************/
/*        MAIN_SCREEN.H         */
/********************************/

void Initialize_LCD_Screen(void);       // Sub-routine that initializes the LCD screen.

#define Flash_Y         150             // Y-coordinate of the Flash display.

#define TS_1            1               // Size of Normal Text.
#define TS_2            2               // Size of PED Text.


// colors
#define RD               ST7735_RED     // Define RD variable as LCD display's RED color.
#define BU               ST7735_BLUE    // Define BU variable as LCD display's BLUE color.
#define GR               ST7735_GREEN   // Define GR variable as LCD display's GREEN color.
#define CY               ST7735_CYAN    // Define CY variable as LCD display's CYAN color.
#define MA               ST7735_MAGENTA // Define MA variable as LCD display's MAGENTA color.
#define BK               ST7735_BLACK   // Define BK variable as LCD display's BLACK color.
#define WH               ST7735_WHITE   // Define WH variable as LCD display's WHITE color.


#define Circle_Size     20              // Size of Circle for Light
#define Circle_X        60              // Location of Circle
#define Circle_Y        80              // Location of Circle
#define Text_X          52              // X-coordinate of the Text
#define Text_Y          77              // Y-coordinate of the Text
