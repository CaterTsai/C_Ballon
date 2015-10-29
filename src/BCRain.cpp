#include "BCRain.h"

#pragma region Rain struct
//--------------------------------------------------------------
stRain::_stRain(ofColor c, float fDurction)
	:_bDie(false)
	,_PosX(ofRandom(0, cCANVAS_WIDTH))
	,_fSize(0.05 * cCANVAS_WIDTH)
{
	_Color.set(c);

	_AnimDrop.setDuration(fDurction);
	_AnimDrop.setCurve(AnimCurve::LINEAR);
	_AnimDrop.setRepeatType(AnimRepeat::PLAY_ONCE);
	_AnimDrop.animateFromTo(-_fSize, cCANVAS_HEIGHT + cRAIN_TAIL_NUM * _fSize);
}

//--------------------------------------------------------------
void stRain::update(float fDelta)
{
	if(_bDie)
	{
		return;
	}
	_AnimDrop.update(fDelta);

	if(_AnimDrop.hasFinishedAnimating() && _AnimDrop.getPercentDone() == 1.0)
	{
		_bDie = true;
	}
}

//--------------------------------------------------------------
void stRain::draw()
{
	ofPushMatrix();
	ofTranslate(_PosX, _AnimDrop.getCurrentValue());
	{
		ofPushStyle();
		ofFill();
		{	
			float fAlpha_ = 255;
			for(int idx_ = 0; idx_ < 5; ++idx_)
			{
				ofSetColor(_Color, fAlpha_);
				ofRect(-_fSize/2, -_fSize/2 - (_fSize * idx_), _fSize, _fSize);
				fAlpha_ *= 0.6;
			}			
		}
		ofPopStyle();
	}
	ofPopMatrix();
}
#pragma endregion

#pragma region Ballon Canvas Rain
//--------------------------------------------------------------
BCRain::BCRain()
	:BCBase(eBC_RAIN, eG_OBJECT)
	,_fTimer(0.0)
	,_fFadeAmnt(10)
{}

//--------------------------------------------------------------
void BCRain::update(const float fDelta)
{	
	auto Iter_ = _RainList.begin();
	while(Iter_ != _RainList.end())
	{
		Iter_->update(fDelta);

		if(Iter_->_bDie)
		{
			Iter_ = _RainList.erase(Iter_);
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
			addRain();
			_fTimer = getTriggerTime();
		}
	}
}

//--------------------------------------------------------------
void BCRain::draw()
{
	ofPushStyle();
	{
		ofFill();
		for(auto& Iter_ : _RainList)
		{
			Iter_.draw();
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void BCRain::start()
{
	_fTimer = getTriggerTime();
	_bStart = true;
}

//--------------------------------------------------------------
void BCRain::setBaseColor(ofColor c)
{
	_baseColor = c;
	_baseColor.setHueAngle(c.getHueAngle() + 180 + ofRandom(-30, 30));
}

//--------------------------------------------------------------
float BCRain::getTriggerTime()
{
	return _fDuratcion * 0.25;
}

//--------------------------------------------------------------
void BCRain::addRain()
{
	ofColor rainC_ = _baseColor;
	rainC_.setSaturation(ofRandom(200, 255));
	stRain NewRain_(rainC_, getTriggerTime() * ofRandom(32, 64));
	_RainList.push_back(NewRain_);
}
#pragma endregion

