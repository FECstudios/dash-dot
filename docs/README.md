# Dash Stem Head

Dash is a compact STEM toy shaped like a robot head. It includes a NeoPixel ring, motion sensor, speaker, microphone, and four buttons.

## Why we built it

Many educational STEM kits are expensive, making them difficult for schools and families to afford. Dash is designed to be a low-cost, easy-to-build learning toy for kids.

## How we built it

The enclosure is designed in Fusion 360 and 3D printed in PLA. The electronics are assembled from affordable, off-the-shelf components.

### Components

- 12 LED NeoPixel ring (5050)           x 1
- 5×5 mm buttons                        x 5
- MPU6050 accelerometer + gyro sensor   x 1
- MAX98357A amplifier                   x 1
- 8 Ω 1 W 45 mm speaker                 x 1
- ESP32-C3 supermini                    x 1
- TP4056 LiPo / Li-ion charging module  x 1
- 1800 mAh Li-ion 2×14500 battery       x 1
- INMP441 omnidirectional microphone    x 1

## Features

You can program Dash yourself. The current preprogrammed modes include:

- Top button: starts a hot potato game. The LED ring slowly shifts toward red while the speaker pitch rises. Players pass Dash around, and the player holding it when it turns red is eliminated.
- Button 1: replays audio captured from the microphone and visualizes volume on the LED ring. Warning: this mode may produce echo.
- Button 2: activates lightsaber mode. The MPU6050 detects motion and the speaker plays synthesized saber sounds while the NeoPixel ring lights respond to movement.
- Button 3: visualizes live microphone input on the NeoPixel ring.

## Notes

- The current build uses synthesized sound effects rather than recorded sound files to keep the design compact and avoid adding an SD card reader.
- The firmware and CAD files are stored in the repository under `firmware/` and `CAD/`.


