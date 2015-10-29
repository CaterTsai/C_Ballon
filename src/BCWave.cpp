#include "BCWave.h"

BCWave::BCWave(vector<stSinWave>& wg)
	:BCBase(eBC_TYPE::eBC_WAVE, eG_OBJECT)
	,_WaveUnitSize(cCANVAS_WIDTH/(float)cWAVE_DENSITY)
	,_DegreeInterval(360.0/cWAVE_DENSITY)
	,_Degree(0)
	,_DegreeDelta(0)
{
	//initial wave
	float fX_ = _WaveUnitSize/2;
	for(int idx_ = 0; idx_ < cWAVE_DENSITY; idx_++)
	{
		_WavePosList[idx_].set(fX_, 0);
		fX_ += _WaveUnitSize;
	}

	_WaveGenerator = wg;
}

//--------------------------------------------------------------
void BCWave::update(const float fDelta)
{
	if(!_bStart)
	{
		return;
	}
	_DegreeDelta = 360 / getTriggerTime();
	_Degree += _DegreeDelta * fDelta;

	if(_Degree >= 360)
	{
		_Degree -= 360;
	}

	float fSDegree_ = _Degree;
	for(int idx_ = 0; idx_ < cWAVE_DENSITY; idx_++)
	{	
		_WavePosList[idx_].y = 0;
		for(auto& Wave_ : _WaveGenerator)
		{
			_WavePosList[idx_].y += Wave_.getValue(fSDegree_);
		}
		fSDegree_ += _DegreeInterval;
	}
}

//--------------------------------------------------------------
void BCWave::draw()
{
	ofPushMatrix();
	ofTranslate(0, cCANVAS_HEIGHT/2);
	{
		ofPushStyle();
		ofFill();
		ofSetColor(_baseColor);
		{
			for(int idx_ = 0; idx_ < cWAVE_DENSITY; idx_++)
			{
				ofCircle(_WavePosList[idx_], _WaveUnitSize * 1.3);
			}
		}
		ofPopStyle();
	}
	ofPopMatrix();
}

//--------------------------------------------------------------
void BCWave::start()
{
	for(int idx_ = 0; idx_ < cWAVE_DENSITY; idx_++)
	{	
		_WavePosList[idx_].y = 0;
	}

	_bStart = true;
}

//--------------------------------------------------------------
void BCWave::setBaseColor(ofColor c)
{
	_baseColor = c;
	_baseColor.setHueAngle(c.getHueAngle() + 180 + ofRandom(-30, 30));
	_baseColor.setSaturation(ofRandom(200, 255));
}

//--------------------------------------------------------------
float BCWave::getTriggerTime()
{
	return _fDuratcion * 4;
}