int tx_pin = 42;

class Capacitive
{
  int readPin;

  public:
  Capacitive(int pin)
  {
    readPin = pin;
  }

  long Read()
  {
    int read_high;
    int read_low;
    int diff;
    long int sum = 0;
    for (int i = 0; i < 100; i++){
      digitalWrite(tx_pin,HIGH);
      read_high = analogRead(readPin);
      delayMicroseconds(100);
      digitalWrite(tx_pin,LOW);
      read_low = analogRead(readPin);
      diff = read_high - read_low;
      sum += diff;
    }
    return sum;
  }
};

void setup() {
    pinMode(tx_pin, OUTPUT);      //Pin 4 provides the voltage step
    Serial.begin(9600);
}

Capacitive a(1);
Capacitive b(2);
Capacitive c(3);
Capacitive d(4);

void loop() {
    Serial.println(a.Read());
    Serial.print(", ");
    Serial.print(b.Read());
    Serial.print(", ");
    Serial.print(c.Read());
    Serial.print(", ");
    Serial.println(d.Read());
}
