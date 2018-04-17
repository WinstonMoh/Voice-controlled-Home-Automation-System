#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x3F for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
        lcd.print("This is chepson");
        lcd.print("arduino is cool");
}

void loop()
{
	// Do nothing here...
}
