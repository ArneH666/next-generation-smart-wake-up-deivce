#include <Arduino.h>
#include "PinModeSetter.hpp"
#include "Pins.hpp"

// TODO: Set the pin modes for all pins.

void setInputPins();

void setOutputPins();

void setSpecialPins();

namespace lib {
    void setPinModes() {
        setInputPins();
        setOutputPins();
        setSpecialPins();
    }
} // lib

void setInputPins() {
}

void setOutputPins() {
}

void setSpecialPins() {
}