#ifndef OFX_LED_CONTRAL
#define OFX_LED_CONTRAL

#include "constParameter.h"
#include "ledColor.h"

class LEDCtrl
{
public:
	LEDCtrl()
		:_bSetup(false)
		,_bStart(false)
		,_bNeedUpdate(false)
	{}
	void setup();
	void update();

	void setColor(vector<ofColor>& newColorList);

public:
	inline void toggle()
	{
		_bStart ^= true;
	}
private:
	void initLedMap();
private:
	deque<ofColor>	_Color;
	ofSerial		_Serial;
	bool	_bSetup, _bStart, _bNeedUpdate;

	int	_LedMap[cCOLOR_NUM]; //Pixel to LED
};


#endif // !OFX_LED_CONTRAL
