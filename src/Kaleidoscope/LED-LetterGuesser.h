/* -*- mode: c++ -*-
 * Kaleidoscope-LED-LetterGuesser -- Illuminate the most likely 'guesses' for the next letter, based on previous key typed.
 * Copyright (C) 2017  Craig Disselkoen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <Kaleidoscope.h>
#include <Kaleidoscope-LEDControl.h>

namespace kaleidoscope {
class LetterGuesserEffect : public LEDMode {
 public:
  LetterGuesserEffect(void);

  void setup(void) final;
  void update(void) final;

  cRGB color1;
  cRGB color2;
  cRGB color3;
  bool afterSpace;

 private:
  typedef struct LEDTriple_ {  // contains led codes for the three keys
    uint8_t guess1;
    uint8_t guess2;
    uint8_t guess3;
  } LEDTriple;
  static const LEDTriple dict[26];
  LEDTriple currentlyLit;  // which keys are currently lit.  Keeping track of them makes it easier to blank the whole keyboard - rather than turn everything off, we know which keys specifically we need to target
  bool isLit;  // whether the keys in 'currentlyLit' are actually lit.  If this is false, the keyboard is blank.

  static Key last_key_pressed;
  static bool changed;  // whether last_key_pressed has changed recently, and needs to be handled

  static const cRGB blank;

  static bool isAlpha(const Key k);
  static bool isModifier(const Key k);
  static bool isWhitespace(const Key k);

  static Key eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state);
};
}

extern kaleidoscope::LetterGuesserEffect LetterGuesserEffect;
