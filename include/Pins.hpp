#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_PINS_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_PINS_HPP
#include <cstdint>

// TODO: Set correct pins

// Pins:
constexpr uint8_t ULTRASONIC_SENSOR_TRIGGER_PIN = 33;
constexpr uint8_t ULTRASONIC_SENSOR_ECHO_PIN = 34;

constexpr uint8_t MOTOR_FORWARD_PIN = 17;
constexpr uint8_t MOTOR_REVERSE_PIN = 18;

constexpr uint8_t SERVO_STEERING_PIN = 16;

constexpr uint8_t SPEAKER_AMPLIFIER_LRC = 32;
constexpr uint8_t SPEAKER_AMPLIFIER_BCLK = 33;
constexpr uint8_t SPEAKER_AMPLIFIER_DIN = 25;

constexpr uint8_t DISPLAY_T_PEN = -1;
constexpr uint8_t DISPLAY_T_DO = -1;
constexpr uint8_t DISPLAY_T_DI = -1;
constexpr uint8_t DISPLAY_T_CS = -1;
constexpr uint8_t DISPLAY_T_CK = -1;
constexpr uint8_t DISPLAY_BL = -1;
constexpr uint8_t DISPLAY_SCK = -1;
constexpr uint8_t DISPLAY_SDI = -1;
constexpr uint8_t DISPLAY_D_C = -1;
constexpr uint8_t DISPLAY_RESET = -1;
constexpr uint8_t DISPLAY_CS = -1;

// Ledc Channels:
constexpr uint8_t SERVO_STEERING_CHANEL = 0;

#endif // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_PINS_HPP