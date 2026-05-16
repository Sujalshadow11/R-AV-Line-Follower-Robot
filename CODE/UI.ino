#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <EEPROM.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#endif

static const unsigned char PROGMEM image_car_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xf0,0x00,0x0c,0x88,0x00,0x18,0x84,0x00,0x7f,0xff,0xc0,0xf7,0xfd,0xa0,0xeb,0xfa,0xe0,0x55,0xf5,0x40,0x08,0x02,0x00};

static const unsigned char PROGMEM image_More_data_placeholder_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0xa8};

static const unsigned char PROGMEM image_More_data_placeholder__copy__bits[] = {0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0xa8,0x00};

static const unsigned char PROGMEM image_refresh_bits[] = {0x00,0x00,0x0f,0x90,0x3f,0xd0,0x70,0xf0,0x40,0x70,0xc1,0xf0,0x80,0x00,0x80,0x00,0x80,0x08,0x00,0x08,0x7c,0x08,0x70,0x10,0x78,0x70,0x5f,0xe0,0x4f,0x80,0x00,0x00};

static const unsigned char PROGMEM image_Detailed_chip_bits[] = {0x3f,0xfe,0x00,0x40,0x01,0x00,0x88,0x88,0x80,0x89,0x48,0x80,0xfa,0x0f,0x80,0x84,0x10,0x80,0x84,0x10,0x80,0x84,0x10,0x80,0xfa,0x2f,0x80,0x89,0x48,0x80,0x88,0x88,0x80,0x40,0x01,0x00,0x3f,0xfe,0x00};

static const unsigned char PROGMEM image_GameMode_bits[] = {0x04,0x00,0x7f,0xc0,0xdf,0xe0,0x8e,0xa0,0xdf,0xe0,0xf1,0xe0,0xe0,0xe0,0xc0,0x60};

static const unsigned char PROGMEM image_menu_tool_wrench_bits[] = {0x00,0x00,0x00,0xe0,0x01,0x60,0x02,0x80,0x02,0x8c,0x03,0x0c,0x02,0xb4,0x02,0x48,0x05,0xf0,0x0a,0x00,0x14,0x00,0x28,0x00,0x50,0x00,0xa0,0x00,0xc0,0x00,0x00,0x00};

static const unsigned char PROGMEM image_InfraredArrowUp_bits[] = {0x18,0x3c,0x7e,0xff};

static const unsigned char PROGMEM image_InfraredArrowDown_bits[] = {0xff,0x7e,0x3c,0x18};

static const unsigned char PROGMEM image_menu_tools_bits[] = {0x80,0xe0,0xc1,0x60,0x42,0x80,0x22,0x8c,0x13,0x0c,0x0a,0xb4,0x06,0x48,0x05,0xf0,0x0b,0x00,0x14,0xe0,0x29,0xb0,0x50,0xd8,0xa0,0x6c,0xc0,0x34,0x00,0x1c,0x00,0x00};

#define FRAME_DELAY (21)
#define FRAME_WIDTH (32)
#define FRAME_HEIGHT (32)
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))
const byte PROGMEM frames[][128] = {
  {0,1,254,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,254,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,254,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,127,0,0,0,35,0,0,0,50,0,0,0,22,0,0,0,28,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,30,0,0,0,19,128,0,0,49,128,0,0,51,0,0,0,50,0,0,0,38,0,0,0,44,0,0,0,56,0,0,0,56,0,0,0,48,0,0,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,252,0,0,1,204,0,0,1,12,0,0,1,8,0,0,3,8,0,0,2,16,0,0,2,16,0,0,6,16,0,0,4,32,0,0,4,32,0,0,12,32,0,0,8,126,0,0,8,118,0,0,24,6,0,0,25,4,0,0,31,136,0,0,0,136,0,0,1,144,0,0,1,48,0,0,1,32,0,0,1,96,0,0,1,64,0,0,3,192,0,0,3,128,0,0,3,128,0,0,3,0,0,0,7,0,0,0,6,0,0,0,4,0,0,0,4,0,0,0,0,0,0},
  {0,0,0,0,0,1,252,0,0,1,12,0,0,3,8,0,0,2,24,0,0,2,24,0,0,6,16,0,0,4,48,0,0,12,32,0,0,12,96,0,0,8,96,0,0,24,64,0,0,24,254,0,0,16,126,0,0,48,12,0,0,55,8,0,0,63,24,0,0,1,48,0,0,3,48,0,0,3,96,0,0,2,64,0,0,6,192,0,0,6,128,0,0,5,128,0,0,7,0,0,0,14,0,0,0,14,0,0,0,12,0,0,0,28,0,0,0,24,0,0,0,16,0,0,0,0,0,0},
  {0,0,0,0,0,1,252,0,0,3,8,0,0,2,24,0,0,6,24,0,0,6,48,0,0,12,48,0,0,12,32,0,0,8,96,0,0,24,64,0,0,16,192,0,0,48,128,0,0,49,248,0,0,32,252,0,0,96,8,0,0,126,24,0,0,126,48,0,0,6,32,0,0,6,96,0,0,4,192,0,0,12,128,0,0,13,128,0,0,11,0,0,0,26,0,0,0,30,0,0,0,28,0,0,0,56,0,0,0,56,0,0,0,48,0,0,0,96,0,0,0,96,0,0,0,0,0,0},
  {0,0,0,0,0,1,254,0,0,1,132,0,0,1,12,0,0,3,12,0,0,2,24,0,0,6,24,0,0,6,16,0,0,12,48,0,0,12,32,0,0,8,96,0,0,24,64,0,0,16,254,0,0,48,126,0,0,48,4,0,0,63,12,0,0,63,24,0,0,3,16,0,0,3,48,0,0,2,96,0,0,6,64,0,0,6,192,0,0,5,128,0,0,13,0,0,0,15,0,0,0,14,0,0,0,28,0,0,0,28,0,0,0,24,0,0,0,48,0,0,0,48,0,0,0,0,0,0},
  {0,0,126,0,0,0,255,0,0,0,194,0,0,1,134,0,0,1,132,0,0,1,12,0,0,3,12,0,0,2,24,0,0,6,24,0,0,6,16,0,0,4,48,0,0,12,32,0,0,8,127,0,0,24,63,0,0,24,2,0,0,63,134,0,0,31,140,0,0,1,136,0,0,1,152,0,0,1,48,0,0,3,32,0,0,3,96,0,0,2,192,0,0,6,128,0,0,7,128,0,0,7,0,0,0,14,0,0,0,14,0,0,0,12,0,0,0,28,0,0,0,24,0,0,0,0,0,0},
  {0,0,254,0,0,0,254,0,0,1,134,0,0,1,4,0,0,3,12,0,0,3,8,0,0,6,24,0,0,6,24,0,0,4,48,0,0,12,48,0,0,8,96,0,0,24,96,0,0,24,126,0,0,16,126,0,0,48,6,0,0,63,12,0,0,63,136,0,0,1,24,0,0,3,48,0,0,3,32,0,0,2,96,0,0,6,192,0,0,6,192,0,0,5,128,0,0,15,0,0,0,15,0,0,0,14,0,0,0,28,0,0,0,28,0,0,0,24,0,0,0,48,0,0,0,0,0,0},
  {0,1,254,0,0,1,134,0,0,3,12,0,0,3,12,0,0,2,24,0,0,6,24,0,0,4,16,0,0,12,48,0,0,12,32,0,0,24,96,0,0,24,96,0,0,16,192,0,0,48,254,0,0,32,126,0,0,96,12,0,0,126,12,0,0,127,24,0,0,3,48,0,0,2,48,0,0,6,96,0,0,6,192,0,0,4,192,0,0,13,128,0,0,13,0,0,0,11,0,0,0,30,0,0,0,28,0,0,0,28,0,0,0,56,0,0,0,48,0,0,0,48,0,0,0,32,0,0},
  {0,1,254,0,0,1,134,0,0,3,12,0,0,3,12,0,0,2,24,0,0,6,24,0,0,4,16,0,0,12,48,0,0,12,32,0,0,24,96,0,0,24,96,0,0,16,192,0,0,48,254,0,0,32,126,0,0,96,12,0,0,126,12,0,0,127,24,0,0,3,48,0,0,2,48,0,0,6,96,0,0,6,192,0,0,4,192,0,0,13,128,0,0,13,0,0,0,11,0,0,0,30,0,0,0,28,0,0,0,28,0,0,0,56,0,0,0,48,0,0,0,48,0,0,0,32,0,0},
  {0,1,254,0,0,1,134,0,0,3,12,0,0,3,12,0,0,2,24,0,0,6,24,0,0,4,16,0,0,12,48,0,0,12,32,0,0,24,96,0,0,24,96,0,0,16,192,0,0,48,254,0,0,32,126,0,0,96,12,0,0,126,12,0,0,127,24,0,0,3,48,0,0,2,48,0,0,6,96,0,0,6,192,0,0,4,192,0,0,13,128,0,0,13,0,0,0,11,0,0,0,30,0,0,0,28,0,0,0,28,0,0,0,56,0,0,0,48,0,0,0,48,0,0,0,32,0,0},
  {0,1,254,0,0,1,134,0,0,3,12,0,0,3,12,0,0,2,24,0,0,6,24,0,0,4,16,0,0,12,48,0,0,12,32,0,0,24,96,0,0,24,96,0,0,16,192,0,0,48,254,0,0,32,126,0,0,96,12,0,0,126,12,0,0,127,24,0,0,3,48,0,0,2,48,0,0,6,96,0,0,6,192,0,0,4,192,0,0,13,128,0,0,13,0,0,0,11,0,0,0,30,0,0,0,28,0,0,0,28,0,0,0,56,0,0,0,48,0,0,0,48,0,0,0,32,0,0},
  {0,1,254,0,0,1,134,0,0,3,12,0,0,3,12,0,0,2,24,0,0,6,24,0,0,4,16,0,0,12,48,0,0,12,32,0,0,24,96,0,0,24,96,0,0,16,192,0,0,48,254,0,0,32,126,0,0,96,12,0,0,126,12,0,0,127,24,0,0,3,48,0,0,2,48,0,0,6,96,0,0,6,192,0,0,4,192,0,0,13,128,0,0,13,0,0,0,11,0,0,0,30,0,0,0,28,0,0,0,28,0,0,0,56,0,0,0,48,0,0,0,48,0,0,0,32,0,0},
  {0,1,254,0,0,1,134,0,0,3,12,0,0,3,12,0,0,2,24,0,0,6,24,0,0,4,16,0,0,12,48,0,0,12,32,0,0,24,96,0,0,24,96,0,0,16,192,0,0,48,254,0,0,32,126,0,0,96,12,0,0,126,12,0,0,127,24,0,0,3,48,0,0,2,48,0,0,6,96,0,0,6,192,0,0,4,192,0,0,13,128,0,0,13,0,0,0,11,0,0,0,30,0,0,0,28,0,0,0,28,0,0,0,56,0,0,0,48,0,0,0,48,0,0,0,32,0,0},
  {0,1,254,0,0,1,134,0,0,3,12,0,0,3,12,0,0,2,24,0,0,6,24,0,0,4,16,0,0,12,48,0,0,12,32,0,0,24,96,0,0,24,96,0,0,16,192,0,0,48,254,0,0,32,126,0,0,96,12,0,0,126,12,0,0,127,24,0,0,3,48,0,0,2,48,0,0,6,96,0,0,6,192,0,0,4,192,0,0,13,128,0,0,13,0,0,0,11,0,0,0,30,0,0,0,28,0,0,0,28,0,0,0,56,0,0,0,48,0,0,0,48,0,0,0,32,0,0},
  {0,0,254,0,0,1,254,0,0,3,12,0,0,3,12,0,0,2,8,0,0,6,24,0,0,4,16,0,0,12,48,0,0,12,32,0,0,8,96,0,0,24,96,0,0,16,192,0,0,48,254,0,0,48,126,0,0,96,12,0,0,126,8,0,0,127,24,0,0,3,48,0,0,2,48,0,0,6,96,0,0,6,192,0,0,4,192,0,0,13,128,0,0,15,0,0,0,11,0,0,0,30,0,0,0,28,0,0,0,28,0,0,0,56,0,0,0,48,0,0,0,48,0,0,0,32,0,0},
  {0,0,252,0,0,1,254,0,0,1,12,0,0,3,12,0,0,2,8,0,0,6,24,0,0,6,16,0,0,12,48,0,0,12,32,0,0,8,96,0,0,24,96,0,0,16,192,0,0,48,254,0,0,48,254,0,0,32,12,0,0,126,8,0,0,63,24,0,0,3,48,0,0,2,32,0,0,6,96,0,0,6,192,0,0,4,128,0,0,13,128,0,0,15,0,0,0,11,0,0,0,30,0,0,0,28,0,0,0,28,0,0,0,56,0,0,0,48,0,0,0,48,0,0,0,0,0,0},
  {0,0,0,0,0,1,252,0,0,1,12,0,0,3,12,0,0,2,8,0,0,6,24,0,0,6,16,0,0,4,48,0,0,12,32,0,0,8,96,0,0,24,96,0,0,24,192,0,0,16,252,0,0,48,254,0,0,32,12,0,0,126,8,0,0,63,24,0,0,3,48,0,0,2,32,0,0,6,96,0,0,6,192,0,0,4,128,0,0,13,128,0,0,15,0,0,0,10,0,0,0,30,0,0,0,28,0,0,0,24,0,0,0,56,0,0,0,48,0,0,0,32,0,0,0,0,0,0},
  {0,0,0,0,0,1,252,0,0,1,12,0,0,3,12,0,0,3,8,0,0,2,24,0,0,6,16,0,0,4,48,0,0,12,32,0,0,8,96,0,0,24,96,0,0,24,192,0,0,16,252,0,0,48,126,0,0,32,12,0,0,126,8,0,0,63,24,0,0,3,48,0,0,2,32,0,0,6,96,0,0,6,192,0,0,4,128,0,0,13,128,0,0,15,0,0,0,10,0,0,0,30,0,0,0,28,0,0,0,24,0,0,0,56,0,0,0,48,0,0,0,32,0,0,0,0,0,0},
  {0,0,0,0,0,1,248,0,0,3,8,0,0,3,24,0,0,2,24,0,0,6,16,0,0,4,48,0,0,12,32,0,0,12,96,0,0,8,96,0,0,24,64,0,0,24,192,0,0,16,252,0,0,48,252,0,0,48,12,0,0,38,24,0,0,63,16,0,0,3,48,0,0,2,32,0,0,2,96,0,0,6,192,0,0,6,128,0,0,5,128,0,0,5,0,0,0,15,0,0,0,14,0,0,0,12,0,0,0,28,0,0,0,24,0,0,0,24,0,0,0,16,0,0,0,0,0,0},
  {0,0,0,0,0,1,248,0,0,3,24,0,0,2,16,0,0,6,48,0,0,4,48,0,0,4,32,0,0,12,96,0,0,8,96,0,0,8,64,0,0,24,192,0,0,24,192,0,0,16,252,0,0,48,204,0,0,48,8,0,0,34,24,0,0,63,16,0,0,3,48,0,0,3,32,0,0,2,96,0,0,2,64,0,0,6,192,0,0,7,128,0,0,5,128,0,0,7,0,0,0,14,0,0,0,14,0,0,0,12,0,0,0,12,0,0,0,24,0,0,0,16,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,60,0,0,0,39,0,0,0,35,0,0,0,98,0,0,0,100,0,0,0,108,0,0,0,104,0,0,0,80,0,0,0,112,0,0,0,96,0,0,0,96,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,126,0,0,0,102,0,0,0,38,0,0,0,52,0,0,0,28,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,254,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,254,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
int address=0;
int frame = 0;
int counter = 1;
int c1=1;
int okon=0;
int counterUDV = 0;
void calibrated(){
  display.clearDisplay();
  display.drawRect(0, 0, 121, 18, 1);
  display.drawBitmap(1, 15, image_car_bits, 19, 16, 1);
  display.drawBitmap(-2, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(8, 27, image_More_data_placeholder__copy__bits, 10, 5, 1);
  display.drawBitmap(26, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(32, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(38, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(44, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(50, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(56, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(62, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(68, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(74, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(80, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(86, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(92, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(98, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(104, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(110, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(116, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(4, 1, image_refresh_bits, 13, 16, 1);
  display.drawBitmap(122, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30, 5);
  display.print("Calibrate");
  display.drawBitmap(20, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.display();
}
void code1(){
  display.clearDisplay();
  display.drawRect(0, 0, 121 , 18, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30, 5);
  display.print(" CODE 1");
  display.drawBitmap(8, 15, image_car_bits, 19, 16, 1);
  display.drawBitmap(0, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(6, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(15, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(26, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(32, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(38, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(44, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(50, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(56, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(62, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(68, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(74, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(80, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(86, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(92, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(98, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(104, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(110, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(116, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(122, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(26, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(4, 2, image_Detailed_chip_bits, 17, 13, 1);
  display.display();
}
void code2(){
  display.clearDisplay();
  display.drawRect(0, 0, 121, 18, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30, 5);
  display.print(" CODE 2");
  display.drawBitmap(15, 15, image_car_bits, 19, 16, 1);
  display.drawBitmap(0, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(6, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(12, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(23, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(32, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(38, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(44, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(50, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(56, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(62, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(68, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(74, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(80, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(86, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(92, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(98, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(104, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(110, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(116, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(122, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(4, 2, image_Detailed_chip_bits, 17, 13, 1);
  display.display();
}
void code3(){
  display.clearDisplay();
  display.drawRect(0, 0, 121, 18, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30,5);
  display.print(" CODE 3");
  display.drawBitmap(20, 15, image_car_bits, 19, 16, 1);
  display.drawBitmap(0, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(12, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(18, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(27, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(38, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(44, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(50, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(56, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(62, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(68, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(74, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(80, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(86, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(92, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(98, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(104, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(110, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(116, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(122, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(6, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(4, 2, image_Detailed_chip_bits, 17, 13, 1);
  display.display();
}
void code4(){
  display.clearDisplay();
  display.drawRect(0, 0, 121, 18, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30,5);
  display.print(" CODE 4");
  display.drawBitmap(26, 15, image_car_bits, 19, 16, 1);
  display.drawBitmap(0, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(12, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(18, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(24, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(33, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(44, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(50, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(56, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(62, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(68, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(74, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(80, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(86, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(92, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(98, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(104, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(110, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(116, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(122, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(6, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(4, 2, image_Detailed_chip_bits, 17, 13, 1);
  display.display();
}
void code5(){
  display.clearDisplay();
  display.drawRect(0, 0, 121, 18, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30,5);
  display.print(" CODE 5");
  display.drawBitmap(32, 15, image_car_bits, 19, 16, 1);
  display.drawBitmap(0, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(12, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(18, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(24, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(29, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(40, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(50, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(56, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(62, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(68, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(74, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(80, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(86, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(92, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(98, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(104, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(110, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(116, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(122, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(6, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(4, 2, image_Detailed_chip_bits, 17, 13, 1);
  display.display();
}
void Kdtune(){
  display.clearDisplay();
  display.drawRect(0, 0, 121, 18, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30,5);
  display.print("Kd Tuning");
  display.setCursor(30, 20);
  display.print("Ki Tuning");
  display.drawBitmap(3, 1, image_menu_tool_wrench_bits, 14, 16, 1);
  display.display();
}
void Kptune(){
  display.clearDisplay();
  display.drawRect(0, 0, 121, 18, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30,5);
  display.print("Kp Tuning");
  display.setCursor(30,20);
  display.print("Kd Tuning");
  display.drawBitmap(3, 1, image_menu_tool_wrench_bits, 14, 16, 1);
  display.display();
}
void Kitune(){
  display.clearDisplay();
  display.drawRect(0, 0, 121, 18, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30,5);
  display.print("Ki Tuning");
  display.setCursor(30, 20);
  display.print("Run");
  display.drawBitmap(5, 20, image_GameMode_bits, 11, 8, 1);
  display.drawBitmap(3, 1, image_menu_tool_wrench_bits, 14, 16, 1);
  display.display();
}
void run(){
  display.clearDisplay();
  display.drawRect(0, 16, 121, 16, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(30,5);
  display.print("Ki Tuning");
  display.setCursor(30, 20);
  display.print("Run");
  display.drawBitmap(5, 20, image_GameMode_bits, 11, 8, 1);
  display.drawBitmap(3, 0, image_menu_tool_wrench_bits, 14, 16, 1);
  display.display();
}
void kpvalue(){
  display.clearDisplay();
  display.drawBitmap(94, 4, image_InfraredArrowUp_bits, 8, 4, 1);
  display.drawBitmap(94, 22, image_InfraredArrowDown_bits, 8, 4, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(34, 11);
  display.print("Kp:");
  display.setCursor(58, 11);
  display.print(EEPROM.read(address+1));
  display.setCursor(52, 11);
  display.print(EEPROM.read(address));
  display.setCursor(64, 11);
  display.print(EEPROM.read(address+2));
  display.setCursor(73, 11);
  display.print(EEPROM.read(address+3));
  display.setCursor(68, 11);
  display.print(".");
  display.setCursor(78, 11);
  display.print(EEPROM.read(address+4));
  display.setCursor(83, 11);
  display.print(EEPROM.read(address+5));
  display.drawBitmap(4, 7, image_menu_tools_bits, 14, 16, 1);
  display.display();
}
void kdvalue(){
  display.clearDisplay();
  display.drawBitmap(94, 4, image_InfraredArrowUp_bits, 8, 4, 1);
  display.drawBitmap(94, 22, image_InfraredArrowDown_bits, 8, 4, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(34, 11);
  display.print("Kd:");
  display.setCursor(58, 11);
  display.print(EEPROM.read(address+1));
  display.setCursor(52, 11);
  display.print(EEPROM.read(address));
  display.setCursor(64, 11);
  display.print(EEPROM.read(address+2));
  display.setCursor(73, 11);
  display.print(EEPROM.read(address+3));
  display.setCursor(68, 11);
  display.print(".");
  display.setCursor(78, 11);
  display.print(EEPROM.read(address+4));
  display.setCursor(83, 11);
  display.print(EEPROM.read(address+5));
  display.drawBitmap(4, 7, image_menu_tools_bits, 14, 16, 1);
  display.display();
}
void kivalue(){
  display.clearDisplay();
  display.drawBitmap(94, 4, image_InfraredArrowUp_bits, 8, 4, 1);
  display.drawBitmap(94, 22, image_InfraredArrowDown_bits, 8, 4, 1);
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setCursor(34, 11);
  display.print("Ki:");
  display.setCursor(58, 11);
  display.print(EEPROM.read(address+1));
  display.setCursor(52, 11);
  display.print(EEPROM.read(address));
  display.setCursor(64, 11);
  display.print(EEPROM.read(address+2));
  display.setCursor(73, 11);
  display.print(EEPROM.read(address+3));
  display.setCursor(68, 11);
  display.print(".");
  display.setCursor(78, 11);
  display.print(EEPROM.read(address+4));
  display.setCursor(83, 11);
  display.print(EEPROM.read(address+5));
  display.drawBitmap(4, 7, image_menu_tools_bits, 14, 16, 1);
  display.display();
}
void UI_INTERFACE(){
  if (digitalRead(29)==HIGH){
    counter=counter+1;
    delay(100);
  }
  if (digitalRead(31)==HIGH){
    counter=counter-1;
    delay(100);
  }
  if (digitalRead(30)==HIGH){
    okon=okon+1;
    delay(450);
  }
  if (digitalRead(28)==HIGH){
    counterUDV=counterUDV+1;
    delay(100);
  }
  if (digitalRead(32)==HIGH){
    counterUDV=counterUDV-1;
    delay(100);
  }
  if (okon>3){
    okon=0;
  }
  counterUDV=constrain(counterUDV,0,4);
  counter=constrain(counter,1,6);

  if(counter==1){
    calibrated();
    delay(75);
    //code calibrateright();
  }

  //code 1 functions UI
  if(counter==2 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }
  if(counter==2 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }
  if(counter==2 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }
  if(counter==2 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }
  if(counter==2 && okon==2 && counterUDV==0){
    address=0;
    kpvalue();
    delay(75);
    if(counter==2 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
          
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==2 && okon==2 && counterUDV==1){
    address=6;
    kdvalue();
    delay(75);
    if(counter==2 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==2 && okon==2 && counterUDV==2){
    address=12;
    kivalue();
    delay(75);
    if(counter==2 && okon==3 && counterUDV==0){
      while(okon==3){
        address=6;
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  // code 1 interface UI
  if(counter==2 && okon==0){
    code1();
    delay(75);
  }

  //code 2 functions UI
  if(counter==3 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }
  if(counter==3 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }
  if(counter==3 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }
  if(counter==3 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }
  if(counter==3 && okon==2 && counterUDV==0){
    address=18;
    kpvalue();
    delay(75);
    if(counter==3 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==3 && okon==2 && counterUDV==1){
    address=24;
    kdvalue();
    delay(75);
    if(counter==3 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==3 && okon==2 && counterUDV==2){
    address=30;
    kivalue();
    delay(75);
    if(counter==3 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }

  // code 2 interface UI
  if(counter==3 && okon==0){
    code2();
    delay(75);
  }

  //code 3 functions UI
  if(counter==4 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }
  if(counter==4 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }
  if(counter==4 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }
  if(counter==4 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }
  if(counter==4 && okon==2 && counterUDV==0){
    address=36;
    kpvalue();
    delay(75);
    if(counter==4 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==4 && okon==2 && counterUDV==1){
    address=42;
    kdvalue();
    delay(75);
    if(counter==4 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==4 && okon==2 && counterUDV==2){
    address=48;
    kivalue();
    delay(75);
    if(counter==4 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }

  //code 3 interface UI
  if(counter==4 && okon==0){
    code3();
    delay(75);
  }

  //code 4 functions UI
  if(counter==5 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }
  if(counter==5 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }
  if(counter==5 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }
  if(counter==5 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }
  if(counter==5 && okon==2 && counterUDV==0){
    address=54;
    kpvalue();
    delay(75);
    if(counter==5 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==5 && okon==2 && counterUDV==1){
    address=60;
    kdvalue();
    delay(75);
    if(counter==5 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==5 && okon==2 && counterUDV==2){
    address=66;
    kivalue();
    delay(75);
    if(counter==5 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }

  //code 4 interface UI
  if(counter==5 && okon==0){
    code4();
    delay(75);
  }

  //code 5 functions UI
  if(counter==6 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }
  if(counter==6 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }
  if(counter==6 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }
  if(counter==6 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }
  if(counter==6 && okon==2 && counterUDV==0){
    address=72;
    kpvalue();
    delay(75);
    if(counter==6 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==6 && okon==2 && counterUDV==1){
    address=78;
    kdvalue();
    delay(75);
    if(counter==6 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }
  if(counter==6 && okon==2 && counterUDV==2){
    address=84;
    kivalue();
    delay(75);
    if(counter==6 && okon==3 && counterUDV==0){
      while(okon==3){
        if(digitalRead(32)==HIGH){
        }
        if(digitalRead(28)==HIGH){
        }
      }
    }
  }

  //code 5 interface UI
  if(counter==6 && okon==0){
    code5();
    delay(75);
  }
}

void setup(){
  // initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();
  for(int i=0; i<28; i++){
    display.clearDisplay();
    display.drawBitmap(48, 1, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
    display.display();
    frame = (frame + 1) % FRAME_COUNT;
    delay(FRAME_DELAY);
    display.display();
  }
  pinMode(13,OUTPUT);
  pinMode(28,INPUT_PULLUP); //Down
  pinMode(29,INPUT_PULLUP); //Right
  pinMode(30,INPUT_PULLUP); //Ok
  pinMode(31,INPUT_PULLUP); //Left
  pinMode(32,INPUT_PULLUP); //Up
  // for(int i=0;i<100;i++){
  //   EEPROM.write(i,0);
  // }
}
void loop() {
  UI_INTERFACE();
}