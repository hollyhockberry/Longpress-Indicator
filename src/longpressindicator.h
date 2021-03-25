// Copyright (c) 2021 Inaba

#ifndef LONGPRESSINDICATOR_H_
#define LONGPRESSINDICATOR_H_

#include "utility/Button.h"
#include "utility/LED_Display.h"

class LongPressIndicator {
 public:
  explicit LongPressIndicator(LED_Display* dis);

  void begin();
  bool loop(Button* btn);

 private:
  LED_Display* dis_;
  int start_, phase_;
  bool rising(int phase);
  bool falling(int phase);
  bool blink(int phase);

  LongPressIndicator(const LongPressIndicator&);
  void operator =(const LongPressIndicator&);
};
#endif  // LONGPRESSINDICATOR_H_
