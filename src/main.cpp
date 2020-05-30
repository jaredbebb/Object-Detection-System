//https://github.com/bitluni/ESP32CameraI2S/blob/master/ESP32_I2S_Camera/ESP32_I2S_Camera.ino

#include "OV7670.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include "BMP.h"
#include <pir.h>

#include <env_config.h>

//Wifi credentials
EnvConfig network_config;
char * Network = "Network";
const char* WLAN_SSID  = network_config.GetDoc(Network,"WLAN_SSID");
const char* WLAN_PASS  = network_config.GetDoc(Network,"WLAN_PASS");


//mqtt credentials
char * MQQTT = "MQTT";
EnvConfig mqtt_config;
const char* MQTT_TOPIC  = mqtt_config.GetDoc(MQQTT,"MQTT_TOPIC");
const char* MQTT_USERNAME  = mqtt_config.GetDoc(MQQTT,"MQTT_USERNAME");
const char* MQTT_KEY  = mqtt_config.GetDoc(MQQTT,"MQTT_KEY");
const char* MQTT_SERVER  = mqtt_config.GetDoc(MQQTT,"MQTT_SERVER");
//const char* MQTT_SERVERPORT  = mqtt_config.GetDoc(Network,"MQTT_SERVERPORT");
#define MQTT_SERVERPORT  1883

#include "MQTTStuff.h"

Pir pir(25);

OV7670 *camera;

WiFiMulti wifiMulti;

WiFiServer server(80);

unsigned char bmpHeader[BMP::headerSize];


void IRAM_ATTR isr(void* arg){
//gpio_isr_t  isr() {
    pir.state = !pir.state;
    if(pir.state == HIGH) {
        //digitalWrite (Status, HIGH);
        Serial.println("Motion detected!");
    }
    else {
        //digitalWrite (Status, LOW);
        // Serial.println("Motion absent!");
    } 
}

void MQTT_connect() {
    WiFiClient client = server.available();
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
        // close the connection:
    int retry = 3;
    while(retry > 0){
        int response = mqttcamera.publish(WiFi.localIP().toString().c_str());
        Serial.println(response);
        retry--;
        Serial.print("retry:");
        Serial.println(retry);
        delay(1000);
    }

    client.stop();
}


void serve()
{
  WiFiClient client = server.available();
  if (client) 
  {
    //Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        //Serial.write(c);
        if (c == '\n') 
        {
          if (currentLine.length() == 0) 
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(
              "<style>body{margin: 0}\nimg{height: 100%; width: auto}</style>"
              "<img id='a' src='/camera' onload='this.style.display=\"initial\"; var b = document.getElementById(\"b\"); b.style.display=\"none\"; b.src=\"camera?\"+Date.now(); '>"
              "<img id='b' style='display: none' src='/camera' onload='this.style.display=\"initial\"; var a = document.getElementById(\"a\"); a.style.display=\"none\"; a.src=\"camera?\"+Date.now(); '>");
            client.println();
            break;
          } 
          else 
          {
            currentLine = "";
          }
        } 
        else if (c != '\r') 
        {
          currentLine += c;
        }
        
        if(currentLine.endsWith("GET /camera"))
        {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:image/bmp");
            client.println();
            
            client.write(bmpHeader, BMP::headerSize);
            client.write(camera->frame, camera->xres * camera->yres * 2);
        }
      }
    }
    // close the connection:
    client.stop();
    //Serial.println("Client Disconnected.");
  }  
}

void SystemDetails(){
  log_d("Total heap: %d", ESP.getHeapSize());
  log_d("Free heap: %d", ESP.getFreeHeap());
  log_d("Total PSRAM: %d", ESP.getPsramSize());
  log_d("Free PSRAM: %d", ESP.getFreePsram());
  
  log_d("getMaxAllocPsram: %d", ESP.getMaxAllocPsram());
  log_d("getFlashChipSpeed: %d", ESP.getFlashChipSpeed());
  log_d("getMinFreePsram: %d", ESP.getMinFreePsram());
  log_d("getChipRevision: %d", ESP.getChipRevision());
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    int SIOD = 21; //SDA
    int SIOC = 22; //SCL

    int VSYNC = 34;
    int HREF = 35;

    int XCLK = 32;
    int PCLK = 33;

    int D0 = 27;
    int D1 = 17;
    int D2 = 16;
    int D3 = 15;
    int D4 = 14;
    int D5 = 13;
    int D6 = 12;
    int D7 = 4;

    wifiMulti.addAP(WLAN_SSID, WLAN_PASS);
    Serial.println("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    camera = new OV7670(OV7670::Mode::QQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
    BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
    server.begin();
    SystemDetails();
    MQTT_connect();
    esp_err_t err;
    err = gpio_isr_handler_add(GPIO_NUM_25, &isr, (void *) 25);
    if (err != ESP_OK) {
      Serial.printf("handler add failed with error 0x%x \r\n", err);
    }
    err = gpio_set_intr_type(GPIO_NUM_25, GPIO_INTR_POSEDGE);
    if (err != ESP_OK) {
      Serial.printf("set intr type failed with error 0x%x \r\n", err);
    }
}

void loop() {
    camera->oneFrame();
    serve();
}