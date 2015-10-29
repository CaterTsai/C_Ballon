#include "ColorSet.h"

//--------------------------------------------------------------
ColorSet::ColorSet()
	:_MainColor(255, 0, 0)
{
	ofColor Background_ = _MainColor;
	Background_.setSaturation(ofRandom(128, 255));
	_ColorMap.insert(make_pair(eBC_BACKGROUND, Background_));

	ofColor Background_ = _MainColor;
	Background_.setSaturation(ofRandom(128, 255));
	_ColorMap.insert(make_pair(eBC_BACKGROUND, Background_));
}

//--------------------------------------------------------------
ColorSet* ColorSet::_pInstance = nullptr;
ColorSet* ColorSet::GetInstance()
{
	if(_pInstance == nullptr)
	{
		_pInstance = new ColorSet();
	}
	return _pInstance;
}

//--------------------------------------------------------------
void ColorSet::Destory()
{
	if(_pInstance != nullptr)
	{
		delete _pInstance;
		_pInstance = nullptr;
	}
}