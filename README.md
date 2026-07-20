# SilentVoice

SilentVoice is a wearable sign-language recognition glove built with an Arduino, five flex sensors, and a 16x2 I2C LCD. It reads finger-bend data in real time and displays a corresponding word or phrase on the LCD, giving a voice to common gestures.

Full build guide (parts list, wiring, and assembly photos): [Build Your Own Sign Language Recognition Glove](https://www.instructables.com/Build-Your-Own-Sign-Language-Recognition-Glove-Usi)

![Uploading image.png…]()


## How It Works

- Five flex sensors (thumb, index, middle, ring, little) are wired to analog pins `A0`, `A1`, `A2`, `A3`, and `A6`.
- Each loop iteration reads the analog values, compares them against per-finger thresholds, and derives a boolean bend state for each finger.
- The resulting 5-bit pattern is matched against a set of gestures, and the matched word is shown on a 16x2 I2C LCD (address `0x27`).
- Raw sensor readings are also streamed over Serial (9600 baud) for calibration and debugging.

## Hardware

- Arduino (Uno/Nano or compatible)
- 5x flex sensors
- 16x2 I2C LCD (PCF8574-based, address `0x27`)
- Glove and wiring/mounting hardware

See the Instructable linked above for the full wiring diagram and voltage-divider setup for the flex sensors.

## Gesture Map

| Fingers Bent (T/I/M/R/L) | Word/Phrase |
|---|---|
| All five | EMERGENCY |
| Thumb + Index | YES |
| Thumb + Middle | NO |
| Thumb + Ring | PLEASE |
| Thumb + Little | FOOD |
| Thumb only | HELLO |
| Index only | FOOD |
| Middle only | WATER |
| Ring only | HELP |
| Little only | THANK YOU |
| None / other combinations | READY |

## Software Setup

1. Install the Arduino IDE.
2. Install the `LiquidCrystal_I2C` library (Library Manager or via GitHub).
3. Open `silentvoice.ino`, select your board and port, and upload.
4. Open the Serial Monitor at 9600 baud to view live sensor readings while calibrating.

## Calibration

The threshold constants near the top of `silentvoice.ino` (`THUMB_THRESHOLD`, `INDEX_THRESHOLD`, etc.) may need adjustment based on your specific flex sensors and wiring. Watch the Serial Monitor output while flexing each finger and tune the thresholds so a bent finger reliably reads above its threshold and a straight finger reads below it.

## License

This project is open source — see the linked Instructable for full build details and feel free to adapt it for your own use.
