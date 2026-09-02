#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "config.h"
#include "wireless.h"

#if defined(ROLE_DETECTOR)

// TEMPORARY broadcast address.
// We'll replace this with the controller MAC after first test.
uint8_t controllerAddress[] = {
    0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF
};

uint32_t sequenceNumber = 0;

void onDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
    Serial.print("ESP-NOW send: ");

    if (status == ESP_NOW_SEND_SUCCESS) {
        Serial.println("SUCCESS");
    } else {
        Serial.println("FAILED");
    }
}

#endif


#if defined(ROLE_CONTROLLER)

void onDataReceived(
    const esp_now_recv_info_t *info,
    const uint8_t *data,
    int length
) {
    if (length != sizeof(ClapMessage)) {
        return;
    }

    ClapMessage message;
    memcpy(&message, data, sizeof(message));

    if (message.trigger) {
        Serial.print("CLAP RECEIVED #");
        Serial.println(message.sequence);
    }
}

#endif


void setup() {
    Serial.begin(115200);
    delay(500);

    WiFi.mode(WIFI_STA);

    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW INIT FAILED");
        return;
    }

#if defined(ROLE_DETECTOR)

    pinMode(PIN_TRIGGER_INPUT, INPUT);
    pinMode(PIN_STATUS_LED, OUTPUT);

    digitalWrite(PIN_STATUS_LED, LOW);

    esp_now_register_send_cb(onDataSent);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, controllerAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("FAILED TO ADD PEER");
    }

    Serial.println("ESP32 Clapper - DETECTOR");

#elif defined(ROLE_CONTROLLER)

    pinMode(PIN_CLAP_OUTPUT, OUTPUT);
    pinMode(PIN_TEST_BUTTON, INPUT_PULLUP);

    digitalWrite(PIN_CLAP_OUTPUT, LOW);

    esp_now_register_recv_cb(onDataReceived);

    Serial.println("ESP32 Clapper - CONTROLLER");

#endif
}


void loop() {

#if defined(ROLE_DETECTOR)

    static bool previousState = LOW;

    bool currentState = digitalRead(PIN_TRIGGER_INPUT);

    if (currentState == HIGH && previousState == LOW) {

        digitalWrite(PIN_STATUS_LED, HIGH);

        ClapMessage message;
        message.sequence = ++sequenceNumber;
        message.trigger = true;

        esp_err_t result = esp_now_send(
            controllerAddress,
            reinterpret_cast<uint8_t *>(&message),
            sizeof(message)
        );

        Serial.print("TRIGGER DETECTED #");
        Serial.println(sequenceNumber);

        if (result != ESP_OK) {
            Serial.println("SEND CALL FAILED");
        }
    }

    if (currentState == LOW) {
        digitalWrite(PIN_STATUS_LED, LOW);
    }

    previousState = currentState;

#endif
}
