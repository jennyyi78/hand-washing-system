
#include <LiquidCrystal.h>

#define fsrpin A0
#define fsrpin2 A1

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int soapFsrreading;
int doorFsrreading;

const int timer = 2000;

bool soapPressed = false;
unsigned long timePressed = 0;

const unsigned long ONE_MINUTE = 60000;
unsigned long pastTimeMeasure = 0;

String goodMessages[] = {"Good job", "You deserve the-best", "My little-pogchamp", "Cleanliness is a-virtue", "Those hands-looking fresh!" }; 
int goodMessagesLength = 5;

String badMessages[] = {"Why are you like-this?", "You are-disgusting", "Literal scum", "Despicable swine", "Not very poggers-of you", "Your spirit-animal is a poop" };  
int badMessagesLength = 6;

int compliance = 0;
int noncompliance = 0;


void setup() {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  lcd.begin(16, 2);
}

void loop() {

  soapFsrreading = analogRead(fsrpin);
  doorFsrreading = analogRead(fsrpin2);
  
  lcd.home();    
 
  if (soapPressed && (millis() - timePressed > 30000)) soapPressed = false;     
  
  if (soapFsrreading > 500) {
    soapPressed = true;
    timePressed = millis();    
  }
  
  if (doorFsrreading > 500 && soapPressed) {
      printMessage("Good");
      soapPressed = false;
      delay(timer);
      lcd.clear();
      compliance++;
  } else if (doorFsrreading > 500 && !soapPressed) {
      printMessage("Bad");
      delay(timer);
      lcd.clear();
      noncompliance++;      
  }
  
  if(millis() >= ONE_MINUTE + pastTimeMeasure){
    outCompliances();
    pastTimeMeasure = millis();
  }
}

void outCompliances()
{
  Serial.print("Compliance: ");
  Serial.print(compliance);
  Serial.print(" ");
  Serial.print("Noncompliance: ");
  Serial.println(noncompliance);
}

void printMessage(String mode) {
  int randIndex;
  String message;
  
  if (mode == "Good") {
    randIndex = random(0, goodMessagesLength);
    message = goodMessages[randIndex];
  } else {
    randIndex = random(0, badMessagesLength);
    message = badMessages[randIndex];
  }
  
  for(int i = 0; i < message.length(); i++) {
      if (message[i] == '-') {
        lcd.setCursor(0, 2);
      } else {
        lcd.print(message[i]); 
      }
      
    }
  
  
}
