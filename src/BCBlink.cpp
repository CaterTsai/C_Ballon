#include "BCBlink.h"

BCBlink::BCBlink(ofColor& color)
	:BCBase(eBC_BLINK, eG_FOREGROUND)
	,_bBlink(false)
	,_FixColor(color)
	,_Timer(.0f)
{
	_baseColor.set(color);
}

//--------------------------------------------------------------
void BCBlink::update(const float fDelta)
{
	if(!_bStart)
	{
		return;
	}

	_Timer -= fDelta;
	if(_Timer <= 0)
	{
		_Timer = getTriggerTime();
		_bBlink = true;
	}
}

//--------------------------------------------------------------
void BCBlink::draw()
{
	if(!_bStart || !_bBlink)
	{
		return;
	}

	ofPushStyle();
	ofSetColor(_FixColor);
	{
		ofRect(0, 0, cCANVAS_WIDTH, cCANVAS_HEIGHT);
	}
	ofPopStyle();
	_bBlink = false;
}

//--------------------------------------------------------------
void BCBlink::start()
{
	_bStart = true;
	_bBlink = true;
	_Timer = getTriggerTime();
}

//--------------------------------------------------------------
void BCBlink::stop()
{
	_bStart = false;
	_bBlink = false;
}