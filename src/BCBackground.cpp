#include "BCBackground.h"

BCBackground::BCBackground()
	:BCBase(eBC_BACKGROUND, eG_BACKGROUND)
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
	ofSetColor(_baseColor);
	{
		ofRect(0, 0, cCANVAS_WIDTH, cCANVAS_HEIGHT);
	}
	ofPopStyle();
}
