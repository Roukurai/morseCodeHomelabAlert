Homelab Alerts via Morse Code with Visual and Audible Feedback

Purpose: This Arduino code facilitates displaying alerts from the homelab in Morse code, providing both visual and audible feedback. It utilizes an LED and a piezo buzzer to display the message in Morse code format.

Declarations:

message: A string variable holding the message to be displayed in Morse code.
PowerState: A boolean variable representing the system state (on/off).
charGap, letterGap, wordGap: Integer variables for defining time gaps between characters, letters, and words in Morse code.
redPin, greenPin, bluePin, beepPin: Integer variables representing the pins connected to the RGB LED and the buzzer.
Functions:

void setup(): Initializes the system, setting pinMode for LED and buzzer pins, and configuring interrupts for the button pins.
void loop(): The main execution loop continually checks the PowerState and displays the message in Morse code if PowerState is true.
void TogglePowerState(): Interrupt service routine (ISR) toggling PowerState when the button is pressed.
void PowerOff(): ISR setting PowerState to false, turning off the system.
void SetColor(int redValue, int greenValue, int blueValue): Sets the RGB LED color by adjusting PWM values.
void dot(), void dash(): Functions to display Morse code patterns with corresponding LED flashes and buzzer beeps.
bool CheckChar(char CHAR): Translates each character in the message to Morse code, calling dot() or dash() accordingly.
Morse Code Translation: The CheckChar() function translates each character in the message to Morse code and calls the corresponding functions (dot() or dash()) to display the pattern. Morse code definitions are within a switch-case statement.

Usage:

Connect the RGB LED and piezo buzzer to specified pins on the Arduino.
Upload the code to the Arduino.
Press the button connected to pin 2 to toggle the display of the message in Morse code.
Press the button connected to pin 3 to turn off the system.
Notes:

Adjust time gaps (charGap, letterGap, wordGap) for proper Morse code timing.
Modify the message variable to display a different message in Morse code.
