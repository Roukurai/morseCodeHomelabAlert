# morseCodeHomelabAlert
Homelab alerts will be provided via morse code, visually and audible. Planting the base for AlertToSpeech

Purpose:
This Arduino code is designed to use an LED and a piezo buzzer to display a message in Morse code when requested by the homelab. The message is coded in Morse, and the LEDs light up according to the Morse code pattern while the buzzer produces corresponding sounds.

Declarations:
message: A string variable that stores the message to be displayed in Morse code.
PowerState: A boolean variable that represents the state of the system (on/off).
charGap, letterGap, wordGap: Integer variables representing the time gaps between characters, letters, and words in Morse code, respectively.
redPin, greenPin, bluePin, beepPin: Integer variables representing the pins connected to the RGB LED and the buzzer.

Functions:
void setup(): The initialization function called once when the program starts. It sets the pinMode for the LED and buzzer pins and sets up interrupts for the button pins.

void loop(): The main execution loop that repeatedly checks the PowerState and displays the message in Morse code if the PowerState is true.

void TogglePowerState(): Interrupt service routine (ISR) that toggles the PowerState when the button is pressed.

void PowerOff(): ISR that sets the PowerState to false, turning off the system.

void SetColor(int redValue, int greenValue, int blueValue): Function to set the color of the RGB LED by writing PWM values to its pins.

void dot(): Function to produce a dot in Morse code pattern by lighting up the LED and emitting a short beep.

void dash(): Function to produce a dash in Morse code pattern by lighting up the LED and emitting a long beep.

bool CheckChar(char CHAR): Function to check each character in the message and translate it to Morse code. It calls dot() and dash() functions accordingly.

Morse Code Translation:
The CheckChar() function translates each character in the message to Morse code and calls corresponding functions (dot() or dash()) to display the pattern. The Morse code for each character is defined within a switch-case statement.

Usage:
Connect the RGB LED and the piezo buzzer to the specified pins on the Arduino board.
Upload the code to the Arduino.
Press the button connected to pin 2 to toggle the display of the message in Morse code.
Press the button connected to pin 3 to turn off the system.
Notes:
Adjust the time gaps (charGap, letterGap, wordGap) for proper Morse code timing.
Modify the message variable to display a different message in Morse code.





