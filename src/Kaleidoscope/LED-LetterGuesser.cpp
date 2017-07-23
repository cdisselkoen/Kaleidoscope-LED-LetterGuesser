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

#include <Kaleidoscope-LED-LetterGuesser.h>

namespace kaleidoscope {

const LetterGuesserEffect::LEDTriple LetterGuesserEffect::dict[26] = {
  // data comes from gist.github.com/lydell/c439049abac2c9226e53, which comes from norvig.com/mayzner.html
#define TRIPLE(FIRST, SECOND, THIRD) { LED_##FIRST, LED_##SECOND, LED_##THIRD }
  /* A */ TRIPLE(N,T,L),
  /* B */ TRIPLE(E,L,O),
  /* C */ TRIPLE(O,E,H),
  /* D */ TRIPLE(E,I,O),
  /* E */ TRIPLE(R,N,S),
  /* F */ TRIPLE(O,I,E),
  /* G */ TRIPLE(E,H,R),
  /* H */ TRIPLE(E,A,I),
  /* I */ TRIPLE(N,S,T),
  /* J */ TRIPLE(U,O,E),
  /* K */ TRIPLE(E,I,N),
  /* L */ TRIPLE(E,I,L),
  /* M */ TRIPLE(E,A,O),
  /* N */ TRIPLE(D,T,G),
  /* O */ TRIPLE(N,R,F),
  /* P */ TRIPLE(E,R,O),
  /* Q */ TRIPLE(U,I,L),  // data doesn't lie, but "QL"?
  /* R */ TRIPLE(E,I,O),
  /* S */ TRIPLE(T,E,I),
  /* T */ TRIPLE(H,I,E),
  /* U */ TRIPLE(R,S,T),
  /* V */ TRIPLE(E,I,A),
  /* W */ TRIPLE(A,H,I),
  /* X */ TRIPLE(P,T,I),
  /* Y */ TRIPLE(O,S,E),
  /* Z */ TRIPLE(E,A,I),
};

const cRGB LetterGuesserEffect::blank = CRGB(0,0,0);

LetterGuesserEffect::LetterGuesserEffect(void)
  : color1(CRGB(0,255,0)), color2(CRGB(255,255,255)), color3(CRGB(255,255,255)),
    afterSpace(false), isLit(false)
{}

void LetterGuesserEffect::begin(void) {
  Kaleidoscope.useEventHandlerHook(eventHandlerHook);
  LEDMode::begin();
}

void LetterGuesserEffect::init(void) {}

Key LetterGuesserEffect::last_key_pressed = Key_Escape;
bool LetterGuesserEffect::changed = false;

Key LetterGuesserEffect::eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state) {
  if (key_is_pressed(key_state)) {
    if(isModifier(mapped_key)) {
      // leave previous lighting in place
      return mapped_key;
    }

    // Lighting will update on next update().
    // Can't do it here because this is a static function.
    last_key_pressed = mapped_key;
    changed = true;
  }
  return mapped_key;
}

void LetterGuesserEffect::update(void) {
  if(changed) {
    changed = false;
    if(isLit) {
      // turn off previously lit keys
      LEDControl.led_set_crgb_at(currentlyLit.guess1, blank);
      LEDControl.led_set_crgb_at(currentlyLit.guess2, blank);
      LEDControl.led_set_crgb_at(currentlyLit.guess3, blank);
    }
    if(isAlpha(last_key_pressed) || (afterSpace && isWhitespace(last_key_pressed))) {
      // illuminate new guesses
      if(isAlpha(last_key_pressed)) currentlyLit = dict[last_key_pressed.keyCode-Key_A.keyCode];  // A gets 0, B gets 1, etc
      else currentlyLit = TRIPLE(T,A,O);  // after whitespace
      LEDControl.led_set_crgb_at(currentlyLit.guess1, color1);
      LEDControl.led_set_crgb_at(currentlyLit.guess2, color2);
      LEDControl.led_set_crgb_at(currentlyLit.guess3, color3);
      isLit = true;
    } else {
      isLit = false;
    }
  }
}

bool LetterGuesserEffect::isAlpha(const Key k) {
  return ( k.keyCode >= Key_A.keyCode &&
           k.keyCode <= Key_Z.keyCode );
}

bool LetterGuesserEffect::isModifier(const Key k) {
  return (k.keyCode & 0xF0) == 0xE0;
}

bool LetterGuesserEffect::isWhitespace(const Key k) {
  return ( k.keyCode == Key_Spacebar.keyCode ||
           k.keyCode == Key_Enter.keyCode    ||
           k.keyCode == Key_Tab.keyCode      );
}

#undef TRIPLE

}

kaleidoscope::LetterGuesserEffect LetterGuesserEffect;
