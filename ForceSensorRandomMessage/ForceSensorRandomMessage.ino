
#include <LiquidCrystal.h>
#define fsrpin A0

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int fsrreading;

int timer = 500;

String messages[] = {"Message", "Test"}; 
int messagesLength = 2;


void setup() {
  
  lcd.begin(16, 2);
}

void loop() {

  fsrreading = analogRead(fsrpin);
  lcd.home();

  if (fsrreading > 500) {
    printMessage();
    delay(timer);
    lcd.clear();
  } 
}

void printMessage() {
  randIndex = random(0, messagesLength);
  lcd.print(messages[randIndex]);
  
}
