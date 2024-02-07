# MycilaTrial

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Continuous Integration](https://github.com/mathieucarbou/MycilaTrial/actions/workflows/ci.yml/badge.svg)](https://github.com/mathieucarbou/MycilaTrial/actions/workflows/ci.yml)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/mathieucarbou/library/MycilaTrial.svg)](https://registry.platformio.org/libraries/mathieucarbou/MycilaTrial)

Arduino / ESP32 library to add a trial duration in your app

```c++
    Mycila::Trial.begin(); // called in setup()

    Mycila::Trial.validate(); // called in loop()
```

You can check the durations with `isExpired()` and `getRemaining()`

Units are in seconds.
