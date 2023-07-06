void setup() {
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(21, INPUT);
}




void loop() {
  wave();
  reversewave();
}




void wave() {
  for(int i = 1; i<=7; i++){
    while(digitalRead(21) == LOW){}
    digitalWrite(i, HIGH);
    digitalWrite((i%7)+1, LOW);
    delay(80);
  }
}




void reversewave() {
  for(int i = 1; i<=7; i++){
    while(digitalRead(21) == LOW){}
    digitalWrite(i, LOW);
    digitalWrite((i%7)+1, HIGH);
    delay(80);
  }
}