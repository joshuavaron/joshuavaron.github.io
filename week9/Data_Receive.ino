#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
    double x;
    double y;
} struct_message;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  double x = myData.x;
  double y = myData.y
  ...
}

void setup() {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  ...
}

void loop() {
  
}