// Copyright (c) 2021 Inaba

#include "longpressindicator.h"

LongPressIndicator::LongPressIndicator(LED_Display* dis)
: dis_(dis), start_(-1), phase_(-1) {
}

void LongPressIndicator::begin() {
  start_ = phase_ = -1;
  dis_->clear();
}

namespace {
const uint8_t pos[] = {
  0, 1, 2, 3, 4, 9, 14, 19, 24, 23, 22, 21, 20,
  15, 10, 5, 6, 7, 8, 13, 18, 17, 16, 11, 12
};
const int kPhaseTerm = 20;
const int kBlinkTimes = 3;
}  // namespace

bool LongPressIndicator::rising(int phase) {
  dis_->drawpix(pos[phase], 0xffffff);
  return false;
}

bool LongPressIndicator::falling(int phase) {
  dis_->drawpix(pos[phase], 0);
  return false;
}

bool LongPressIndicator::blink(int phase) {
  if ((phase % 10) != 0) return false;

  phase /= 10;
  if (phase > kBlinkTimes * 2) {
    return true;
  }

  if (phase % 2 == 0) {
    for (int i = 0; i < 25; ++i) {
      dis_->drawpix(i, 0xffffff);
    }
  } else {
    dis_->clear();
  }
  return false;
}

bool LongPressIndicator::loop(Button* btn) {
  if (btn->wasPressed()) {
    start_ = ::millis();
  } else if (btn->wasReleased()) {
    start_ = phase_ = -1;
    dis_->clear();
  } else if (start_ > 0) {
    int phase = (::millis() - start_) / kPhaseTerm;
    if (phase == phase_) return false;
    phase_ = phase;

    const int p = sizeof(pos) / sizeof(pos[0]);

    if (phase < p) {
      return rising(phase);
    } else if (phase < p * 2) {
      return falling(phase - p);
    } else {
      return blink(phase - p * 2);
    }
  }
  return false;
}
