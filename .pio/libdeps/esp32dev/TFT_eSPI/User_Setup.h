// User Setup for the ESP32 TouchDown V1.0 and V1.1
// ILI9488 using 4-wire SPI and using an FT6206 touch controller

// ReSharper disable once CppMissingIncludeGuard
#define USER_SETUP_ID 204

#define ILI9488_DRIVER

#define TFT_BL   32
#define TFT_BACKLIGHT_ON HIGH

#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 25
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST   4

#define TOUCH_CS 13
#define TOUCH_

#define LOAD_GLCD

#define SPI_FREQUENCY  60000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000