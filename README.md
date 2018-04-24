#  ![VC-HAUS](https://github.com/WinstonMoh/Voice-controlled-Home-Automation-System/blob/master/images/logo.PNG)

# Voice-controlled-Home-Automation-System
Hardware system which allows a user to give commands to Arduino device and control events such as show temperature, turn on lights etc.

# Introduction
Our project is a prototype of an autonomous Home System which will rely solely on the user's voice commands. It would consist of a 1SHEELD+ device and a smartphone with the corresponding 1Sheeld app installed on it to get the user input. There would be an lCD Keypad shield to display information of the system. And there would be LEDs or lightbulbs to display the system function (turning on and off). All the different components will be processed by the program uploaded in the Arduino board. </br>

Program uploaded in the Arduino board will process all the input data from the 1SHEELD Device. Then output will be given accordingly to the LEDs and LCD Display. The main objective of the Home Autonomous system is for the user to control house appliances by using his speech only. Hence the main objective of the 1Sheeld device is to relay information from the smartphone voice input and transmit it to the Arduino software which can then be processed in the code. This will reduce user effort to control appliances by a substantial amount. At the same time money will be saved due to time saving and effort can be used on more important things. </br>

There are many companies which are innovating to Home Autonomous Systems. But currently there is no commercially viable system for the consumers. But if more projects such as ours are being built in more universities then innovation will take place faster and the prices will reduce. 


# Set-up
- Download and Install Arduino IDE(Latest version) from https://www.arduino.cc/en/Main/Software.
- Buy Arduino MEGA board from https://store.arduino.cc/usa/arduino/most-popular. ATMega2560 was used because the SD card library consumed almost all of the SRAM and caused stability issues. The MEGA was used because it carries 8KB of SRAM which is suitable for our purposes.
- Connect Arduino and other components accordingly, compile and upload your code and start using the product.
*Analysis:* </br>
<u>Arduino MEGA </u>: Global variables use 2,095 bytes (25%) of dynamic memory, leaving 6,097 bytes for local variables. Maximum is 8,192 bytes. </br>
<u>Arduino UNO </u>: Global variables use 1,656 bytes (80%) of dynamic memory, leaving 384 bytes for local variables. Maximum is 2,048 bytes. </br>
Hence, we went with the Arduino MEGA. 

# Summary
## A) Functions
1.	Design a cheap and portable Home Automation System with Voice-recognition which works with new technology known as a 1SHEELD+ Device.
2.	Receives input from User in the form of Voice commands such as “Turn off x...” or “Turn off y...” and much more. Voice commands are converted from sound to text using 1SHEELD+ application in mobile phone and transmits the converted text via Bluetooth to our arduino Board which then loads the text into the program code and performs the required action. </br> 
Regular expressions were used to match the voice commands with the expected commands. This reduced the amount of work on the user's end to replicate exact strings. for example. "Turn off red light", "... turn off the red light ..." and "Red light off" all work in the same way to turn off the red light.
3. Final outputs include: </br>
 - Turning Ligths ON/OFF.
 - Displaying room temperatures in celcius and Fahrenheit.
 - Displaying time in 24h format with current Date.
 - Alarm system for very high temperatures. Uses TMP36 to detect high temperatures but a smoke detector could be used in place of it.
4.	Display received commands with other information on the LCD screen.
 

## B) Requirements
1.	Arduino Mega – Microcontroller for Project
2.	PC with Arduino IDE
3.	1SHEELD+ device – Acts as our communication device between speech and the Arduino
4.	Smartphone (iOS or Android) with 1SHEELD application installed and Bluetooth enabled – Receives voice input from USER.
5.	Resistors for LEDs ~ 200Ω – Regulate brightness of the LEDs.
6.	Breadboard – Used for testing components on.
7.	LCD Keypad Shield – Displays information of the System.
8.  TMP36 - Temperature Sensor.
9.  RTC - Real-Time Clock to display current Time.
10. PCB with resistors, LEDs and diodes.
11.	Relays (AC250V 10A; DC30V 10A) – Connects Arduino to real appliances by stepping up the Arduino Voltage.


# Conclusion
This project can be replicated in multiple quantitities.
