//  Modified for use with BuyDisplay RA8876 10.1" TFT 09-18-26 Warren Watson
// required libraries
//#include "ILI9341_t3.h"  // high speed display that ships with Teensy
#include "RA8876_Config_SPI.h"
#include <RA8876_t3.h>
#include "font_Arial.h"  // custom fonts that ships with ILI9341_t3.h
#include <font_ArialBold.h>
#include <RA8876_t4_Keypad.h>
#include <XPT2046_RA8876.h>

// For Teensy
//#define TFT_CS 10
//#define TFT_DC 9
//#define TFT_RST 8
//#define T_CS 0
//#define T_IRQ 1

#define CS_PIN  7
//XPT2046 ts(CS_PIN);
#define TIRQ_PIN  2
//XPT2046 ts(CS_PIN,TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling
//XPT2046 ts(CS_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

RA8876_t3 Display = RA8876_t3(RA8876_CS, RA8876_RESET); //Using standard SPI pins

// easy way to include fonts but change globally
#define FONT_BUTTON Arial_16_Bold  // font for keypad buttons


// you know the drill
//ILI9341_t3 Display(TFT_CS, TFT_DC, TFT_RST);

//XPT2046_Touchscreen Touch(T_CS, T_IRQ);
XPT2046 Touch(CS_PIN, TIRQ_PIN);


// create some keypad objects
NumberPad MyNumberPad(&Display, &Touch);

// you will probably need to calibrate your screen, these are coordinates of presses on display
uint16_t ScreenLeft = 1921, ScreenRight = 171, ScreenTop = 1974, ScreenBottom = 70;
//uint16_t ScreenLeft = 1921, ScreenRight = 1974, ScreenTop = 171, ScreenBottom = 70;

void setup() {
/*
  Serial.begin(9600);

  // fire up the display
  Display.begin();

  Display.setRotation(3);

  Touch.begin();
  Touch.setRotation(3);

  Display.fillScreen(ILI9341_BLACK);
*/
  Serial.begin(115200);

#if defined(USE_SPI_47000000)
  Display.begin(47000000); // Max is 47000000 MHz (using short 3" wires)
#else
  Display.begin(); // default SPI clock speed is 30000000 MHz 
#endif
  Display.setRotation(0); // Landscape (480x320)
  Display.setOrigin(0,0);
  Display.fillScreen(0x0000);
  Display.setFont(Arial_14);
  Display.clearStatusLine(COLOR65K_BLACK);
  Touch.begin(Display.width(), Display.height());

  // Replace these for your screen module
  Touch.setCalibration(1921, 1974, 171, 70);

  MyNumberPad.init(COLOR65K_BLACK, COLOR65K_WHITE, COLOR65K_BLUE, COLOR65K_NAVY, COLOR65K_DARKGREY, COLOR65K_NAVY, COLOR65K_BLACK, FONT_BUTTON);
  MyNumberPad.setTouchLimits(ScreenRight, ScreenLeft, ScreenBottom, ScreenTop);

  // optional methods
  MyNumberPad.setDisplayColor(COLOR65K_CYAN, COLOR65K_DARKGREY);
  //MyNumberPad.useButtonIcon(true);  // want icons for action buttons? omit call or false for text.
  MyNumberPad.enableDecimal(true);   // disable / enable decimal point (enabled by default)
  MyNumberPad.enableNegative(true);  // disable / enable negative sign (enabled by default)
  MyNumberPad.setCornerRadius(5);
  MyNumberPad.setMinMax(3, 300);  // want bounds checks (disables OK button if out of range)?
                                  // use the value property to set the initial value if desired
  MyNumberPad.setInitialText("Height?");
  MyNumberPad.value = 3.14159;  // set initial value
  // MyNumberPad.hideInput();
}

void loop() {

  Display.fillScreen(COLOR65K_BLACK);
  MyNumberPad.getInput();

  Serial.print("Entered value ");
  Serial.println(MyNumberPad.value);
  // reset if needed
  // MyNumberPad.value = 0;
}
