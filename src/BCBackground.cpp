#include "BCBackground.h"

BCBackground::BCBackground()
	:BCBase(eBC_BACKGROUND)
	,_color(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255))
{}

//--------------------------------------------------------------
void BCBackground::draw()
{
	if(!_bStart)
	{
		return;
	}

	ofPushStyle();
	ofFill();
	ofSetColor(_color);
	{
		ofRect(0, 0, cCANVAS_WIDTH, cCANVAS_HEIGHT);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void BCBackground::start()
{
	_color.set(ColorSet::GetInstance()->getRandomColor());
	_bStart = true;
}

//--------------------------------------------------------------
void BCBackground::stop()
{
	_bStart = false;
}