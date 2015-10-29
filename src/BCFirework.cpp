#include "BCFirework.h"

#pragma region Firework
//--------------------------------------------------------------
Firework::Firework(ofColor c, float fDurction, int SparkNum, int height)
	:_IsDie(false)
	,_bExplode(false)
	,_iSparkNum(SparkNum)
	,_pos(ofRandom(0, cCANVAS_WIDTH), cCANVAS_HEIGHT)
	,_iHeight(height)
	,_Color(c)
{
	_AnimUp.setDuration(fDurction);
	_AnimUp.setCurve(AnimCurve::QUADRATIC_EASE_OUT);
	_AnimUp.animateFromTo(0.0, height);

	_AnimExplode.setDuration(1.0);
	_AnimExplode.setCurve(AnimCurve::QUADRATIC_EASE_OUT);	
}

//--------------------------------------------------------------
void Firework::update(float fDelta)
{
	if(_IsDie)
	{
		return;
	}

	_AnimUp.update(fDelta);
	_AnimExplode.update(fDelta);

	if(!_bExplode)
	{
		_pos.y = cCANVAS_HEIGHT - _AnimUp.getCurrentValue();
		if(_AnimUp.hasFinishedAnimating() && _AnimUp.getPercentDone() ==  1.0)
		{
			_bExplode = true;
			_AnimExplode.animateFromTo(0, _iHeight);
		}
	}
	else
	{
		if(_AnimExplode.hasFinishedAnimating() && _AnimExplode.getPercentDone() ==  1.0)
		{
			_IsDie = true;
		}
	}
	
}

//--------------------------------------------------------------
void Firework::draw()
{
	if(_IsDie)
	{
		return;
	}

	ofPushStyle();
	
	ofPushMatrix();
	ofTranslate(_pos);
	if(!_bExplode)
	{
		ofSetColor(_Color);
		ofCircle(0, 0, cFIREWORK_SIZE);
	}
	else
	{
		float fRotateDeg_ = 360.f/_iSparkNum;
		float shift_ = _AnimExplode.getCurrentValue();
		ofPushMatrix();
		ofSetColor(_Color);
		
		for(int idx_ = 0; idx_ < _iSparkNum; ++idx_)
		{
			ofRotateZ(fRotateDeg_);			
			ofCircle(-shift_, 0, cFIREWORK_SIZE);
		}
		ofPopMatrix();
	}
	ofPopMatrix();
	ofPopStyle();
}
#pragma endregion

#pragma region BCFirework
//--------------------------------------------------------------
BCFirework::BCFirework()
	:BCBase(eBC_FIREWORK, eG_OBJECT)
	,_fTimer(0.0)
{}

//--------------------------------------------------------------
void BCFirework::update(const float fDelta)
{
	auto Iter_ = _FireworkList.begin();
	while(Iter_ != _FireworkList.end())
	{
		Iter_->update(fDelta);

		if(Iter_->isDie())
		{
			Iter_ = _FireworkList.erase(Iter_);
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
			addFirework();
			_fTimer = getTriggerTime();
		}
	}
}

//--------------------------------------------------------------
void BCFirework::draw()
{
	ofPushStyle();
	{
		for(auto& Iter_ : _FireworkList)
		{
			Iter_.draw();
		}
	}	
	ofPopStyle();
}

//--------------------------------------------------------------
void BCFirework::start()
{
	_fTimer = _fDuratcion;
	_bStart = true;
	addFirework();
}

//--------------------------------------------------------------
void BCFirework::stop()
{
	_bStart = false;
	_FireworkList.clear();
}

//--------------------------------------------------------------
void BCFirework::setBaseColor(ofColor c)
{
	_baseColor.set(c);
	_baseColor.setHueAngle(c.getHueAngle() + 180);
}

//--------------------------------------------------------------
void BCFirework::addFirework()
{
	ofColor newColor_ = _baseColor;
	newColor_.setHueAngle(newColor_.getHueAngle() + ofRandom(-40, 40));
	Firework _newFirework(newColor_, _fDuratcion, static_cast<int>(ofRandom(5, 8)), ofRandom(cCANVAS_HEIGHT * 0.2, cCANVAS_HEIGHT));
	_FireworkList.push_back(_newFirework);
}
#pragma endregion

