int target = 4600;

class Thermistor
{
	int readPin;

  public:
  Thermistor(int pin)
  {
	readPin = pin;
	pinMode(readPin, INPUT);     
  }

  int Read()
  {
    return analogRead(readPin);
  }

  void Print()
  {
    Serial.print(analogRead(readPin));
    Serial.print(", ");
    Serial.println(target);
  }
};

class Relay
{
  int signalPin;
  int isOn;

  public:
  Relay(int pin)
  {
    signalPin = pin;
    pinMode(signalPin, OUTPUT);
    isOn = 0;
  }

  void On(){
    digitalWrite(signalPin, HIGH);
  }

  void Off(){
    digitalWrite(signalPin, LOW);
  }
};

void setup() {
  Serial.begin(9600);
}

Thermistor therm(4);
Relay relay(3);

void loop() {
  while(therm.Read() > target){ //therm.Read() decreases as heat increases
    if (Serial.available() > 0) {
      target = Serial.parseInt();
    }
    therm.Print();
    relay.On();
  }
  if (Serial.available() > 0) {
    target = Serial.parseInt();
  }
  therm.Print();
  relay.Off();
}