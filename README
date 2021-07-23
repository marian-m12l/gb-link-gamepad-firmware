This firmware for the Raspberry Pi Pico makes it appear like a USB HID gamepad.
It gets the inputs from GB serial link cable, thus the Game Boy must be running [this custom rom](https://github.com/marian-m12l/gb-link-gamepad-rom) sending inputs over serial.

Build instructions:

```
PICO_SDK_FETCH_FROM_GIT=1 cmake .
make
cp gbgamepad.uf2 /path/to/pico/mountpoint/
```
