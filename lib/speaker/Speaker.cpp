#include "Speaker.hpp"

#include <Arduino.h>
#include <cc.h>
#include <driver/i2s.h>

#include <Pins.hpp>

#define SAMPLE_RATE 16000
#define TONE_FREQ 1000.0f
#define AMPLITUDE 1000

constexpr uint32_t TONE_ON_TIME = 500;
constexpr uint32_t TONE_OFF_TIME = 500;
static constexpr i2s_port_t I2S_PORT = I2S_NUM_0;

namespace speaker {
Speaker::Speaker() {
  constexpr i2s_config_t i2s_config = {
      .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 8,
      .dma_buf_len = 256,
      .use_apll = false,
      .tx_desc_auto_clear = true,
      .fixed_mclk = 0};

  constexpr i2s_pin_config_t pin_config = {
      .bck_io_num = SPEAKER_AMPLIFIER_BCLK,
      .ws_io_num = SPEAKER_AMPLIFIER_LRC,
      .data_out_num = SPEAKER_AMPLIFIER_DIN,
      .data_in_num = I2S_PIN_NO_CHANGE};

  i2s_driver_install(I2S_PORT, &i2s_config, 0, nullptr);
  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_zero_dma_buffer(I2S_PORT);
}

void Speaker::startAlarm() { this->alarm_active = true; }
void Speaker::endAlarm() { this->alarm_active = false; }

void Speaker::writeAlarm() {
  if (!this->alarm_active) {
    Serial.println("Not activated");
    return;
  }

  Serial.println("RINGING");

  const unsigned long now = millis();

  if (this->tone_state == TONE_ON) {
    if (now - this->last_toggle >= TONE_ON_TIME) {
      this->tone_state = TONE_OFF;
      this->last_toggle = now;
    }
  } else {
    if (now - this->last_toggle >= TONE_OFF_TIME) {
      this->tone_state = TONE_ON;
      this->last_toggle = now;
    }
  }

  if (this->tone_state == TONE_ON) {
    generateTone(this->audio_buffer);
  } else {
    generateSilence(this->audio_buffer);
  }

  size_t bytesWritten;
  i2s_write(I2S_PORT, this->audio_buffer, sizeof(this->audio_buffer),
            &bytesWritten, 0);
}

void Speaker::generateTone(int16_t *buffer) {
  constexpr float phaseStep = 2.0f * PI * TONE_FREQ / SAMPLE_RATE;

  for (int i = 0; i < BUFFER_SAMPLES; i++) {
    buffer[i] = static_cast<int16_t>(sinf(this->phase) * AMPLITUDE);
    this->phase += phaseStep;
    if (this->phase >= 2.0f * PI) this->phase -= 2.0f * PI;
  }
}

void Speaker::generateSilence(int16_t *buffer) {
  memset(buffer, 0, BUFFER_SAMPLES * sizeof(int16_t));
}
}  // namespace speaker