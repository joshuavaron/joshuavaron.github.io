#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//Change these
const char* ssid = "ssid";
const char* password =  "password";

String endpoint = "https://api.agify.io/?country_id=US&name=";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

}

void loop() {

  if ((WiFi.status() == WL_CONNECTED)) {

    HTTPClient http;
    if(Serial.available() > 0){
      String endpointTemp = endpoint + Serial.readString();
      http.begin(endpointTemp);
      int httpCode = http.GET();

      if (httpCode > 0) {

          String payload = http.getString();
          Serial.println(httpCode);
          Serial.println(payload);

          DynamicJsonDocument doc(10000);

          DeserializationError error = deserializeJson(doc, payload);

          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return;
          }
          const int age = doc["age"];
          const int count = doc["count"];
          const String name = doc["name"];
          
          if(count < 10000){
            Serial.print("Hello ");
            Serial.print(name);
            Serial.print(". I am unable to determine how old you are.");
            return;
          }

          Serial.print("Hello ");
          Serial.print(name);
          Serial.print(". I am ");
          Serial.print(count/5000.0);
          Serial.print("% sure you are ");
          Serial.print(age);
          Serial.println(" years old.");
        }

      else {
        Serial.println("Error on HTTP request");
      }

      http.end();
    }
  }
}