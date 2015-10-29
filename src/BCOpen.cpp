#include "BCOpen.h"

//--------------------------------------------------------------
BCOpen::BCOpen()
	:BCBase(eBC_OPEN, eG_BACKGROUND)
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
		ofColor NextColor_, NowColor_;
		NextColor_ = NowColor_ = _baseColor;
		NextColor_.setHueAngle(_baseColor.getHueAngle() + _iColorFlag * 45);
		NowColor_.setHueAngle(_baseColor.getHueAngle() - _iColorFlag * 45);

		ofSetColor(NextColor_);
		ofRect(0, 0, cCANVAS_WIDTH, cCANVAS_HEIGHT);

		ofSetColor(NowColor_);
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
	_iColorFlag = 1;
	open();	
}

//--------------------------------------------------------------
void BCOpen::setBaseColor(ofColor c)
{
	_baseColor = c;
	_baseColor.setSaturation(ofRandom(200, 255));
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
	_fOpenDist = cCANVAS_WIDTH;
	_AnimOpenDist.animateFromTo(0, 1);

	_iColorFlag *= -1;
}