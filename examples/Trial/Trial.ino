#include <MycilaTrial.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)
    continue;

  Mycila::Trial.begin();
}

void loop() {
  Serial.printf("Remaining: %d\n", Mycila::Trial.getRemaining());
  Serial.println(Mycila::Trial.isExpired() ? "Expired" : "Not expired");
  Mycila::Trial.validate();
  delay(1000);
}
