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
EnvConfig::EnvConfig(){
}


const char * EnvConfig::GetDoc(char element[],char element1[]){
    json = F("{$env_variables}");
    DeserializationError err = deserializeJson(doc, json);
    if (err) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(err.c_str());
    }
    else{
        Serial.print("deserialized successfully");
        Serial.println();
    }
    return doc[element][element1];
}
EnvConfig::~EnvConfig(){
    delete json;
}



