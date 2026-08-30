#include <Arduino.h>
#include "config.h"

void setup() {
    Serial.begin(115200);
    delay(500);

#if defined(ROLE_DETECTOR)

    pinMode(PIN_TRIGGER_INPUT, INPUT);
    pinMode(PIN_STATUS_LED, OUTPUT);

    Serial.println("ESP32 Clapper - DETECTOR");

#elif defined(ROLE_CONTROLLER)

    pinMode(PIN_CLAP_OUTPUT, OUTPUT);
    pinMode(PIN_TEST_BUTTON, INPUT_PULLUP);

    digitalWrite(PIN_CLAP_OUTPUT, LOW);

    Serial.println("ESP32 Clapper - CONTROLLER");

#endif
}
void loop() {

#if defined(ROLE_DETECTOR)

    static bool previousState = LOW;
    bool currentState = digitalRead(PIN_TRIGGER_INPUT);

    if (currentState == HIGH && previousState == LOW) {
        Serial.println("TRIGGER DETECTED");
        digitalWrite(PIN_STATUS_LED, HIGH);
    }

    if (currentState == LOW) {
        digitalWrite(PIN_STATUS_LED, LOW);
    }

    previousState = currentState;

#endif
}
