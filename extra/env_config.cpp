#include <Arduino.h>
#include <env_config.h>

/*
json = F(
    {
        "AdaFruit":{
            "AIO_FEED":"AIO_USERNAME/feeds/feedname",
            "AIO_USERNAME":"AIO_USERNAME",
            "AIO_KEY":"AIO_KEY",
            "AIO_SERVERPORT":"1883",
            "AIO_SERVER":"io.adafruit.com"
        },
        "Network":{
            "WLAN_SSID":"SSID",
            "WLAN_PASS":"PASSWORD"
        }
    }
)
*/
EnvConfig::EnvConfig(char element[]){
    Serial.begin(115200);
    filter[element] = true;
    const __FlashStringHelper* json = F("{$env_variables}");
    DeserializationError err = deserializeJson(doc, json, DeserializationOption::Filter(filter));
    if (err) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(err.c_str());
    }
    else{
        Serial.print("deserialized successfully");
        Serial.println();
    }
}

StaticJsonDocument<512> EnvConfig::GetDoc(){
    return doc;
}

EnvConfig::~EnvConfig(){}


