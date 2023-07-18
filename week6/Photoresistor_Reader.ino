long previousMillis = 0;

class Photoresistor
{
	int readPin;

  public:
  Photoresistor(int pin)
  {
	readPin = pin;
	pinMode(readPin, INPUT);     
  }

  int Read()
  {
    return analogRead(readPin);
  }
};

Photoresistor left(9);
Photoresistor right(10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > 100) {
    previousMillis = currentMillis; 
    int leftVal = left.Read();
    int rightVal = right.Read();
    Serial.println(leftVal - rightVal);
  }
}