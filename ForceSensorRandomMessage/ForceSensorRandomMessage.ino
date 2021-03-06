
#include <LiquidCrystal.h>
#define fsrpin A0
#define fsrpin2 A1

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int soapFsrreading;
int doorFsrreading;

int timer = 500;
bool soapPressed = false;
int timePressed = 0;

String goodMessages[] = {"Good", "Test"}; 
int goodMessagesLength = 2;

String badMessages[] = {"Bad", "Message"}; 
int badMessagesLength = 2;

int compliance = 0;
int noncompliance = 0;


void setup() {
  
  lcd.begin(16, 2);
}

void loop() {

  soapFsrreading = analogRead(fsrpin);
  doorFsrreading = analogRead(fsrpin2);
  
  lcd.home();

  if (soapPressed && (millis() - timePressed > 30000)) {
    soapPressed = false; 
  }

  if (soapFsrreading > 500) {
    soapPressed = true;
    timePressed = millis();
  }
  
  if (doorFsrreading > 500 && soapPressed) {
    printMessage("Good");
    delay(timer);
    lcd.clear();
    compliance++;
  } else if (doorFsrreading > 500 && !soapPressed) {
    printMessage("Bad");
    delay(timer);
    lcd.clear();
    noncompliance++;
  }
}

void printMessage(String mode) {
  if (mode == "Good") {
    int randIndex = random(0, goodMessagesLength);
    lcd.print(goodMessages[randIndex]);
  } else {
    int randIndex = random(0, badMessagesLength);
    lcd.print(badMessages[randIndex]);
  }
  
  
}
