#include <esp_now.h>
#include <WiFi.h>


typedef struct struct_message {
    double x;
    double y;
    int speed;
} struct_message;


struct_message myData;


const int stepPin = 1;
const int dirPin = 2;
const int stepPin2 = 4;
const int dirPin2 = 5;


const int a = 62;
const int b = 42;


double prevX = 0;
double prevY = 0;
 
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));


  digitalWrite(dirPin,HIGH);
  digitalWrite(dirPin2,HIGH);
  double x = myData.x;
  double y = myData.y;
  int speed = myData.speed;

  double diffL = ((sqrt((a+x)*(a+x) + (b-y)*(b-y))) - (sqrt((a+prevX)*(a+prevX) + (b-prevY)*(b-prevY))));
  double diffR = ((sqrt((a-x)*(a-x) + (b-y)*(b-y))) - (sqrt((a-prevX)*(a-prevX) + (b-prevY)*(b-prevY))));
  prevX = x;
  prevY = y;
  Serial.println(diffL);
  Serial.println(diffR);
  if(diffL > 0){
    digitalWrite(dirPin2,HIGH);
  } else {
    digitalWrite(dirPin2,LOW);
  }
  if(diffR > 0){
    digitalWrite(dirPin,HIGH);
  } else {
    digitalWrite(dirPin,LOW);
  }
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  if(abs(diffL) > abs(diffR)){
    for(int i = 0; i<abs((int)(3200*diffL/1.89)); i++){
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin2,LOW);  
      delayMicroseconds(400);
      if(diffR != 0 && i%(int)(diffL / diffR) == 0){
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(400);
        digitalWrite(stepPin,LOW);  
        delayMicroseconds(400);
      }
    }
  } else {
    for(int i = 0; i<abs((int)(3200*diffR/1.89)); i++){
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin,LOW);  
      delayMicroseconds(400);
      if(diffL != 0 && i%(int)(diffR / diffL) == 0){
        digitalWrite(stepPin2,HIGH);
        delayMicroseconds(400);
        digitalWrite(stepPin2,LOW);  
        delayMicroseconds(400);
      }
    }
  }
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
}


void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  WiFi.mode(WIFI_STA);


  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}
void loop() {


}

