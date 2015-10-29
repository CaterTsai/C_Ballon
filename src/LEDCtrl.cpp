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

	unsigned char color_[cCOLOR_NUM + 2] = {0};
	color_[0] = 'h';

	for(int i = 0; i < cCOLOR_NUM; ++i)
	{
		color_[i + 1] = ledColorMap::encode(_Color[i]);	
	}
	color_[cCOLOR_NUM + 1] = '\n';
	_Serial.writeBytes(color_, cCOLOR_NUM + 2);

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
	for(int x = 0; x < cCOL_NUM; ++x)
	{
		int StartLEDIdx_, DeltaLEDIdx_;
		if(x % 2 == 0)
		{
			StartLEDIdx_ = x * cROW_NUM + (cROW_NUM - 1);
			DeltaLEDIdx_ = -1;
		}
		else
		{
			StartLEDIdx_ = x * cROW_NUM;
			DeltaLEDIdx_ = 1;
		}

		for(int y = 0; y < cROW_NUM; ++y)
		{
			int PixelIndex_ = y * cCOL_NUM + x;
			_LedMap[PixelIndex_] = StartLEDIdx_;
			StartLEDIdx_ += DeltaLEDIdx_;
		}
	}
}