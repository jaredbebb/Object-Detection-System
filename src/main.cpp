#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <env_config.h>

EnvConfig adafruit_config("AdaFruit");
const char* AIO_KEY = adafruit_config.GetDoc()["AdaFruit"]["AIO_KEY"];

const char* AIO_USERNAME = adafruit_config.GetDoc()["AdaFruit"]["AIO_USERNAME"];

const uint16_t AIO_SERVERPORT =  1883;
const char* AIO_SERVER = adafruit_config.GetDoc()["AdaFruit"]["AIO_SERVER"];

const char * feed = adafruit_config.GetDoc()["AdaFruit"]["AIO_FEED"];

/* Put your SSID & Password */
EnvConfig network_config("Network");
const char* WLAN_PASS = network_config.GetDoc()["AdaFruit"]["AIO_SERVER"];
const char* WLAN_SSID = network_config.GetDoc()["AdaFruit"]["AIO_SERVER"];


// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
// Setup a feed called 'backyardImages' for publishing.
Adafruit_MQTT_Publish backyardImages = Adafruit_MQTT_Publish(&mqtt, feed);


// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

uint16_t backyardImage = 9;
uint16_t flag = 1;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("waiting to connect to wifi");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  if (flag != 0){
    Serial.print(F("Sending backyard image "));
    Serial.print(backyardImage);
    Serial.print("...");
    if (! backyardImages.publish(backyardImage)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  }

  flag = 0;
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
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