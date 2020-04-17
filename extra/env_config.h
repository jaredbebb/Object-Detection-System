#include <ArduinoJson.h>

class EnvConfig{
    private:
        const __FlashStringHelper* json;
        StaticJsonDocument<512> doc;
    public:
        EnvConfig();
        ~EnvConfig();
        //StaticJsonDocument<200> filter;
        const char * GetDoc(char element[],char element1[]);
};
