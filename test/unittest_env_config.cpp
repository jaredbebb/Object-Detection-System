#include <Arduino.h>
#include <unity.h>
#include "env_config.h"
#include <iostream>
#include <pir.h>

 EnvConfig adafruit_config;
void TestGetAdafruitDoc(){
    char * Adafruit = "AdaFruit";

    char * aio_server = "AIO_SERVER";
    const char* AIO_SERVER = adafruit_config.GetDoc(Adafruit,aio_server);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("io.adafruit.com",AIO_SERVER,15);


    char * aio_serverport = "AIO_SERVERPORT";
    const char* AIO_SERVERPORT = adafruit_config.GetDoc(Adafruit,aio_serverport);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("1883",AIO_SERVERPORT,4);

    char * aio_feed = "AIO_FEED";
    const char* AIO_FEED = adafruit_config.GetDoc(Adafruit,aio_feed);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("AIO_USERNAME/feeds/feedname",AIO_FEED,26);
}

EnvConfig network_config;
void TestGetNetworkDoc(){ 
    char * Network = "Network";

    char * wlan_ssid = "WLAN_SSID";
    const char* WLAN_SSID = network_config.GetDoc(Network,wlan_ssid);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("SSID",WLAN_SSID,4);
    
    char * wlan_pass = "WLAN_PASS";
    const char* WLAN_PASS = network_config.GetDoc(Network,wlan_pass);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("PASSWORD",WLAN_PASS,4);
}

void TestPIR(){
    Pir pir(13);
    pir.enable();
    UNITY_TEST_ASSERT(LOW == pir.get_state(),"line","message");
}

void setup() {
    delay(2000); // for Arduino framework
    Serial.begin(115200);
    Serial.println(F("Setup test"));
}

/*
Please note that you will need to use #ifdef UNIT_TEST and #endif guard to hide non-test related source code. For example, own main() or setup() / loop() functions.
*/
uint16_t flag = 1;
void loop(){
    if (flag){
        Serial.println(F("loop test"));
        UNITY_BEGIN();
        RUN_TEST(TestGetAdafruitDoc);
        RUN_TEST(TestGetNetworkDoc);
        RUN_TEST(TestPIR);
        UNITY_END();
        delay(2000);
        flag = 0;
    }

}

