# Pinout

## ESP32 Pins to Components

| ESP32 Pin | Component Pin      | Special Condition |
|-----------|--------------------|-------------------|
| 2         | TFT DC             |                   |
| 4         | TFT RST            |                   |
| (12)      |                    | LOW during boot   |
| 13        | TOUCH CS           |                   |
| 14        |                    |                   |
| (15)      | TFT CS             | HIGH during boot  |
| 16        | Servo Data         |                   |
| 17        | Motor DRV Forward  |                   |
| 18        | Motor DRV Backward |                   |
| 19        | TFT Miso           |                   |
| 21        | SDA                | I2C               |
| 22        | SCL                | I2C               |
| 23        | TFT Mosi           |                   |
| 25        | TFT SCLK           |                   |
| 26        |                    |                   |
| 27        |                    |                   |
| 32        | TFT Backlight      |                   |
| 33        | US-Sensor Trig     |                   |
| 34        | US-Sensor Echo     | INPUT ONLY        |
| 35        |                    | INPUT ONLY        |
| 36        |                    | INPUT ONLY        |
| 39        |                    | INPUT ONLY        |

## ESP32

- Power:
  - Startup: max. 700mA
  - max cont: 250mA

## Ultrasonic distance sensor

- Power
  - 5V
  - 15mA
- **Output at 5V?**

## BME280

- Power:
  - 3.3V
  - 3.6uA

## Speaker driver

- Power
  - 5V
  - max typ: 400mA
  - max peak: 1.5A

## Servo Motor
- Power:
  - 5V
  - ~430mA

## Display

- Power:
  - 3.3V
  - Backlight: about 150mA
  - 15mA Controller
