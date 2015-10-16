#ifndef LED_COLOR
#define LED_COLOR

#include "ofMain.h"

static const int cCOLOR_HUE_NUM = 16;
static const int cCOLOR_LIGHT_NUM = 4; 
static const int cCOLOR_SATURATION_NUM = 4; 
static const int cCOLOR_GRAY_NUM = 15;

static const int cHUE_INTERVAL = static_cast<int>(255.0 / (cCOLOR_HUE_NUM - 1));
static const int cLIGHT_INTERVAL = static_cast<int>(255.0 / cCOLOR_LIGHT_NUM);
static const int cSATURATION_INTERVAL = static_cast<int>(255.0 / cCOLOR_SATURATION_NUM);
static const int cGRAY_INTERVAL = static_cast<int>(255.0 / cCOLOR_GRAY_NUM - 1);

static const unsigned char cHUE_MASK = 0xF0;
static const unsigned char cSATURATION_MASK = 0x0C;
static const unsigned char cLIGHT_MASK = 0x03;
static const unsigned char cGRAY_MASK = 0x0F;

static const int HUE_CODETABLE[cCOLOR_HUE_NUM] = 
	{8, 25, 42, 59, 76, 93, 110, 127, 144, 161, 178, 195, 212, 229, 246, 0}; //0~14(H) + 1(S)
static const int LIGHT_CODETABLE[cCOLOR_LIGHT_NUM] = 
	{32, 96, 160, 224}; //0~4
static const int SATURATION_CODETABLE[cCOLOR_SATURATION_NUM] = 
	{32, 96, 160, 224}; //0~4
static const int GRAYLEVEL_CODETABLE[cCOLOR_GRAY_NUM] = 
	{0, 18, 36, 54, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252};
//Code

class ledColorMap
{
public:
	static ofColor getNearColor(const ofColor& c);
	static unsigned char encode(const ofColor& c);
	static ofColor decode(unsigned char code);
};

#endif // !LED_COLOR
