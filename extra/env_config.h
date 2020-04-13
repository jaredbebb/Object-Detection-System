#include <ArduinoJson.h>

class EnvConfig{
    private:
    public:
        StaticJsonDocument<512> doc;
        EnvConfig(char element[]);
        ~EnvConfig();
        StaticJsonDocument<200> filter;
        StaticJsonDocument<512> GetDoc();
};
