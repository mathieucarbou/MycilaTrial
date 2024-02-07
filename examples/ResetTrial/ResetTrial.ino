#define MYCILA_TRIAL_DURATION 15

#include <MycilaTrial.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)
    continue;

  Mycila::Trial.begin();
  Mycila::Trial.reset();
  Mycila::Trial.end();
}

void loop() {
  delay(1000);
}

