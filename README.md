# Arduino Environmental Monitor

This Arduino-based project measures and displays **temperature**, **humidity**, **carbon monoxide (CO) concentration**, and the **current time** on an LCD display. It utilizes the following sensors and modules:

* **DHT11**: for temperature and humidity readings
* **MQ-7**: for CO concentration
* **DS3231 Real-Time Clock (RTC)**: for accurate timekeeping
* **16x2 LCD Display**: for visual output using I2C

## Features

* Real-time display of:

  * Ambient temperature (°C)
  * Humidity (%)
  * CO concentration (ppm, approximate)
  * Current date and time
* Modular design using standard Arduino libraries
* Suitable for indoor air quality monitoring and educational purposes

## Components Used

* Arduino Uno (or compatible board)
* DHT11 temperature and humidity sensor
* MQ-7 carbon monoxide sensor
* DS3231 real-time clock module
* 16x2 I2C LCD display
* Jumper wires, breadboard, power source

## Libraries Required

Make sure to install the following libraries via the Arduino Library Manager:

* `DHT sensor library` by Adafruit
* `Adafruit Unified Sensor`
* `LiquidCrystal_I2C`
* `RTClib` by Adafruit

## Setup Instructions

1. Connect all components to the Arduino according to standard pin assignments.
2. Upload the provided sketch to your Arduino using the Arduino IDE.
3. Ensure the RTC is set with the correct time on the first run.
4. Open the Serial Monitor (optional) for debugging output.

## License

This project is open-source and available under the [MIT License](LICENSE).
