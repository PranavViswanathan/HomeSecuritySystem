
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Orange04"
#define WLAN_PASS       "AllIsWell"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "PranavViswanathan"
#define AIO_KEY         "aio_uMiD22VjwV9veI3ZXKlGsXLJljMx"

/************ Global State ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);


/****************************** Feeds ***************************************/
Adafruit_MQTT_Publish hcclose = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/hcclose");

Adafruit_MQTT_Publish text = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/serial-monitor");

Adafruit_MQTT_Publish warning = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/warning");
/*************************** Sketch Code ************************************/

void MQTT_connect();



const int trigPin = 12;
const int echoPin = 14;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input


  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  
}

void loop() {
  MQTT_connect();
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * 0.034 / 2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  
  if (! hcclose.publish(distanceCm)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("HcClose1 Published to server!"));
  }
  if (! text.publish(distanceCm)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("text Published to server!!"));
  }
  if (! warning.publish(distanceCm)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("warning Published to server!"));
  }
  delay(5000);
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
