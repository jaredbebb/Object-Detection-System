#include "pir.h" 
#include "Arduino.h"
#include "FunctionalInterrupt.h"

// pin is the input pin for the pir
Pir::Pir(int pin){
    sensorPin = pin;
    pinMode(sensorPin, INPUT_PULLUP);   
}

void Pir::event(void){
    state = !state;
    if(state == HIGH) {
        //digitalWrite (Status, HIGH);
        Serial.println("Motion detected!");
    }
    else {
        //digitalWrite (Status, LOW);
        // Serial.println("Motion absent!");
    } 
}

void Pir::enable(void){
    Serial.println("Enabling pir...");
    attachInterrupt(sensorPin, std::bind(&Pir::event,this), CHANGE);
    Serial.println("Pir enabled...");
}

byte Pir::get_state(){
    return state;
}