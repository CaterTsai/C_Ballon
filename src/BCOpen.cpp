#include "BCOpen.h"

//--------------------------------------------------------------
BCOpen::BCOpen()
	:BCBase(eBC_OPEN)
	,_fOpenAngle(.0)
	,_fOpenDist(0)
	,_OpenSize(cCANVAS_WIDTH/2 * 1.5, cCANVAS_WIDTH * 1.5)
{}

//--------------------------------------------------------------
void BCOpen::update(const float fDelta)
{
	_AnimOpenDist.update(fDelta);

	if(_bStart)
	{
		if(_AnimOpenDist.hasFinishedAnimating() && _AnimOpenDist.getPercentDone() == 1.0)
		{
			open();
		}
	}
}

//--------------------------------------------------------------
void BCOpen::draw()
{
	ofPushStyle();
	ofFill();
	{
		ofSetColor(_NextColor);
		ofRect(0, 0, cCANVAS_WIDTH, cCANVAS_HEIGHT);

		ofSetColor(_NowColor);
		ofPushMatrix();
		ofTranslate(cCANVAS_WIDTH/2, cCANVAS_HEIGHT/2);
		ofRotateZ(_fOpenAngle);
		{
			float fDist_ = _AnimOpenDist.getCurrentValue() * _fOpenDist;

			//Left
			ofRect(-(fDist_ + _OpenSize.x), (-_OpenSize.y/2), _OpenSize.x, _OpenSize.y);
			//Right
			ofRect(fDist_, (-_OpenSize.y/2), _OpenSize.x, _OpenSize.y);
		}
		ofPopMatrix();
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void BCOpen::start()
{
	_bStart = true;
	_NextColor.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	open();	
}

//--------------------------------------------------------------
void BCOpen::stop()
{
	_bStart = false;
}

//--------------------------------------------------------------
float BCOpen::getTriggerTime()
{
	return _fDuratcion * 2.0;
}

//--------------------------------------------------------------
void BCOpen::open()
{
	_AnimOpenDist.setDuration(getTriggerTime());
	_fOpenAngle = ofRandom(0, 180);
	//_fOpenAngle = 0;
	//_fOpenDist = cCANVAS_HEIGHT/2 * 1 / cos(_fOpenAngle);
	_fOpenDist = cCANVAS_WIDTH;
	_NowColor = _NextColor;
	_NextColor.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	_AnimOpenDist.animateFromTo(0, 1);
}