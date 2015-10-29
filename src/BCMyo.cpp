#include "BCMyo.h"

//--------------------------------------------------------------
BCMyo::BCMyo()
	:BCBase(eBC_MYO, eG_FOREGROUND)
	,_UnitSize(cCANVAS_WIDTH/cCOL_NUM, cCANVAS_HEIGHT/cROW_NUM)
{
	_CTMyo.setup();
}

//--------------------------------------------------------------
void BCMyo::update(const float fDelta)
{
	if(!_bStart)
	{
		return;
	}
	_CTMyo.update();

	if(!_isTrigger)
	{
		if(_CTMyo.getGyros().distance(ofVec3f(0)) >= 500)
		{
			_isTrigger = true;
			_fTimer = 0.3;
		}
	}
	else
	{
		_fTimer -= fDelta;
		if(_fTimer <= 0)
		{
			_isTrigger = false;
		}
	}
}

//--------------------------------------------------------------
void BCMyo::draw()
{
	if(!_bStart)
	{
		return;
	}

	if(!_isTrigger)
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
				newColor_.setHsb(ofRandom(0, 255), 255, 255);
				if(ofRandom(-1, 1) > 0)
				{
					ofSetColor(newColor_);
					ofRect(posX_, posY_, _UnitSize.x, _UnitSize.y);
				}
			}
		}
	}
	ofPopStyle();
}
