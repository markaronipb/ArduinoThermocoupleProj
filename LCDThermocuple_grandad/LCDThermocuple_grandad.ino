// include the thermocouple library code
#include "max6675.h"
// include the lcd library code:
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // include the lcd library code;

// define thermocouple pins for 4 inputs, could use common CLK and CS pins but wired it wrong, reversed 1 and 3 so they fit better on tank. 4 not used.
const int ktc1SO = 37, ktc1CLK = 41, ktc1CS = 39;
const int ktc2SO = 43, ktc2CLK = 47, ktc2CS = 45;
const int ktc3SO = 49, ktc3CLK = 53, ktc3CS = 51;
const int ktc4SO = 31, ktc4CLK = 35, ktc4CS = 33;
// create special degree C character
byte degc[8] = {B10000,B00111,B01000,B01000,B01000,B01000,B00111,B00000};
const int delaytime=350; //this is the delay between moves in ms

// initialize 1 instances of the ktc
MAX6675 ktc1(ktc1CLK, ktc1CS, ktc1SO);
MAX6675 ktc2(ktc2CLK, ktc2CS, ktc2SO);
MAX6675 ktc3(ktc3CLK, ktc3CS, ktc3SO);
//MAX6675 ktc4(ktc4CLK, ktc4CS, ktc4SO);
int x = 0;

// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
////////////////// set up the LCD's number of columns and rows:///////////////////
  lcd.init();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0,degc);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Grandad's version");
}
void loop() {
   delay(500);
  float Temp[] = {ktc1.readCelsius(),ktc2.readCelsius(),ktc3.readCelsius(),0};
   int Col[] = {0,0,0,0};
   int Row[] = {0,1,2,3};
   x = 0;
   while(x <= 3){
    lcd.setCursor(Col[x],Row[x]);
    lcd.print(x + 1);
    lcd.print(":");
    lcd.print(String(Temp[x],1));
    lcd.write(0);
    lcd.print("    ");
    x = x + 1;
   }
 
}



      
