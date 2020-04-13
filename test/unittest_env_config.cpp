#include <Arduino.h>
#include <unity.h>
#include "env_config.h"
#include <iostream>


EnvConfig adafruit_config("AdaFruit");
void TestGetDoc(){
    const char* AIO_SERVER = adafruit_config.GetDoc()["AdaFruit"]["AIO_SERVER"];
    TEST_ASSERT_EQUAL_CHAR_ARRAY("io.adafruit.com",AIO_SERVER,15);
    
    const char* AIO_SERVERPORT = adafruit_config.GetDoc()["AdaFruit"]["AIO_SERVERPORT"];
    TEST_ASSERT_EQUAL_CHAR_ARRAY("1883",AIO_SERVERPORT,4);
}

void setup() {
    delay(2000); // for Arduino framework
    Serial.begin(115200);
    Serial.println(F("Setup test"));
}

/*
Please note that you will need to use #ifdef UNIT_TEST and #endif guard to hide non-test related source code. For example, own main() or setup() / loop() functions.
*/
void loop(){
    Serial.println(F("loop test"));
    UNITY_BEGIN();
    RUN_TEST(TestGetDoc);
    UNITY_END();
    delay(2000);
}

