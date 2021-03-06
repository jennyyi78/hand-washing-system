
#include <LiquidCrystal.h>
#define fsrpin A0
#define fsrpin2 A1

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int soapFsrreading;
int doorFsrreading;

int timer = 2000;
bool soapPressed = false;
unsigned long timePressed = 0;

String goodMessages[] = {"Good job", "You deserve the best", "My little pogchamp", "Cleanliness is a virtue" }; 
int goodMessagesLength = 4;

String badMessages[] = {"Why are you like this?", "You are disgusting", "Literal scum", "Despicable swine", "Not very poggers of you" }; 
int badMessagesLength = 5;

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

  
  outlong("start loop - time since press:", millis() - timePressed );
  // 1
  if (soapPressed && (millis() - timePressed > 30000)) {
    soapPressed = false; 
    outSP("1 SP:", soapPressed);
  }

  // 2
  if (soapFsrreading > 500) {
    soapPressed = true;
    timePressed = millis();
    outSP("2 SP:", soapPressed);
  }

  //3
  if (doorFsrreading > 500 && soapPressed) {
    printMessage("Good");
    soapPressed = false;
    delay(timer);
    lcd.clear();
    compliance++;
     outSP("3 SP:", soapPressed);
  } 
  else if (doorFsrreading > 500 && !soapPressed) {
    //4
    printMessage("Bad");
    delay(timer);
    lcd.clear();
    noncompliance++;
    outSP("4 SP:", soapPressed);
   
  }
  outSP("end loop - SP: ", soapPressed);
}
void outlong(String msg, unsigned long timeVar)
{
  Serial.print(msg);
  Serial.println(timeVar);
}

void outSP(String msg, bool soapPressed)
{
  Serial.print(msg);
  Serial.println(soapPressed);
}

void printMessage(String mode) {
  if (mode == "Good") {
    int randIndex = random(0, goodMessagesLength);
    lcd.print(goodMessages[randIndex]);
    String message = goodMessages[randIndex];
    for(int i = 0; i < message.length(); i++) {
      if (message[i] == '-') {
        lcd.setCursor(0, 2);
      } else {
        lcd.print(message[i]); 
      }
      
    }
    
  } else {
    int randIndex = random(0, badMessagesLength);
    lcd.print(badMessages[randIndex]);
    String message = badMessages[randIndex];
    for(int i = 0; i < message.length(); i++) {
      if (message[i] == '-') {
        lcd.setCursor(0, 2);
      } else {
        lcd.print(message[i]); 
      }
    }
  }
  
  
}
