// SPDX-License-Identifier: MIT
/*
 * Copyright (C) 2023-2024 Mathieu Carbou
 */
#include <MycilaTrial.h>

#include <esp32-hal-timer.h>

#ifdef MYCILA_LOGGER_SUPPORT
#include <MycilaLogger.h>
extern Mycila::Logger logger;
#define LOGD(tag, format, ...) logger.debug(tag, format, ##__VA_ARGS__)
#define LOGI(tag, format, ...) logger.info(tag, format, ##__VA_ARGS__)
#define LOGW(tag, format, ...) logger.warn(tag, format, ##__VA_ARGS__)
#define LOGE(tag, format, ...) logger.error(tag, format, ##__VA_ARGS__)
#else
#define LOGD(tag, format, ...) ESP_LOGD(tag, format, ##__VA_ARGS__)
#define LOGI(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)
#define LOGW(tag, format, ...) ESP_LOGW(tag, format, ##__VA_ARGS__)
#define LOGE(tag, format, ...) ESP_LOGE(tag, format, ##__VA_ARGS__)
#endif

#define TAG "TRIAL"

void Mycila::TrialClass::begin() {
  _prefs.begin("MycilaTrial");
  _lastUsed = _prefs.getLong("duration", 0);
  _lastSave = 0;
}

void Mycila::TrialClass::end() {
  _prefs.end();
}

void Mycila::TrialClass::validate() {
  if (_lastUsed >= MYCILA_TRIAL_DURATION) {
    LOGE(TAG, "Trial expired");
    while (true) {
      delay(1000);
    }
  }

  const uint32_t now = millis();
  const uint32_t deltaMillis = now - _lastSave;
  _lastUsed = _lastUsed + deltaMillis / 1000;
  _prefs.putLong("duration", _lastUsed);
  _lastSave = now;

  LOGD(TAG, "%" PRIu32 " seconds left for trial", getRemaining());

  if (_lastUsed >= MYCILA_TRIAL_DURATION) {
    LOGE(TAG, "Trial expired");
    while (true) {
      delay(1000);
    }
  }
}

bool Mycila::TrialClass::isExpired() const {
  const uint32_t deltaMillis = millis() - _lastSave;
  const uint32_t totalSecs = _lastUsed + deltaMillis / 1000;
  return totalSecs >= static_cast<uint32_t>(MYCILA_TRIAL_DURATION);
}

uint32_t Mycila::TrialClass::getRemaining() const {
  const uint32_t deltaMillis = millis() - _lastSave;
  const uint32_t totalSecs = _lastUsed + deltaMillis / 1000;
  return totalSecs >= static_cast<uint32_t>(MYCILA_TRIAL_DURATION) ? 0 : static_cast<uint32_t>(MYCILA_TRIAL_DURATION) - totalSecs;
}

void Mycila::TrialClass::reset() {
  LOGD(TAG, "Resetting trial");
  _prefs.clear();
  _lastSave = 0;
  _lastUsed = 0;
}

namespace Mycila {
  TrialClass Trial;
} // namespace Mycila
