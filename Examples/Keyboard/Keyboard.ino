//  Modified for use with BuyDisplay RA8876 10.1" TFT 09-18-26 Warren Watson
// required libraries
#include "RA8876_Config_SPI.h"
#include <RA8876_t3.h>
#include "font_Arial.h"  // custom fonts that ships with ILI9341_t3.h
#include <font_ArialBold.h>
#include <RA8876_t4_Keypad.h>
#include <XPT2046_RA8876.h>

#define CS_PIN  7
//XPT2046 ts(CS_PIN);
#define TIRQ_PIN  2
//XPT2046 ts(CS_PIN,TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling
//XPT2046 ts(CS_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

RA8876_t3 Display = RA8876_t3(RA8876_CS, RA8876_RESET); //Using standard SPI pins

// easy way to include fonts but change globally
#define FONT_BUTTON Arial_16  // font for keypad buttons
uint16_t ScreenLeft = 1921, ScreenRight = 171, ScreenTop = 1974, ScreenBottom = 70;

XPT2046 Touch(CS_PIN, TIRQ_PIN);

Keyboard MyKeyboard(&Display, &Touch);

void setup() {
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

  // simulate a good old fashioned keyboard
  MyKeyboard.init(COLOR65K_BLACK, COLOR65K_WHITE, COLOR65K_BLUE, COLOR65K_NAVY, COLOR65K_DARKGREY, COLOR65K_NAVY, COLOR65K_BLACK, FONT_BUTTON);
  MyKeyboard.setTouchLimits(ScreenRight, ScreenLeft, ScreenBottom, ScreenTop);
  // optional methods
  // max input characters is controlled by in the .h file
  // #define MAX_KEYBOARD_CHARS 18
  // change input display color
  MyKeyboard.setDisplayColor(COLOR65K_WHITE, COLOR65K_BLUE);
  // want rounded corners?
  // MyKeyboard.setCornerRadius(3);

  // Set initial instructions
  // MyKeyboard.setInitialText("IP 111.222.333.444");

  // MyKeyboard.hideInput(); // for hidden password input
  // MyKeyboard.setInitialText("Password");

  // optional to populate the input box
  //  strcpy(MyKeyboard.data, "TEXT");
}


void loop() {

  MyKeyboard.getInput();
  Serial.print("Password is: ");
  Serial.println(MyKeyboard.data);
}
