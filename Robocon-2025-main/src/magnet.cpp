#include <Arduino.h>
#include "magnet.h"

void turnOnAndTurnOffMagnet(char cmd){
    if(cmd == 'P'){
        digitalWrite(MAGNET_PIN, HIGH);
    }
    if(cmd == 'T'){
        digitalWrite(MAGNET_PIN, LOW);
    }
}
