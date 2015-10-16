#include "BCBlink.h"

BCBlink::BCBlink()
	:BCBase(eBC_BLINK)
	,_bBlink(false)
	,_color(255)
	,_Timer(.0f)
{}

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
	ofSetColor(_color);
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