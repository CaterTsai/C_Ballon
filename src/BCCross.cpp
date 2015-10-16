#include "BCCross.h"

BCCross::BCCross()
	:BCBase(eBC_CROSS)
	,_color(128, 255, 255)
	,_UnitSize(cCANVAS_WIDTH/cCOL_NUM, cCANVAS_HEIGHT/cROW_NUM)
{
	for(int idx_ = 0; idx_ < cROW_NUM; idx_++)
	{
		_CrossMap[idx_].resize(cCOL_NUM);
		_Timer[idx_] = 0.0;
		_BaseTimer[idx_] = 0.0;
	}
}

//--------------------------------------------------------------
void BCCross::update(const float fDelta)
{	
	for(int idx_ = 0; idx_ < cROW_NUM; idx_++)
	{
		_Timer[idx_] -= fDelta;
		if(_Timer[idx_] <= 0.0)
		{
			_CrossMap[idx_].pop_front();

			if(_bStart)
			{
				if(ofRandom(-1, 1) > 0)
				{
					_CrossMap[idx_].push_back(ofRandom(0, 255));
				}
				else
				{
					_CrossMap[idx_].push_back(0);
				}
			}
			else
			{
				_CrossMap[idx_].push_back(0);
			}
			_Timer[idx_] = _BaseTimer[idx_];
		}
	}
}

//--------------------------------------------------------------
void BCCross::draw()
{
	ofPushStyle();
	{
		for(int y_ = 0; y_ < cROW_NUM; ++y_)
		{
			int posY_ = y_ * _UnitSize.y;
			for(int x_ = 0; x_ < cCOL_NUM; ++x_)
			{
				int fAlpha_ = _CrossMap[y_][x_];
				int posX_ = 0;
				if(y_ % 2 == 0)
				{
					posX_ = x_ * _UnitSize.x;
				}
				else
				{
					posX_ = cCANVAS_WIDTH -  (x_ + 1) * _UnitSize.x;
				}
				if(fAlpha_ > 0)
				{
					ofSetColor(_color, fAlpha_);
					
					ofRect(posX_, posY_, _UnitSize.x, _UnitSize.y);
				}
			}
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void BCCross::start()
{
	_color.set(ColorSet::GetInstance()->getRandomColor());
	_bStart = true;
	for(int idx_ = 0; idx_ < cROW_NUM; idx_++)
	{
		_BaseTimer[idx_] = getTriggerTime();
		_Timer[idx_] = _BaseTimer[idx_];
	}
}

//--------------------------------------------------------------
void BCCross::stop()
{
	_bStart = false;
}

//--------------------------------------------------------------
float BCCross::getTriggerTime()
{
	return _fDuratcion / 8  * ofRandom(0.5, 2);
}

//--------------------------------------------------------------
void BCCross::setDuratcionTime(float duratctionT)
{
	_fDuratcion = duratctionT;
	for(int idx_ = 0; idx_ < cROW_NUM; idx_++)
	{
		_BaseTimer[idx_] = getTriggerTime();
	}
}