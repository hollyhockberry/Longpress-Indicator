// longpress-indicator for M5Atom
// Copyright (c) 2021 Inaba

#include <M5Atom.h>
#include "longpressindicator.h"

namespace {
LongPressIndicator indicator(&M5.dis);
}  // namespace

void setup() {
  M5.begin(true, false, true);
  indicator.begin();
}

void loop() {
  M5.update();
  if (indicator.loop(&M5.Btn)) {
    Serial.println("pressed!");
  }
}
