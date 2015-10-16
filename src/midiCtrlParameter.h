#ifndef OFX_MIDI_CTRL
#define OFX_MIDI_CTRL

enum cMIDI_CTRL_CODE : int
{
	//Ctrl 
	eMC_SPEED_SLIDER = 16
	
	,eMC_CTRL_SLIDER_1 = 0
	,eMC_CTRL_SLIDER_2 = 1
	,eMC_CTRL_SLIDER_3 = 2

	,eMC_CTRL_NEXT = 62
	,eMC_CTRL_PREV = 61

	,eMC_SPEED_TAP = 46
	,eMC_MANUAL_BLINK = 45

	//Background trigger
	,eMC_BACKGROUND = 32
	,eMC_VIDEO_SET1
	,eMC_VIDEO_SET2
	,eMC_VIDEO_SET3
	,eMC_ROTATE_TECT
	,eMC_OPEN
	,eMC_NOISE

	//Object trigger
	,eMC_RAIN = 48
	,eMC_SPLIT_BALL
	,eMC_WAVE
	,eMC_SNAKE
	,eMC_FIREWORK
	,eMC_SCANNER_H
	,eMC_SCANNER_V

	//Foreground trigger
	,eMC_WATERFALL = 64
	,eMC_CROSS
	,eMC_SIMPLE_BLINK	
};

static const int cMIDI_MIN_VALUE = 0;
static const int cMIDI_MAX_VALUE = 127;

static const int cMIDI_BTN_RELEASE = 0;
static const int cMIDI_BTN_PRESS = 127;

#endif // !OFX_MIDI_CTRL
