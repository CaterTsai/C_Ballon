#include "LEDCtrl.h"

//--------------------------------------------------------------
void LEDCtrl::setup()
{
	if(!_Serial.setup(cSERIAL_PORT, cSERIAL_BAUD))
	{
		ofLog(OF_LOG_ERROR, "[LEDCtrl] Connection to arduion failed");
		return;
	}
	
	initLedMap();
	_Color.resize(cCOLOR_NUM);
	_bSetup = true;
}

//--------------------------------------------------------------
void LEDCtrl::update()
{
	if(!_bStart || !_bSetup || !_bNeedUpdate)
	{
		return;
	}

	unsigned char color_[cCOLOR_NUM * 3 + 1] = {0};	
	for(int i = 0; i < cCOLOR_NUM; ++i)
	{
		color_[i * 3] = _Color[i].r;
		color_[i * 3 + 1] = _Color[i].g;
		color_[i * 3 + 2] = _Color[i].b;
	}
	color_[cCOLOR_NUM * 3] = '\n';
	_Serial.writeBytes(color_, cCOLOR_NUM * 3 + 1);
}

//--------------------------------------------------------------
void LEDCtrl::setColor(vector<ofColor>& newColorList)
{
	if(!_bStart || !_bSetup)
	{
		return;
	}

	for(int idx_ = 0; idx_ < newColorList.size(); idx_++)
	{
		_Color[_LedMap[idx_]].set(newColorList[idx_]);
	}
	_bNeedUpdate = true;
}

//--------------------------------------------------------------
void LEDCtrl::initLedMap()
{
	for(int y = 0; y < cROW_NUM; ++y)
	{
		int LedX_, DeltaX_;
		if( (y + 1) % 2 == 0 )
		{
			LedX_ = cCOL_NUM - 1;
			DeltaX_ = -1;
		}
		else
		{
			LedX_ = 0;
			DeltaX_ = 1;
		}

		for(int x = 0; x < cCOL_NUM; ++x)
		{
			int LEDindex_ = y * cCOL_NUM + LedX_;
			int ColorIndex_ = y * cCOL_NUM + x;
			_LedMap[LEDindex_] = ColorIndex_;
			LedX_ += DeltaX_;
		}
	}
}