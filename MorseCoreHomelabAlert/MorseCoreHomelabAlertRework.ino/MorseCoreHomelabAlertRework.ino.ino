// Declaring Variables
String alertMessage = "hello world";
volatile bool powerState = true;
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
int redPin = 9;
int greenPin = 5;
int bluePin = 6;

//Declaring ColorValues
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

//Declaring BuzzerPin
int beepPin = 4;

void setup() {
  Serial.begin(115200);
  Serial.println("Welcome, configurations are on the way");
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
  
}

void powerStateToggle() {
  Serial.print("Changing Power State to ");
  Serial.println(!powerState);
  powerState = !powerState;
}
void setColor(int red, int green, int blue) {
  redValue = red;
  greenValue=green;
  blueValue=blue;   
}

void toggleLed(bool toggleStatus, bool toggleBuzzer=false){
  if (!toggleStatus){
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);
  digitalWrite(beepPin, LOW);  
  }else {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
  
  if (toggleBuzzer){
    digitalWrite(beepPin, HIGH);
  }
  }
}
void dot() {
  toggleLed(true,true);
  delay(100);
  toggleLed(false);
  delay(charDelay);
}

void dash() {
  toggleLed(true,true);
  delay(300);
  toggleLed(false);
  delay(charDelay);
}


bool encodeMorseCharacter(char CHAR) {
  //Iterate through the morse code mapping
  for (int i=0; i<sizeof(MORSE_CODE) / sizeof(MORSE_CODE[0]); i++){
    if (MORSE_CODE[i][0]==CHAR){
      String morse = String(MORSE_CODE[i][1]);

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
        }
      }
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

void printMorseDic(){
  for (int i = 0; i < sizeof(MORSE_CODE) / sizeof(MORSE_CODE[0]); i++) {
    char character = MORSE_CODE[i][0];
    String morse = String(MORSE_CODE[i][1]);
    Serial.print(character);
    Serial.print(": ");
    Serial.println(morse);
  }
  messageToMorse(alertMessage);
}


void messageToMorse(String message){
  //Convert to UPPER to remove CaseSensitive messages
  message.toUpperCase();
  Serial.print("Current message is: ");
  Serial.println(message);
  int messageLength = message.length();
  for (int i=0; i<=messageLength && powerState == true; i++){
    char testChar = message[i];
    Serial.print("Current char is: ");
    Serial.println(testChar);
    encodeMorseCharacter(testChar);  
    delay(charDelay);
  }
  toggleLed(true,false);  
}

void loop() {
  if (powerState == true) {
    
    // If Power State indicates that the service has been turned On
    setColor(0, 255, 0);
    toggleLed(true,false);
    while (Serial.available()==0){
      if(!powerState){
        break;
        }
          
    }
    String inputMessage = Serial.readStringUntil('\n');
    messageToMorse(inputMessage);
    
    
  } else {
    //Obviously Power State is Off, or StandBy for context purposes
        setColor(0, 0, 255);
        toggleLed(true,false);
  }
  delay(wordDelay);
}
