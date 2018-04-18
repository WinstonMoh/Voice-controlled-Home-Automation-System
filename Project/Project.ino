/** 
  SENIOR DESIGN PROJECT - EE 467W/477 (FALL 2017 - SPRING 2018)
  TITLE: Voice-controlled Home Automation System via Bluetooth. (VC-HAUS)
        - Turn on/off lights and other Electrical appliances with help of relay module.
        - Display Time and Temperature 
        - Play Music*****
  Components: 1SHEELD+, Arduino, LightBulbs, Resistors,4 module Relay, Switches, 1sheeld APP for smartphone, TMP 36.
  Minnesota State University, Mankato
  Department of Electrical and Computer Engineering Technology
  Team Outlaws 2.0 
    - Asif Uddin
    - Winston Moh Tangongho
*/
//_______________________________________________________________________________________________________________
// Regular Expressions library.
#include <Regexp.h>

// Set up LCD KEYPAD SHIELD
#include <LiquidCrystal.h>
#include <Wire.h>
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
//______________________________________________________________________________________________________________

//Set up 1SHEELD+ 
//Call the custom settings to optimize the flash memory usage
#define CUSTOM_SETTINGS
//Calling for Arduino Voice Recognize Shield
#define INCLUDE_VOICE_RECOGNIZER_SHIELD

//A Boolean flag to know if recognition has been started already
bool started = false;

//TMP36 Pin Variables
int sensorPin = 1; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
                        //Use pin A1 since pin A0 is conected to buttons on LCD Keypad Shield.

//Including 1Sheeld library.
#include <OneSheeld.h>

// Include RTC Clock library.
#include <DS3231.h>
DS3231  rtc(SDA, SCL);  // SDA - A4 and SCL - A5 on Arduino Uno.

//______________________________________________________________________________________________________________

//Set the lamp to pin 13 - Can be changed later.
// connect bent(long end) end of LED to pin D13 and straight end to GND.
int red = 13;
int green = 12; 
//______________________________________________________________________________________________________________

/* Speaker pin
#include "SD.h"
#define SD_ChipSelectPin 3  // CS PIN
#include "TMRpcm.h"
#include "SPI.h"

// Create object of class TMRpcm
TMRpcm tmrpcm;
*/

//______________________________________________________________________________________________________________

void setup() {
  
   Serial.begin(115200);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
   // put your setup code here, to run once:
   rtc.begin();                    // start rtc module.
   
   lcd.begin(16, 2);               // start the library
   lcd.setCursor(0,0);             // set the LCD cursor   position 
   lcd.print("Welcome to VC-HAUS");  // print a simple message on the LCD
   lcd.setCursor(0,1);
   lcd.print("Push Select Button to Start");
   
   /* Start Communication. */
   OneSheeld.begin();
   /* Error Commands handiling. */
   VoiceRecognition.setOnError(error);
   //This is a trigger for the newCommand void , 
   //It's called each time a new command is recognized by the phone
   VoiceRecognition.setOnNewCommand(newCommand);   
   
   //Set the LED pins to be an Output.
   pinMode(red,OUTPUT);
   pinMode(green,OUTPUT);
   
   // Speaker pin.
   //tmrpcm.speakerPin = 1;
   
}

void loop(){   
   lcd_key = read_LCD_buttons();   // read the buttons
 
   switch (lcd_key){               // depending on which button was pushed, we perform an action

       case btnRIGHT:{             //  push button "RIGHT" and show the word on the screen
            lcd.scrollDisplayLeft();
            delay(300);
            break;
       }
       case btnLEFT:{
             lcd.scrollDisplayRight();//  push button "LEFT" and show the word on the screen
             delay(300);
             break;
       }    
       case btnUP:{
             break;
       }
       case btnDOWN:{
             break;
       }
       case btnSELECT:{
             if (!started){
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("Listening...");  //  push button "SELECT" and show the word on the screen
             VoiceRecognition.start();
             started = true;}
             break;
       }
       case btnNONE:{
             //  No action on the KeyPad
             started = false;
             break;
       }
   }
}

void error(byte errorData)
{
  /* Switch on error and print it on the terminal. */
  switch(errorData)
  {
    case NETWORK_TIMEOUT_ERROR: lcd.setCursor(0,1);lcd.print("Network timeout");break;
    case NETWORK_ERROR: lcd.setCursor(0,1);lcd.print("Network Error");break;
    case AUDIO_ERROR: lcd.setCursor(0,1);lcd.print("Audio error");break;
    case SERVER_ERROR: lcd.setCursor(0,1);lcd.print("No Server");break;
    case SPEECH_TIMEOUT_ERROR: lcd.setCursor(0,1);lcd.print("Speech timeout");break;
    case NO_MATCH_ERROR: lcd.setCursor(0,1);lcd.print("No match");break;
    case RECOGNIZER_BUSY_ERROR: lcd.setCursor(0,1);lcd.print("Busy");break;
  }
}

int read_LCD_buttons(){// read the buttons
    
    // read the value from the keypad since only one analog pin is used
    adc_key_in = analogRead(0);       
     

    if (adc_key_in > 1000) return btnNONE; 

    //For V1.1 of the LCD/Keypad Shield enable this threshold
    
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  
    
   // For V1.0 comment the other threshold and use the one below:
   /*
     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   
   */
   

    return btnNONE;  // when all others fail, return this.
}

void newCommand(String command){
    //Clear the text on the LCD Screen
    lcd.clear();
    lcd.setCursor(0,0);// set the LCD cursor position 
    lcd.print("You said");
    lcd.setCursor(0,1);
    
    String str = VoiceRecognition.getLastCommand();    // variable to hold voice comand string.
    Serial.print(str);                      // Print in serial monitor for debugging purposes.
    //print last command received
    lcd.print(str);
    
    MatchState ms;      // Create match state instance.
    
    // Convert string to char* for ms.Match()
    int length = str.length() + 1;  // Place NULL in last slot.
    char buff[length];
    str.toCharArray(buff, length);
    
    ms.Target (buff);    // What to search.
    //Compare the last command received by the Arduino Voice Recognition Shield with the command "ON"
    if(ms.Match("on", 0) == REGEXP_MATCHED)
    {
      //Then turn the light on
      if (ms.Match("red", 0) == REGEXP_MATCHED && !(ms.Match("both", 0) == REGEXP_MATCHED))
      {
        digitalWrite(red, HIGH);
      }
      else if(ms.Match("green", 0) == REGEXP_MATCHED && !(ms.Match("both", 0) == REGEXP_MATCHED))
      {
        digitalWrite(green, HIGH);
      }
      // Turn both lights off.
      else if (ms.Match("both", 0) == REGEXP_MATCHED)
      {
        digitalWrite(red, HIGH);
        digitalWrite(green, HIGH);
      }
    }
    
    //Compare the last command received by the Arduino Voice Recognition Shield with the command "OFF"
    else if(ms.Match("off", 0) == REGEXP_MATCHED)
    {
      //Then turn the light off
      if (ms.Match("red", 0) == REGEXP_MATCHED)
      {
        digitalWrite(red, LOW);
      }
      else if(ms.Match("green", 0) == REGEXP_MATCHED)
      {
        digitalWrite(green, LOW);
      }
      // Turn both lights off
      else if (ms.Match("both", 0) == REGEXP_MATCHED)
      {
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
      }
    }     
    
    // Commands for Temperature.
    else if (ms.Match("temperature", 0) == REGEXP_MATCHED)
    {
     //getting the voltage reading from the temperature sensor
     int reading = analogRead(sensorPin);  
     
     // converting that reading to voltage, for 3.3v arduino use 3.3
     float voltage = reading * 5.0;
     voltage /= 1024.0; 
     
     // now print out the temperature
     float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                   //to degrees ((voltage - 500mV) times 100)
     // now convert to Fahrenheit
     float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;                                                  
     
     // Print out Temperature on LCD Keypad Shield.
     lcd.clear();
     lcd.setCursor(0,0);  // set the LCD cursor position to line 0
     lcd.print("Temp in C: ");
     lcd.setCursor(11,0);
     lcd.print(temperatureC);
     
     lcd.setCursor(0,1);// set the LCD cursor position to next line
     lcd.print("Temp in F: ");
     lcd.setCursor(11,1); 
     lcd.print(temperatureF);       
      
    }
    
    // Display time for 10 seconds.
    else if (ms.Match("time", 0) == REGEXP_MATCHED)
    {
     // Print out time from rtc
     for (int i=0; i<10; i++)  // run for 10 seconds.
     {   
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Time:  ");
       lcd.print(rtc.getTimeStr());
       
       lcd.setCursor(0,1);
       lcd.print("Date: ");
       String _date = rtc.getDateStr();
       String _day = _date.substring(0,2);
       String _month = _date.substring(3,5);
       String _year = _date.substring(6,10);
       lcd.print(_month + "." + _day + "." + _year);  // print in US format.
       delay(1000); 
     }  
    }
    
    // Play music
    /*else if (ms.Match("music", 0) == REGEXP_MATCHED)
    {
        if (!SD.begin(SD_ChipSelectPin)) 
        {
            Serial.println("SD fail");
            return;
        }
        tmrpcm.setVolume(6);
        tmrpcm.play("music.wav");
    }
    */
}

