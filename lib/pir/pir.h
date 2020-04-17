#include "Arduino.h"

class Pir{
    private:
        int sensorPin = 13;
        volatile byte state = LOW;
    public:
        Pir(int pin);
        void enable(void);
        void event(void);
        byte get_state();
};