// SPDX-License-Identifier: MIT
/*
 * Copyright (C) 2023-2024 Mathieu Carbou and others
 */
#pragma once

#include <Preferences.h>
#include <stdint.h>

#define MYCILA_TRIAL_VERSION "1.0.0"
#define MYCILA_TRIAL_VERSION_MAJOR 1
#define MYCILA_TRIAL_VERSION_MINOR 0
#define MYCILA_TRIAL_VERSION_REVISION 0

#ifndef MYCILA_TRIAL_DURATION
#define MYCILA_TRIAL_DURATION 86400 // 1 day in seconds
#endif

namespace Mycila {
  class TrialClass {
    public:
      void begin();
      void end();

      void validate();
      bool isExpired() const;
      // trial remaining time in seconds
      uint32_t getRemaining() const;

      void reset();

    private:
      uint32_t _lastSave = 0;
      uint32_t _lastUsed = 0;
      Preferences _prefs;
  };

  extern TrialClass Trial;
} // namespace Mycila
