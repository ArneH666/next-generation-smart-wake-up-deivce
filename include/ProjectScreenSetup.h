// See SetupX_Template.h for all options available
#pragma once
#define USER_SETUP_ID 21

#define ILI9488_DRIVER

#define TFT_BL 32
#define TFT_BACKLIGHT_ON HIGH

#define TFT_MISO 19  // (TFT SDO *NOT* CONNECTED!)
#define TFT_MOSI 23
#define TFT_SCLK 25
#define TFT_CS 15
#define TFT_DC 2
#define TFT_RST 4

#define TOUCH_CS 13

#define LOAD_GLCD

#define SPI_FREQUENCY 60000000
#define SPI_READ_FREQUENCY 16000000
#define SPI_TOUCH_FREQUENCY 2500000
