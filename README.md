# Kaleidoscope-LED-LetterGuesser

![status][st:experimental] [![Build Status][travis:image]][travis:status]

 [travis:image]: https://travis-ci.org/keyboardio/Kaleidoscope-LED-LetterGuesser.svg?branch=master
 [travis:status]: https://travis-ci.org/keyboardio/Kaleidoscope-LED-LetterGuesser

 [st:stable]: https://img.shields.io/badge/stable-✔-black.svg?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.svg?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.svg?style=flat&colorA=dfb317&colorB=494e52

LetterGuesser is an LED effect that tries to 'guess' the next letter you will
type.  It leverages knowledge about common digraphs (in English) to light up
'guessed' or 'suggested' letters after each key you press.  By default the
most likely letter will be illuminated in green, and the 2nd and 3rd most
likely letters will be illuminated in white.  Colors are configurable.

By default, LetterGuesser goes blank after any keypress that is not a letter.
Optionally, LetterGuesser can be configured to also 'guess' letters following
whitespace (space, enter, and tab).  (In this case, LetterGuesser guesses the
first letter of the next word.)

At the moment, LetterGuesser only works properly with the QWERTY layout.
If you have a non-QWERTY layout, LetterGuesser will receive the correct input
key based on your layout, but will light up suggestions based on the
suggestions' QWERTY positions.

## Using the plugin

To use the plugin, one needs to include the header and select the effect.
Optionally, one can also set the colors to be used for the 1st, 2nd, and 3rd
most likely next letters.

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-LED-LetterGuesser.h>

void setup (){
  Kaleidoscope.use(&LetterGuesser);

  Kaleidoscope.setup();

  LetterGuesserEffect.color1 = CRGB(0, 255, 0);
  LetterGuesserEffect.color2 = CRGB(255, 255, 255);
  LetterGuesserEffect.color3 = CRGB(255, 255, 255);
  LetterGuesserEffect.activate();
}
```

## Plugin methods

The plugin provides the `LetterGuesserEffect` object, which has the following
properties:

### `.color1`, `.color2`, and `.color3`

> The colors for the 1st, 2nd, and 3rd most likely next letters.

### `.afterSpace`

> If `true`, highlight letters following whitespace (space, enter, and tab).
> If `false` (default), no letters are highlighted following whitespace.

## Dependencies

* [Kaleidoscope-LEDControl](https://github.com/keyboardio/Kaleidoscope-LEDControl)

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: https://github.com/keyboardio/Kaleidoscope-LED-LetterGuesser/blob/master/examples/LED-LetterGuesser/LED-LetterGuesser.ino
