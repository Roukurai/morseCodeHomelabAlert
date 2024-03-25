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
int CHAR_DELAY = 100;
int LETTER_DELAY = 200;
int WORD_DELAY = 600;

//Declaring Pins
int RED_PIN = 9;
int GREEN_PIN = 5;
int BLUE_PIN = 6;
int BEEP_PIN = 4;

//Declaring ColorValues
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

// Declaring functions [kinda like init i would assume before any one is requested they already exist]
void setup();
void loop();
void setColor(int red,int green, int blue);
void toggleLed(bool toggleStatus, bool toggleBuzzer=false);
void dot();
void dash();
bool encodeMorseChar(char CHAR);
void printMorseDictionary();
void messageToMorse(String message);



void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BEEP_PIN, OUTPUT);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), powerStateToggle, RISING);
  Serial.println("Arduino is ready");
}

void powerStateToggle() {
  powerState = !powerState;
}

void setColor(int red, int green, int blue) {
  redValue = red;
  greenValue=green;
  blueValue=blue;   
}

void toggleLed(bool toggleStatus, bool toggleBuzzer=false){
  if (!toggleStatus){
  digitalWrite(RED_PIN,LOW);
  digitalWrite(GREEN_PIN,LOW);
  digitalWrite(BLUE_PIN,LOW);
  digitalWrite(BEEP_PIN, LOW);  
  }else {
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);
  if (toggleBuzzer){
    digitalWrite(BEEP_PIN, HIGH);
  }
  }
}

void dot() {
  toggleLed(true,true);
  delay(100);
  toggleLed(false);
  delay(CHAR_DELAY);
}

void dash() {
  toggleLed(true,true);
  delay(300);
  toggleLed(false);
  delay(CHAR_DELAY);
}


bool encodeMorseChar(char CHAR) {
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
          errorMessage = "CHAR Not found in morse mapping";
          errorCode = 1300;
          return false;
        }
      }
      return true;
    }
  }
  if (CHAR == ' '){
    delay(WORD_DELAY);
    return true;
  } else {
    errorMessage = "CHAR Not found in morse mapping";
    errorCode = 1300;
    return false;
  }
}

void printMorseDic(){
  for (int i = 0; i < sizeof(MORSE_CODE) / sizeof(MORSE_CODE[0]); i++) {
    char character = MORSE_CODE[i][0];
    String morse = String(MORSE_CODE[i][1]);
  }
  messageToMorse(alertMessage);
}


void messageToMorse(String message){
  //Convert to UPPER to remove CaseSensitive messages
  message.toUpperCase();
  Serial.print("Message received");
  int messageLength = message.length()-1;
  for (int i=0; i<=messageLength && powerState == true; i++){
    char testChar = message[i];
    Serial.print(":: ");
    Serial.println(testChar);
    encodeMorseChar(testChar);  
    delay(CHAR_DELAY);
  }
  toggleLed(true,false);
  Serial.println("/420");  
}

void loop() {
  if (powerState == true) {
    // If Power State indicates that the service has been turned On
    setColor(0, 255, 0);
    toggleLed(true,false);
    while (!Serial.available()){
      
    }

    // Receive message and check not empty
    String inputMessage = Serial.readStringUntil('\n');    
    if (inputMessage!=NULL){
      messageToMorse(inputMessage);      
    }
  } else {
    //Obviously Power State is Off, or StandBy for context purposes
        setColor(0, 0, 255);
        toggleLed(true,false);
  }
  delay(WORD_DELAY);
}
