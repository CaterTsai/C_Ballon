#ifndef OFX_CONST_PARAMETER
#define OFX_CONST_PARAMETER

#include "ofMain.h"
#include "ledColor.h"

static const float cBASE_SCALE = 3;

//Ballon Wall
static const int cCOL_NUM = 20;
static const int cROW_NUM = 10;
static const int cCANVAS_WIDTH = 600;
static const int cCANVAS_HEIGHT = 300;

static const float cBALLON_R = 9 * cBASE_SCALE;
static const int cWALL_WIDTH = 420 * cBASE_SCALE;
static const int cWALL_HEIGHT = 225 * cBASE_SCALE;
static const int cBALL_TYPE = 0; //0: Cube 1:Shift

static const int cRAIN_TAIL_NUM = 5;
static const int cSNAKE_WIDTH = 30;
static const int cFIREWORK_SIZE = 25;
static const int cSCANNER_WIDTH = 30;
static const int cTEXT_FONT_SIZE = 170;

static const int cMAX_BPM = 320;
static const int cMIN_BPM = 60;

//Serial
static const bool cUSE_LED_CTRL = true;
static const int cCOLOR_NUM = cCOL_NUM * cROW_NUM;
static const int cSERIAL_BAUD = 115200;
static const string cSERIAL_PORT = "COM4";

//GUI
static const int cGUI_WIDTH = cCANVAS_WIDTH;
static const int cGUI_HEIGHT = cWALL_HEIGHT;
static const int cGUI_FONT_SIZE = 40;
//Windows 
static const int cWINDOW_WIDTH = cWALL_WIDTH + cGUI_WIDTH;
static const int cWINDOW_HEIGHT = cWALL_HEIGHT;


#endif // !OFX_CONST_PARAMETER
