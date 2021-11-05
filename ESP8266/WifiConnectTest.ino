#include "ESP8266WiFi.h"

// WiFi parameters to be configured
const char* ssid = "WIFI NAME"; // Write here your router's username
const char* password = "WIFI PASSWORD"; // Write here your router's passward

void setup(void)
{ 
  Serial.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, password);

 
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());

}
void loop() {
  // Nothing
}
