#pragma once

// ============================================================
// BOARD-SPECIFIC PIN CONFIGURATION
// ============================================================

#if defined(BOARD_ESP32_C6)

// Bench detector board
static constexpr int PIN_TRIGGER_INPUT = 4;
static constexpr int PIN_STATUS_LED    = 5;

#elif defined(BOARD_WROOM32E)

#if defined(ROLE_DETECTOR)

static constexpr int PIN_TRIGGER_INPUT = 23;
static constexpr int PIN_STATUS_LED    = 22;

#elif defined(ROLE_CONTROLLER)

static constexpr int PIN_CLAP_OUTPUT = 23;
static constexpr int PIN_TEST_BUTTON = 22;

#endif

#elif defined(BOARD_XIAO_C3)

// End-user XIAO ESP32-C3 hardware
// These are role-dependent below.

#if defined(ROLE_DETECTOR)

static constexpr int PIN_TRIGGER_INPUT = D0;
static constexpr int PIN_STATUS_LED    = D1;

#elif defined(ROLE_CONTROLLER)

static constexpr int PIN_CLAP_OUTPUT = D0;
static constexpr int PIN_TEST_BUTTON = D1;

#endif

#else
#error "No supported board configuration selected."
#endif
