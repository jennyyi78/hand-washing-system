void setup() {
  // put your setup code here, to run once:
  
  // pinMode([pinNum],[INPUT/OUTPUT])
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // digitalWrite([pinNum], [HIGH/LOW])
  // delay([number of ms])
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);

}
