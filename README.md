# Dash Stem Head

Dash is a compact STEM toy shaped like a robot head. It includes a NeoPixel ring, motion sensor, speaker, microphone, and four buttons.
---
## Gallery

<div align="center">

# 3D Render
<img src="https://github.com/user-attachments/assets/3aeea935-03bc-4f0b-bd3c-0ca0e9fda41f" width="450"/>

---

# Schematics
<img src="https://github.com/user-attachments/assets/8aae4814-d6af-4e10-ba98-9f98607f5c97" width="900"/>

---

# Real Photos
<img src="https://cdn.hackclub.com/019efe8c-a1a7-7eda-b523-a54bf9585839/image.png" width="450"/>

</div>

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


## Bill of Materials (BoM)

| Part | Qty | Cost (TL) | Link |
|------|----:|------------------:|---------------|
| ESP32-C3 Super Mini | 1 | 365.65 | https://www.trendyol.com/genel-markalar/esp32-c3-super-mini-gelistirme-karti-wifi-bluetooth-type-c-usb-160mhz-4mb-flash-400kb-psram-p-809775652 |
| MPU6050 6-Axis Accelerometer & Gyroscope | 1 | 123.15 | https://www.robotistan.com/mpu6050-6-eksen-ivme-ve-gyro-sensoru-6-dof-3-axis-accelerometer-and-gyros |
| WS2812B NeoPixel Ring (12 LEDs, 50 mm) | 1 | 83.00 | https://www.robo90.com/ws2812b-neopixel-halka-led-12-bit-50mm |
| MAX98357A I2S 3W Audio Amplifier | 1 | 126.96 | https://www.robo90.com/max98357-i2s-3w-amplifikator-modulu |
| INMP441 Omnidirectional I2S Microphone | 1 | 138.00 | https://robiz.net/inmp441 |
| TP4056 USB-C Li-ion Charging Module | 1 | 16.56 | https://www.robo90.com/tp4056-lityum-pil-sarj-modulu-5v-1a-type-c |
| 3.7 V 1800 mAh 14500 Li-ion Battery | 1 | 429.00 | https://www.trendyol.com/voltify-enerji/3-7v-1800-mah-14500-li-ion-oyuncak-araba-pili-p-831832503 |
| 8 Ω 1 W 45 mm Speaker | 1 | 50.76 | https://www.motorobit.com/hoparlor-8ohm-1w-45mm |
| 6×6×5 mm Tactile Push Button | 5 | 10.40 | https://www.robotistan.com/4-pinli-push-buton-siyah-6x6x5mm |
| WS2812B Addressable LED | 2 | 5.40 | https://www.robolinkmarket.com/ws2812b-adreslenebilir-led |
| **Total Estimated Cost** |  | **₺1,354.28** | |

## Steps to Reproduce

1. Order all of the parts listed in the Bill of Materials.
2. 3D print the parts from the `CAD/` folder.
3. Assemble the electronics by following the schematic above.
4. Open `firmware/arduino.ino` in the Arduino IDE.
5. Select *ESP32-C3 Super Mini*, choose the correct port, and upload the firmware.
6. Turn the device on and test each button, the LED ring, speaker, microphone, and motion sensor to make sure everything works.

## Features

You can program Dash yourself. The current preprogrammed modes include:

- Top button: starts a hot potato game. The LED ring slowly shifts toward red while the speaker pitch rises. Players pass Dash around, and the player holding it when it turns red is eliminated.
- Button 1: replays audio captured from the microphone and visualizes volume on the LED ring. Warning: this mode may produce echo.
- Button 2: activates lightsaber mode. The MPU6050 detects motion and the speaker plays synthesized saber sounds while the NeoPixel ring lights respond to movement.
- Button 3: visualizes live microphone input on the NeoPixel ring.

## Firmware

The code works without any changes but if you want to add custom modes or other features you can always modify the code or maybe even create a pull request or remix (Code can be found at firmware/arduino.ino)

## Notes

- The current build uses synthesized sound effects rather than recorded sound files to keep the design compact and avoid adding an SD card reader.
- The firmware and CAD files are stored in the repository under `firmware/` and `CAD/`.


