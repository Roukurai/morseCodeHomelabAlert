// Declaring Variables
String message = "HELLO WORLD";
volatile bool powerState = false;
String errorMessage = "";
int errorCode = 0;


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
};

//Declaring gap timing
int charDelay = 100;
int letterDelay = 200;
int wordDelay = 600;

//Declaring ColorPins
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

//Declaring BuzzerPin
int beepPin = 4;

void setup() {
  Serial.begin(9600);
  // ColorPin are configured for output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // BuzzerPin is configured for output
  pinMode(beepPin, OUTPUT);

  // InputPin is configured for input
  pinMode(2, INPUT);

  //Start message loop Interrupt setup
  attachInterrupt(digitalPinToInterrupt(2), powerStateToggle, RISING);
  
  //PowerState Interrupt setup
  attachInterrupt(digitalPinToInterrupt(3), powerStateOff, RISING);
}

void powerStateToggle() {
  Serial.print("Changing Power State ");
  Serial.println(!powerState);
  powerState = !powerState;
}

void powerStateOff(){
  Serial.println("Turning Off");
  powerState = false;
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void dot() {
  setColor(0, 0, 255);
  digitalWrite(beepPin, HIGH);
  delay(100);
  setColor(0, 0, 0);
  digitalWrite(beepPin, LOW);
  delay(100);
}

void dash() {
  setColor(0, 255, 0);
  digitalWrite(beepPin, HIGH);
  delay(300);
  setColor(0, 0, 0);
  digitalWrite(beepPin, LOW);
  delay(100);
}


bool encodeMorseCharacter(char CHAR) {
  //Convert to UPPER to remove CaseSensitive messages

  CHAR = toupper(CHAR);
  
  //Iterate through the morse code mapping
  for (int i=0; i<sizeof(MORSE_CODE) / sizeof(MORSE_CODE[0]); i++){
    Serial.println(MORSE_CODE[i][0]);
    if (*MORSE_CODE[i][0]==CHAR){
      String morse = MORSE_CODE[i][1];

      //Iterate through the morse code string and produce dots and dashes
      for (int j=0; j<morse.length(); j++){
        if (morse[j] == '.'){
          dot();
        } else if (morse[j] == '-'){
          dash();
        } else {
          //False due to morse char not available
          errorMessage = "CHAR Not found in morse mapping";
          errorCode = 1300;
          return false;
        }}
      return true;
    }
  }
  if (CHAR == ' '){
    delay(wordDelay);
    return true;
  } else {
    // CHAR Not found in mapping
    errorMessage = "CHAR Not found in morse mapping";
    errorCode = 1300;
    return false;
  }
}

void loop() {
  Serial.print("PowerState is currently: ");
  Serial.println(powerState);
  if (powerState == true) {
    int messageLength = message.length();
    for (int i = 0; i <= messageLength && powerState == true; i++) {
      char testChar = message[i];
      encodeMorseCharacter(testChar);
      delay(charDelay);
    }
  } else {
    setColor(255, 0, 0);
  }
  delay(wordDelay);
}
