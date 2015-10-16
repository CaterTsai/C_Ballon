#include "BCNoise.h"

BCNoise::BCNoise()
	:BCBase(eBC_NOISE)
	,_fTimer(0)
	,_UnitSize(cCANVAS_WIDTH/cCOL_NUM, cCANVAS_HEIGHT/cROW_NUM)
{
}

//--------------------------------------------------------------
void BCNoise::update(const float fDelta)
{
	if(!_bStart)
	{
		return;
	}

	for(auto& Iter_ : _colorMap)
	{
		Iter_.update(fDelta);
	}
}

//--------------------------------------------------------------
void BCNoise::draw()
{
	if(!_bStart)
	{
		return;
	}
	ofPushStyle();
	{
		for(int y_ = 0; y_ < cROW_NUM; ++y_)
		{
			int posY_ = y_ * _UnitSize.y;
			for(int x_ = 0; x_ < cCOL_NUM; ++x_)
			{
				int posX_ = x_ * _UnitSize.x;
				
				ofColor newColor_;
				newColor_.setHsb(_colorMap[y_ * cCOL_NUM + x_].H, 255, _colorMap[y_ * cCOL_NUM + x_].V);
				ofSetColor(newColor_);
				ofRect(posX_, posY_, _UnitSize.x, _UnitSize.y);
			}
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void BCNoise::start()
{
	_bStart = true;
}

//--------------------------------------------------------------
void BCNoise::stop()
{
	_bStart = false;
}
