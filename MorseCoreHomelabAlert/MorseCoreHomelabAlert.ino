
// Declaring Variables
String message = "HELLO WORLD";
volatile bool PowerState = false;

// Defining morse code mapping
const char* MORSE_CODE[][2]={
  {'A', ".-"},   {'B', "-..."},  {'C', "-.-."}, {'D', "-.."},
  {'E', "."},    {'F', "..-."},  {'G', "--."},  {'H', "...."},
  {'I', ".."},   {'J', ".---"},  {'K', "-.-"},  {'L', ".-.."},
  {'M', "--"},   {'N', "-."},    {'O', "---"},  {'P', ".--."},
  {'Q', "--.-"}, {'R', ".-."},   {'S', "..."},  {'T', "-"},
  {'U', "..-"},  {'V', "...-"},  {'W', ".--"},  {'X', "-..-"},
  {'Y', "-.--"}, {'Z', "--.."},  {'1', ".----"}, {'2', "..---"},
  {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."},
  {'7', "--..."}, {'8', "---.."}, {'9', "----."}, {'0', "-----"}
}

//Declaring gap timing
int charGap = 100;
int letterGap = 200;
int wordGap = 600;

//Declaring ColorPins
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

//Declaring BuzzerPin
int beepPin = 4;

void setup() {
  // ColorPin are configured for output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // BuzzerPin is configured for output
  pinMode(beepPin, OUTPUT);

  // InputPin is configured for input
  pinMode(2, INPUT);

  //Start message loop Interrupt setup
  attachInterrupt(digitalPinToInterrupt(2), TogglePowerState, RISING);
  
  //PowerStete Interrupt setup
  attachInterrupt(digitalPinToInterrupt(3), PowerOff, RISING);
}

void TogglePowerState() {
  PowerState = !PowerState;
}

void PowerOff(){
  PowerState = false;
}

void SetColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void dot() {
  SetColor(0, 0, 255);
  digitalWrite(beepPin, HIGH);
  delay(100);
  SetColor(0, 0, 0);
  digitalWrite(beepPin, LOW);
  delay(100);
}

void dash() {
  SetColor(0, 255, 0);
  digitalWrite(beepPin, HIGH);
  delay(300);
  SetColor(0, 0, 0);
  digitalWrite(beepPin, LOW);
  delay(100);
}


bool CheckChar(char CHAR) {
  switch (CHAR) {
    case 'A':
      dot();
      dash();
      break;

    case 'B':
      dash();
      for (int i = 0; i < 3; i++) {
        dot();
      };
      break;

    case 'C':
      for (int i = 0; i < 2; i++) {
        dash();
        dot();
      };
      break;

    case 'D':
      dash();
      for (int i = 0; i < 2; i++) {
        dot();
      };
      break;

    case 'E':
      dot();
      break;

    case 'F':
      for (int i = 0; i < 2; i++) {
        dot();
      };
      dash();
      dot();
      break;

    case 'G':
      for (int i = 0; i < 2; i++) {
        dash();
      };
      dot();
      break;

    case 'H':
      for (int i = 0; i < 4; i++) {
        dot();
      };
      break;

    case 'I':
      for (int i = 0; i < 2; i++) {
        dot();
      };
      break;

    case 'J':
      dot();
      for (int i = 0; i < 3; i++) {
        dash();
      };
      break;

    case 'K':
      dash();
      dot();
      dash();
      break;

    case 'L':
      dot();
      dash();
      for (int i = 0; i < 2; i++) {
        dot();
      };
      break;

    case 'M':
      for (int i = 0; i < 3; i++) {
        dash();
      };
      break;

    case 'N':
      dash();
      dot();
      break;

    case 'O':
      for (int i = 0; i < 3; i++) {
        dash();
      };
      break;

    case 'P':
      for (int i = 0; i < 2; i++) {
        dash();
        dot();
      };
      break;

    case 'Q':
      dot();
      dash();
      dot();
      break;

    case 'R':
      dot();
      dash();
      dot();
      break;

    case 'S':
      for (int i = 0; i < 3; i++) {
        dot();
      };
      break;

    case 'T':
      dash();
      break;

    case 'U':
      for (int i = 0; i < 2; i++) {
        dot();
      };
      dash();
      break;

    case 'V':
      for (int i = 0; i < 3; i++) {
        dot();
      };
      dash();
      break;

    case 'W':
      dot();
      for (int i = 0; i < 2; i++) {
        dash();
      };
      break;

    case 'X':
      dash();
      for (int i = 0; i < 2; i++) {
        dot();
      };
      dash();
      break;

    case 'Y':
      dash();
      for (int i = 0; i < 2; i++) {
        dot();
      };
      dash();
      break;

    case 'Z':
      for (int i = 0; i < 2; i++) {
        dash();
      };
      for (int i = 0; i < 2; i++) {
        dot();
      };
      break;

    case '1':
      dot();
      for (int i = 0; i < 4; i++) {
        dash();
      };
      break;

    case '2':
      for (int i = 0; i < 2; i++) {
        dot();
      };
      for (int i = 0; i < 3; i++) {
        dash();
      };
      break;

    case '3':
      for (int i = 0; i < 3; i++) {
        dot();
      };
      for (int i = 0; i < 2; i++) {
        dash();
      };
      break;

    case '4':
      for (int i = 0; i < 4; i++) {
        dot();
      };
      dash();
      break;

    case '5':
      for (int i = 0; i < 5; i++) {
        dot();
      };
      break;

    case '6':
      dash();
      for (int i = 0; i < 4; i++) {
        dot();
      };
      break;

    case '7':
      for (int i = 0; i < 2; i++) {
        dash();
      };
      break;

    case '8':
      for (int i = 0; i < 3; i++) {
        dash();
      };
      for (int i = 0; i < 2; i++) {
        dot();
      };
      break;

    case '9':
      for (int i = 0; i < 4; i++) {
        dash();
      };
      break;

    case '0':
      for (int i = 0; i < 5; i++) {
        dash();
      };
      break;
    case ' ':
      delay(wordGap);
      break;

    default:
      return false;
      break;
  }


  return true;
}

void loop() {
  if (PowerState == true) {
    int messageLenght = message.length();
    for (int i = 0; i <= messageLenght && PowerState == true; i++) {
      char testChar = message[i];
      CheckChar(testChar);
      delay(charGap);
    }
  } else {
    SetColor(255, 0, 0);
  }
  delay(wordGap);
}
