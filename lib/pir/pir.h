#include "Arduino.h"

class Pir{
    private:
        int sensorPin = 5;
    public:
        Pir(int pin);
        void enable(void);
        void event(void);
        byte get_state();
        int sensor_pin();
        volatile byte state = LOW;

};