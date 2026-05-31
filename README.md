# DEJI-V.1
It's code for my first dasai mochi with IOT using chronos app.

Components/Wiring Diagram:
1. Buzzer
- VCC ==> Pin 5 Esp32-C3
- GND ==> GND Esp32-C3

2. USB Charging Module
- B+ ==> Lipo Battery VCC
- B- ==> Lipo Battery GND
- OUT- ==> GND Esp32-C3
- OUT+ ==> Center Switch

3. OLED Display
- VCC ==> Esp32-C3 3.3V Pin
- GND ==> Esp32-C3 GND Pin
- SCL ==> Esp32-C3 Pin 9
- SDA ==> Esp32-C3 Pin 8

4. Touch Sensor
- VCC ==> Esp32-C3 3.7V Pin
- I/O ==> Esp32-C3 Pin 4
- GND ==> GND Esp32-C3

5. Toggle Switch
- Center Pin ==> OUT+ USB Module
- Right/Left Pins ==> 5V Pin Esp32-C3


Boards Manager Download:
1. Arduino AVR Boards by Arduino
2. Esp32 by Espressif Systems

Library Manager Download:
1. Adafruit BusIO by Adafruit
2. Adafruit DotStar by Adafruit
3. Adafruit GFX Library by Adafruit
4. Adafruit SSD1306 by Adafruit
5. ChronosEsp32 by fbiego
6. Esp32Time by fbiego
7. NimBLE-Arduino by h2zero
