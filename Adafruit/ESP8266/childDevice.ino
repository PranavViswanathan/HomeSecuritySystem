#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "Orange04"
#define WLAN_PASS       "AllIsWell"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "PranavViswanathan"
#define AIO_KEY         "aio_uMiD22VjwV9veI3ZXKlGsXLJljMx"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);


/****************************** Feeds ***************************************/
Adafruit_MQTT_Publish hcclose = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/hcclose");


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  
  while (!Serial) {
        ; 
      }
      
}
int var = 0;
void loop() { 
  MQTT_connect();
  if (Serial.available()) {
    var = Serial.read();
    if (! hcclose.publish(var)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("HcClose1 Published to server!"));
  }
  }
}
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
