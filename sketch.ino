#include <WiFi.h>
#include <ThingSpeak.h>

#include "secret.h"

long duration;
float distanceCm;

const int trigPin = 5;
const int echoPin = 18;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.println("Couldn't establish WIFI connection");
  }
  Serial.println("Wifi is connected!");
  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
  delay(1000);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;
  
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  
  delay(20000);

  ThingSpeak.setField(5, distanceCm);
  int resultCode = ThingSpeak.writeFields(myChannelNumber, myApiKey);
  
  if (resultCode == 200) {
    Serial.println("Sent the data withou errors");
  }

}
