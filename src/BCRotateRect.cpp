#include "BCRotateRect.h"

#pragma region Rotate Rect struct
//--------------------------------------------------------------
stRotateRect::_stRotateRect(ofColor c, float fDurction, ofVec2f Central)
	:_Central(Central)
	,_bDie(false)
{
	_Color.set(c);

	_AnimRotate.setDuration(fDurction);
	_AnimRotate.setRepeatType(AnimRepeat::PLAY_ONCE);

	_AnimSize.setDuration(fDurction);
	_AnimSize.setRepeatType(AnimRepeat::PLAY_ONCE);
	
	_AnimRotate.animateFromTo(0, 360);
	_AnimSize.animateFromTo(0, 1);
}

//--------------------------------------------------------------
void stRotateRect::update(float fDelta)
{
	if(_bDie)
	{
		return;
	}

	_AnimRotate.update(fDelta);
	_AnimSize.update(fDelta);

	if(_AnimRotate.hasFinishedAnimating() && _AnimRotate.getPercentDone() == 1.0 && 
		_AnimSize.hasFinishedAnimating() && _AnimSize.getPercentDone() == 1.0)
	{
		_bDie = true;
	}
}

//--------------------------------------------------------------
void stRotateRect::draw()
{
	ofPushMatrix();
	ofTranslate(_Central);
	ofRotateZ(_AnimRotate.getCurrentValue());
	{
		float fRectW_ = _AnimSize.getCurrentValue() * cCANVAS_WIDTH;
		float fRectH_ = _AnimSize.getCurrentValue() * cCANVAS_HEIGHT;

		ofPushStyle();
		ofSetColor(_Color);
		ofFill();
		{
			ofRect(-fRectW_/2, -fRectH_/2, fRectW_, fRectH_);
		}
		ofPopStyle();
	}
	ofPopMatrix();
}
#pragma endregion

#pragma region Ballon Canvas Rotate Rect
//--------------------------------------------------------------
BCRotateRect::BCRotateRect()
	:BCBase(eBC_ROTATE_RECT, eG_BACKGROUND)
	,_fTimer(0.0)
	,_Background(0)
	,_iColorFlag(1)
{}

//--------------------------------------------------------------
void BCRotateRect::update(const float fDelta)
{	
	auto Iter_ = _RectList.begin();
	while(Iter_ != _RectList.end())
	{
		Iter_->update(fDelta);

		if(Iter_->_bDie)
		{
			_Background = Iter_->_Color;
			Iter_ = _RectList.erase(Iter_);
		}
		else
		{
			Iter_++;
		}
	}

	if(_bStart)
	{
		_fTimer -= fDelta;
		if(_fTimer <= 0.0)
		{
			addRect();
			_fTimer = getTriggerTime();
		}
	}
}

//--------------------------------------------------------------
void BCRotateRect::draw()
{	
	ofPushStyle();
	{
		ofFill();
		ofSetColor(_Background);
		ofRect(0, 0, cCANVAS_WIDTH, cCANVAS_HEIGHT);

		ofSetColor(255);
		for(auto& Iter_ : _RectList)
		{
			Iter_.draw();
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void BCRotateRect::start()
{
	_Background.set(0);
	_iColorFlag = 1;
	addRect();
	_fTimer = getTriggerTime();
	_bStart = true;
}

//--------------------------------------------------------------
void BCRotateRect::setBaseColor(ofColor c)
{
	_baseColor = c;
	_baseColor.setSaturation(ofRandom(200, 255));
}

//--------------------------------------------------------------
float BCRotateRect::getTriggerTime() 
{
	return _fDuratcion * 2;
}

//--------------------------------------------------------------
void BCRotateRect::addRect()
{
	ofColor rectColor_ = _baseColor;
	rectColor_.setHueAngle(_baseColor.getHueAngle() + _iColorFlag * 45);

	stRotateRect NewRect_(rectColor_, getTriggerTime() * 2, ofVec2f(cCANVAS_WIDTH/2, cCANVAS_HEIGHT/2));
	_RectList.push_back(NewRect_);
	_iColorFlag *= -1;
}
#pragma endregion

