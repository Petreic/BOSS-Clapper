#pragma once

#include <Arduino.h>

struct ClapMessage {
    uint32_t sequence;
    bool trigger;
};
