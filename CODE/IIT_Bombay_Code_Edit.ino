//----------------import files-------------------------------------
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <EEPROM.h>
#include <SparkFun_TB6612.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#endif

//-------------------touch sensor pins---------------------------------------------------------
#define UPB 30
#define DNB 31
#define LTB 29
#define RTB 28
#define OKB 32

//----------------- motor pins----------------------------------------------------
#define AIN1 10
#define AIN2 11
#define BIN1 8
#define BIN2 7
#define PWMA 12
#define PWMB 6
#define STBY 9

//--------------define speed--------------------------------------------
#define baseSpeed 90
#define fspeed 80
#define tspeed 80
#define fdelay 250
#define ldelay 658
#define rdelay 658
#define ts 220
#define ds1 150
#define ds2 160
#define  turnth 610
#define turning 130

int maxSize = 100;
int index1 = -1;
const int offsetA = 1;
const int offsetB = 1;

//-----------------left to right S1 to S16-----------------------------------------
const int sensorPins[10] = {A6,A3,A2,A1,A0,A17,A16,A13,A12,A11}; 

float minValues[10], maxValues[10], threshold[10];

Motor motor1 = Motor(AIN2, AIN1, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN2, BIN1, PWMB, offsetB, STBY);

int edge=0;
bool end=1,ans;

//-----------------------UI code----------------------------------------------------
static const unsigned char PROGMEM image_car_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xf0,0x00,0x0c,0x88,0x00,0x18,0x84,0x00,0x7f,0xff,0xc0,0xf7,0xfd,0xa0,0xeb,0xfa,0xe0,0x55,0xf5,0x40,0x08,0x02,0x00};
static const unsigned char PROGMEM image_More_data_placeholder_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0xa8};
static const unsigned char PROGMEM image_More_data_placeholder_copy_bits[] = {0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0xa8,0x00};
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
int counterUDV=0;
int PC=0;
int a=0;
float Kpo,Kdo,Kio;

//------------WHITE LOW - BLACK HIGH----------------

//------------------calibrate ui code--------------------------------
void calibrated(){
  display.clearDisplay();
  display.drawRect(0, 0, 121, 18, 1);
  display.drawBitmap(1, 15, image_car_bits, 19, 16, 1);
  display.drawBitmap(-2, 25, image_More_data_placeholder_bits, 5, 7, 1);
  display.drawBitmap(8, 27, image_More_data_placeholder_copy_bits, 10, 5, 1);
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

//-----------------------code1 ui----------------------------------------------
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

//----------------------code2 ui-----------------------------------------------
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

//---------------------------code3 ui----------------------------------------------
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

//------------------------------code4 ui------------------------------------------
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

//--------------------------------------code5 ui-----------------------------------
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

//------------------------kd tune ui code------------------------------------------
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

//------------------------------kp tune ui code-----------------------------------
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

//-------------------------------ki tune ui code-------------------------------
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

//-------------------------run ui code--------------------------------
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

//--------------------------------------kp value change ui code------------------------------------------
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

//--------------------------------------kd value change ui code---------------------------------------------
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

//----------------------------------ki value change ui code--------------------------------------------------
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

//------------------------------calibration code------------------------------------------------------------
void calibrateRight() {
  for (int i = 0; i < 10; i++) {
    minValues[i] = analogRead(sensorPins[i]);
    maxValues[i] = minValues[i];
  }
  right(motor2,motor1,255);

  for (int i = 0; i < 5000; i++) {
    delay(1);
    for (int j = 0; j < 10; j++) {
      int sensorValue = analogRead(sensorPins[j]);
      if (sensorValue < minValues[j]) {
        minValues[j] = sensorValue; 
      } 
      if (sensorValue > maxValues[j]) { 
        maxValues[j] = sensorValue; 
      } 
    } 
  } 

  for (int i = 0; i < 10; i++) {
    threshold[i] = (minValues[i] + maxValues[i]) / 2;
  }
  for (int i = 0; i < 10; i++) {
    float value=threshold[i];
    EEPROM.write(90+i,value);
  }
  brake(motor1, motor2);
}

//--------------------------------sensor read code-----------------------------------------------------------
int readSensor() {
  int sensorValues[10];
  int result = 0;

  for (int i = 0; i < 10 ; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    if (sensorValues[i] > threshold[i]) {
      result |= (1 << i); // Set the corresponding bit if the sensor is active
    }
  }
  return result;
}

//A0 to A1 because of 3cm line and 2 cm max distance between two sens giving 1cm offset
//-------------------------------------------pid code---------------------------------------------------
void PID(){
  int lef,rig;
  lef=analogRead(A1);
  rig=analogRead(A17);
  float Kp=Kpo,Kd=Kdo,Ki=Kio;
  float error=lef-rig;
  float preverror=0;
  float prop=error;
  float deriv;
  deriv=error-preverror;
  float integ=0;
  integ=integ+error; 
  float sol=(Kp*prop)+(Kd*deriv)+(Ki*integ);
  int speedr=baseSpeed-sol;   //+ black iine
  int speedl=baseSpeed+sol;
  int leftspeed=constrain(speedl,-255,255);
  int rightspeed=constrain(speedr,-255,255);
  motor2.drive(leftspeed);
  motor1.drive(rightspeed);
  preverror=error;
  lef=analogRead(A1);
  rig=analogRead(A17);
}


//--------------------------------------------run logic for code 1 code------------------------------------------
// 0 is white(line) and 1 is black
//right domination
void runLogic1(){
  int previousData=readSensor();
  int lef;
  int rig;
  lef = analogRead(A1);
  rig = analogRead(A17);
  previousData = readSensor();
  char path[maxSize]; 
  // right turn
  PID();
  previousData=readSensor();
  if(previousData == 0b0000001111 || previousData == 0b0000000111){
    right(motor2,motor1,turning);
    delay(100);
    forward(motor2, motor1,turning);
    delay(125);
    brake(motor1, motor2);
    delay(400);
    lef = analogRead(A0);
    rig = analogRead(A17);
    previousData=readSensor();
    while(lef>turnth){
      right(motor2,motor1, turning);
      delayMicroseconds(1);
      lef = analogRead(A0);
      rig = analogRead(A17);
    }
    index++;
    path[index] = 'R';
  }
  
  // T
  previousData=readSensor();
  if(previousData == 0b0000000000){
    previousData=readSensor();
    brake(motor1,motor2);
    delay(150);
    right(motor2,motor1,turning);
    delay(100);
    forward(motor2, motor1,turning);
    delay(125);
    brake(motor1, motor2);
    delay(400);
    lef = analogRead(A0);
    rig = analogRead(A17);
    while(lef > turnth && rig > turnth){
      right(motor2,motor1, turning);
      delayMicroseconds(1);
      lef = analogRead(A0);
      rig = analogRead(A17);
    }
    index++;
    path[index] = 'R';
  }
  
  // u turn or deadend
  previousData=readSensor();
  if(previousData == 0b1111111111){ 
    // digitalWrite(33,HIGH);
    // digitalWrite(34,HIGH);
    previousData=readSensor();
    brake(motor1,motor2);
    delay(150);
    forward(motor2, motor1,turning);
    delay(125);
    brake(motor1, motor2);
    delay(400);
    lef = analogRead(A0);
    rig = analogRead(A17);
    while(lef > turnth && rig > turnth){
      left(motor2, motor1, turning);
      delayMicroseconds(1);
      lef = analogRead(A0);
      rig = analogRead(A17);
      // digitalWrite(33,HIGH);
      // digitalWrite(34,HIGH);
    }
    index++;
    path[index] = 'B';
  }
  
  //left turn
  previousData=readSensor();
  if(previousData==0b1111000000 || previousData==0b1110000000){   
    previousData=readSensor();
    forward(motor2, motor1,turning);
    delay(125);
    lef=analogRead(A0);
    rig=analogRead(A17);
    if(lef > turnth && rig > turnth){
      index++;
      path[index] = 'S';
    }
    brake(motor1, motor2);
    delay(400);
    lef=analogRead(A0);
    rig=analogRead(A17);
    // digitalWrite(34, HIGH);
    while(rig>turnth){
      left(motor2,motor1,turning);
      delay(5);
      lef=analogRead(A0);
      rig=analogRead(A17);
      // digitalWrite(33, HIGH);   
    }
    brake(motor1,motor2);
    //digitalWrite(34, LOW);
    index++;
    path[index] = 'L';
  }
  previousData=readSensor();
}
//--------------------------------------------------- run logic 2------------------------------------------------------------------------------------------------------
// void runLogic2(){
// // char path[100]={'L','B','L','L','L','B','S','B','L','L','B','S','L','L'};
// // char raw[100]={'L','B','L','L','S','L','B','L','B','S','L','L','R','B','L','L','S','L','L','B','L','S','L','S','L','B','L','L','S','B','L','B','L','R','S','L','L','B','L','L','L','B','L','L','L','B','L','B','S','L','L','R'};
// char pro[100]={ };
// // code1Run();
// int i,j,k,l;
// // char x,y,z;
//     for(int a=0;a<100;a++){
        
//         for (i=0,j=0;i<100,j<100;i++,j++){
            
//             if(path[i]=='L' && path[i+1]=='B' && path[i+2]=='L'){
//                 pro[j]='S';
                
//                 for(k=(i+3);k<100;k++){
//                     pro[k-2]=path[k];
//                 }
                
//                 Serial.print("path");
//                 for (int m=0;m<100;m++){
//                     Serial.println(path[m]);
//                 }
                
                
//                 for(l=0;l<100;l++){
//                     path[l]=pro[l];
//                 }
                
                
                
//                 Serial.print("PRO");
//                 for (int m=0;m<100;m++){
//                     Serial.println(pro[m]);
//                 }
                
//                 break;
//                     // i=i+1;
//             }
            
//             else if(path[i]=='S' && path[i+1]=='B' && path[i+2]=='S'){
//                 pro[j]='B';
                
//                 for(k=(i+3);k<100;k++){
//                     pro[k-2]=path[k];
//                 }
            
//                 Serial.print("path");
//                 for (int m=0;m<100;m++){
//                     Serial.println(path[m]);
//                 }
            
            
//                 for(l=0;l<100;l++){
//                     path[l]=pro[l];
//                 }
            
            
                
//                 Serial.print("PRO");
//                 for (int m=0;m<100;m++){
//                     Serial.println(pro[m]);
//                 }
            
//                 break;
//                 // i=i+1;
//             }
            
//             else if(path[i]=='S' && path[i+1]=='B' && path[i+2]=='L'){
//                 pro[j]='R';
//                 for(k=(i+3);k<100;k++){
//                     pro[k-2]=path[k];
//                 }
            
//                 Serial.print("path");
//                 for (int m=0;m<100;m++){
//                     Serial.println(path[m]);
//                 }
            
            
//                 for(l=0;l<100;l++){
//                     path[l]=pro[l];
//                 }
            
            
                
//                 Serial.print("PRO");
//                 for (int m=0;m<100;m++){
//                     Serial.println(pro[m]);
//                 }
            
//                 break;
//                 // i=i+1;
//             }
            
//             else if(path[i]=='R' && path[i+1]=='B' && path[i+2]=='L'){
//                 pro[j]='B';
//                 for(k=(i+3);k<100;k++){
//                     pro[k-2]=path[k];
//                 }
            
//                 Serial.print("path");
//                 for (int m=0;m<100;m++){
//                     Serial.println(path[m]);
//                 }
            
            
//                 for(l=0;l<100;l++){
//                     path[l]=pro[l];
//                 }
            
            
              
//                 Serial.print("PRO\n");
//                 for (int m=0;m<100;m++){
//                     Serial.println(pro[m]);
//                 }
            
//                 break;
//                 // i=i+1;
//             }
            
//             else if(path[i]=='L' && path[i+1]=='B' && path[i+2]=='S'){
//                 pro[j]='R';
//                 for(k=(i+3);k<100;k++){
//                     pro[k-2]=path[k];
//                 }  
            
//                 Serial.print("path");
//                 for (int m=0;m<100;m++){
//                     Serial.println(path[m]);
//                 }
            
            
//                 for(l=0;l<100;l++){
//                     path[l]=pro[l];
//                 }   
            
            
                
//                 Serial.print("PRO");
//                 for (int m=0;m<100;m++){
//                     Serial.println(pro[m]);
//                 }
            
//                 break;
//                 // i=i+1;
//             }
            
//             else if(path[i]=='L' && path[i+1]=='B' && path[i+2]=='R'){
//                 pro[j]='B';
//                 for(k=(i+3);k<100;k++){
//                     pro[k-2]=path[k];
//                 }
            
//                 Serial.print("path");
//                 for (int m=0;m<100;m++){
//                     Serial.print(path[m]);
//                 }
            
            
//                 for(l=0;l<100;l++){
//                     path[l]=pro[l];
//                 }
            
            
                
//                 Serial.print("PRO\n");
//                 for (int m=0;m<100;m++){
//                     Serial.println(pro[m]);
//                 }
            
//                 break;
//             }
            
//             else{
//                 pro[j]=path[i];
//             }
//             // for(k=(i+3);k<100;k++){
//             //     pro[k-2]=path[k];
//             // }
            
//             // Serial.print("path\n");
//             // for (int m=0;m<100;m++){
//             //     Serial.print("%c\n ",path[m]);
//             // }
            
            
//             // for(l=0;l<100;l++){
//             //     path[l]=pro[l];
//             // }
            
            
//             // Serial.print("\n");
//             // Serial.print("PRO\n");
//             // for (int m=0;m<100;m++){
//             //     Serial.print("%c\n ",pro[m]);
//             // }
            
//             // break;
//         }
//     }
//     return;
// }     
//------------------------------------UI interface to run code----------------------------------------------------------------------
void UI_INTERFACE(){
  if (digitalRead(RTB)==HIGH){
    counter=counter+1;
    delay(75);
  }
  if (digitalRead(LTB)==HIGH){
    counter=counter-1;
    delay(75);
  }
  if (digitalRead(OKB)==HIGH){
    okon=okon+1;
    delay(450);
  }
  if (digitalRead(DNB)==HIGH){
    counterUDV=counterUDV+1;
    delay(75);
  }
  if (digitalRead(UPB)==HIGH){
    counterUDV=counterUDV-1;
    delay(75);
  }
  if (okon>3){
    okon=0;
  }
  counterUDV=constrain(counterUDV,0,3);
  counter=constrain(counter,1,6);

  //---------------------------calibrate interface UI---------------------------------------------------
  if(counter==1){
    calibrated();
    delay(75);
    //code calibrateright();
  }

  //-----------------------------calibration code-----------------------------------------------
  if(counter==1 && okon==1){
    delay(1000);
    calibrateRight();
    okon=0;
  }

  //--------------------------------------- code 1 interface UI--------------------------------------------
  if(counter==2 && okon==0){
    code1();
    delay(75);
  }

  //----------------------------------------------code 1 kptune--------------------------------------------
  if(counter==2 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }

  //----------------------------------------code 1 kdtune----------------------------------------------
  if(counter==2 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }

  //-------------------------------------code 1 kitune------------------------------------------------
  if(counter==2 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }

  //------------------------------------------code 1 runner-----------------------------------------
  if(counter==2 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }

  //-----------------------------------------code 1 run------------------------------------------
  if(counter==2 && okon==2 && counterUDV==3){
    a=0;
    Kpo=((EEPROM.read(a)*100)+(EEPROM.read(a+1)*10)+(EEPROM.read(a+2)*1)+(EEPROM.read(a+3)*0.1)+(EEPROM.read(a+4)*0.01)+(EEPROM.read(a+5)*0.001));
    Kdo=((EEPROM.read(a+6)*100)+(EEPROM.read(a+7)*10)+(EEPROM.read(a+8)*1)+(EEPROM.read(a+9)*0.1)+(EEPROM.read(a+10)*0.01)+(EEPROM.read(a+11)*0.001));
    Kio=((EEPROM.read(a+12)*100)+(EEPROM.read(a+13)*10)+(EEPROM.read(a+14)*1)+(EEPROM.read(a+15)*0.1)+(EEPROM.read(a+16)*0.01)+(EEPROM.read(a+17)*0.001));
    while(counter==2 && okon==2 && counterUDV==3){
      PID();
      runLogic1();
      delay(1);
      if (digitalRead(OKB)==HIGH){
        delay(100);
        okon=0;
        brake(motor1,motor2);
        break;
      }
    }
  }
  
  //-----------------------------------------code 1 kpvalue---------------------------------------------
  if(counter==2 && okon==2 && counterUDV==0){
    address=0;
    kpvalue();
    delay(75);
  }

  //--------------------------------------------code 1 kdvalue--------------------------------------
  if(counter==2 && okon==2 && counterUDV==1){
    address=6;
    kdvalue();
    delay(75);
  }

  //-----------------------------------------------------code 1 kivalue----------------------------------
  if(counter==2 && okon==2 && counterUDV==2){
    address=12;
    kivalue();
    delay(75);
  }

  //-------------------------------------------------------code 1 kptuner------------------------------
  if(counter==2 && okon==3 && counterUDV==0){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=0;
      kpvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //--------------------------------------code 1 kdtuner---------------------------------------
  if(counter==2 && okon==3 && counterUDV==1){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=6;
      kdvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //---------------------------------code 1 kituner------------------------------------------
  if(counter==2 && okon==3 && counterUDV==2){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=12;
      kivalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //----------------------------------------- code 2 interface UI-----------------------------------
  if(counter==3 && okon==0){
    code2();
    delay(75);
  }

  //-----------------------------------code 2 kptune---------------------------------------------
  if(counter==3 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }
  
  //-------------------------------------------code 2 kdtune--------------------------------------
  if(counter==3 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }

  //----------------------------------------------code 2 kitune-----------------------------
  if(counter==3 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }

  //-----------------------------------code 2 runner--------------------------------------
  if(counter==3 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }

  //------------------------------------code 2 run---------------------------------------------
  if(counter==3 && okon==2 && counterUDV==3){
    a=0;
    Kpo=((EEPROM.read(a)*100)+(EEPROM.read(a+1)*10)+(EEPROM.read(a+2)*1)+(EEPROM.read(a+3)*0.1)+(EEPROM.read(a+4)*0.01)+(EEPROM.read(a+5)*0.001));
    Kdo=((EEPROM.read(a+6)*100)+(EEPROM.read(a+7)*10)+(EEPROM.read(a+8)*1)+(EEPROM.read(a+9)*0.1)+(EEPROM.read(a+10)*0.01)+(EEPROM.read(a+11)*0.001));
    Kio=((EEPROM.read(a+12)*100)+(EEPROM.read(a+13)*10)+(EEPROM.read(a+14)*1)+(EEPROM.read(a+15)*0.1)+(EEPROM.read(a+16)*0.01)+(EEPROM.read(a+17)*0.001));
    while(counter==2 && okon==2 && counterUDV==3){
      PID();
      // runLogic2();
      if (digitalRead(29)==HIGH){
        delay(100);
        okon=0;
        brake(motor1,motor2);
        break;
      }
    }
  }

  //------------------------------------------code 2 kpvalue------------------------------------------
  if(counter==3 && okon==2 && counterUDV==0){
    address=18;
    kpvalue();
    delay(75);
  }

  //-----------------------------------code 2 kdvalue--------------------------------------------------
  if(counter==3 && okon==2 && counterUDV==1){
    address=24;
    kdvalue();
    delay(75);
  }

  //--------------------------------------------------code 2 kivalue------------------------------
  if(counter==3 && okon==2 && counterUDV==2){
    address=30;
    kivalue();
    delay(75);
  }

  //-----------------------------------------code 2 kptuner------------------------------------
  if(counter==3 && okon==3 && counterUDV==0){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=18;
      kpvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //---------------------------------------------code 2 kdtuner--------------------------------------
  if(counter==3 && okon==3 && counterUDV==1){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=24;
      kdvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //--------------------------------------------code 2 kituner--------------------------------------
  if(counter==3 && okon==3 && counterUDV==2){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=30;
      kivalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //---------------------------------------------code 3 interface UI---------------------------------
  if(counter==4 && okon==0){
    code3();
    delay(75);
  }

  //-----------------------------------------code 3 kptune----------------------------------------
  if(counter==4 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }

  //--------------------------------------------code 3 kdtune--------------------------------
  if(counter==4 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }

  //----------------------------------------------code 3 kitune-----------------------------------
  if(counter==4 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }

  //--------------------------------------------code 3 runner------------------------------
  if(counter==4 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }

  //-------------------------------------------code 3 kpvalue-----------------------------
  if(counter==4 && okon==2 && counterUDV==0){
    address=36;
    kpvalue();
    delay(75);
  }

  //-------------------------------------------code 3 kdvalue-------------------------------
  if(counter==4 && okon==2 && counterUDV==1){
    address=42;
    kdvalue();
    delay(75);
  }

  //------------------------------------------------code 3 kivalue-------------------------------
  if(counter==4 && okon==2 && counterUDV==2){
    address=48;
    kivalue();
    delay(75);
  }

  //---------------------------------------------------code 3 kptuner-----------------------------
  if(counter==4 && okon==3 && counterUDV==0){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=36;
      kpvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //-----------------------------------------------------code 3 kdtuner-----------------------------------
  if(counter==4 && okon==3 && counterUDV==1){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=42;
      kdvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //-----------------------------------------------------code 3 kituner------------------------------------
  if(counter==4 && okon==3 && counterUDV==2){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=48;
      kivalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //--------------------------------------------------code 4 interface UI-----------------------------------------
  if(counter==5 && okon==0){
    code4();
    delay(75);
  }

  //-------------------------------------------------code 4 kptune-------------------------------------------------
  if(counter==5 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }

  //------------------------------------------------------code 4 kdtune----------------------------------
  if(counter==5 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }

  //------------------------------------------------code 4 kitune---------------------------------------
  if(counter==5 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }

  //-------------------------------------code 4 runner----------------------------------------
  if(counter==5 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }

  //---------------------------------------------code 4 kpvalue---------------------------------
  if(counter==5 && okon==2 && counterUDV==0){
    address=54;
    kpvalue();
    delay(75);
  }

  //-------------------------------------------code 4 kdvalue----------------------------------
  if(counter==5 && okon==2 && counterUDV==1){
    address=60;
    kdvalue();
    delay(75);
  }
  
  //---------------------------------------code 4 kivalue--------------------------------------
  if(counter==5 && okon==2 && counterUDV==2){
    address=66;
    kivalue();
    delay(75);
  }

  //-------------------------------------------code 4 kptuner----------------------------------
  if(counter==5 && okon==3 && counterUDV==0){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=54;
      kpvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //----------------------------------------code 4 kdtuner---------------------------------
  if(counter==5 && okon==3 && counterUDV==1){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=60;
      kdvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //-----------------------------------------code 4 kituner----------------------------------
  if(counter==5 && okon==3 && counterUDV==2){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=66;
      kivalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //-------------------------------------------code 5 interface UI---------------------------------
  if(counter==6 && okon==0){
    code5();
    delay(75);
  }

  //---------------------------------------code 5 kptune-----------------------------------------
  if(counter==6 && okon==1 && counterUDV==0){
    Kptune();
    delay(75);
  }

  //-------------------------------------------------code 5 kdtune------------------------------------
  if(counter==6 && okon==1 && counterUDV==1){
    Kdtune();
    delay(75);
  }

  //-----------------------------------------code 5 kitune-------------------------------------
  if(counter==6 && okon==1 && counterUDV==2){
    Kitune();
    delay(75);
  }

  //---------------------------------------code 5 runner----------------------------------------
  if(counter==6 && okon==1 && counterUDV==3){
    run();
    delay(75);
  }

  //----------------------------------------------code 5 kpvalue-----------------------------
  if(counter==6 && okon==2 && counterUDV==0){
    address=72;
    kpvalue();
    delay(75);
  }

  //---------------------------------------code 5 kdvalue-----------------------------------
  if(counter==6 && okon==2 && counterUDV==1){
    address=78;
    kdvalue();
    delay(75);
  }

  //-------------------------------------code 5 kivalue------------------------------------------
  if(counter==6 && okon==2 && counterUDV==2){
    address=84;
    kivalue();
    delay(75);
  }

  //-----------------------------------------code 5 kptuner--------------------------------------
  if(counter==6 && okon==3 && counterUDV==0){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=72;
      kpvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //----------------------------------code 5 kdtuner-----------------------------------------
  if(counter==6 && okon==3 && counterUDV==1){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=78;
      kdvalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
  }

  //------------------------------------------code 5 kituner-------------------------------
  if(counter==6 && okon==3 && counterUDV==2){
    PC=0;
    while(okon==3){
      if(digitalRead(OKB)==HIGH){
        okon=okon+1;
        delay(75);
      }
      address=84;
      kivalue();
      if (digitalRead(RTB)==HIGH){
        PC=PC+1;
        delay(75);
      }
      if (digitalRead(LTB)==HIGH){
        PC=PC-1;
        delay(75);
      }
      if(PC>6){
          PC=0;
      }
      if(digitalRead(UPB)==HIGH){
          int val;
          delay(75);
          val=EEPROM.read(address+PC);
          val=val+1;
          val=constrain(val,0,9);
          EEPROM.write((address+PC),val);
        }
      if(digitalRead(DNB)==HIGH){
        int val;
        delay(75);
        val=EEPROM.read(address+PC);
        val=val-1;
        val=constrain(val,0,9);
        EEPROM.write((address+PC),val);
      }
    }
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
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);
  pinMode(A8,INPUT);
  pinMode(A9,INPUT);
  pinMode(A14,INPUT);
  pinMode(A15,INPUT);
  pinMode(A16,INPUT);
  pinMode(A17,INPUT);
  pinMode(13,OUTPUT);
  pinMode(UPB,INPUT); 
  pinMode(DNB,INPUT); 
  pinMode(LTB,INPUT);   
  pinMode(RTB,INPUT); 
  pinMode(OKB,INPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT); 
  pinMode(BIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
  pinMode(33,INPUT);
  pinMode(34,INPUT);
  for(int i=0;i<100;i++){
    int value=EEPROM.read(i);
    EEPROM.write(i,value);
  }
}
void loop(){
  // digitalWrite(33,LOW);
  // digitalWrite(34,LOW);
  UI_INTERFACE();
  // left(motor2,motor1,100);
  // delay(1000);
  // right(motor2,motor1,100);
  // delay(1000);
  // forward(motor2,motor1,100);
  // delay(1000);
  delay(1);
}