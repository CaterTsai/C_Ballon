#include "BCWaterfall.h"

//--------------------------------------------------------------
BCWaterfall::BCWaterfall()
	:BCBase(eBC_WATERFALL)
	,_fTimer(0.0)
	,_color(128, 255, 255)
	,_UnitSize(cCANVAS_WIDTH/cCOL_NUM, cCANVAS_HEIGHT/cROW_NUM)
{}

//--------------------------------------------------------------
void BCWaterfall::update(const float fDelta)
{
	if(_WaterfallList.size() > 0)
	{
		_fTimer -= fDelta;
		if(_fTimer <= 0.0)
		{
			auto Iter_ = _WaterfallList.begin();
			while(Iter_ != _WaterfallList.end())
			{
				Iter_->next();

				if(Iter_->isDie())
				{
					Iter_ = _WaterfallList.erase(Iter_);
				}
				else
				{
					Iter_++;
				}
			}

			if(_bStart)
			{
				addWaterfall();
			}
			_fTimer = getTriggerTime();
		}
	}
}

//--------------------------------------------------------------
void BCWaterfall::draw()
{
	ofPushStyle();
	{
		for(auto Iter_ : _WaterfallList)
		{
			if(Iter_.isDie())
			{
				continue;
			}

			int posY_ = Iter_.iIndex  * _UnitSize.y;
			
			for(int idx_ = 0; idx_ < cCOL_NUM; idx_++)
			{	
				if(Iter_.bDisplayArray[idx_])
				{
					int posX_ = idx_ * _UnitSize.x;
					ofSetColor(_color, Iter_.fAlpha[idx_]);
					ofRect(posX_, posY_, _UnitSize.x, _UnitSize.y);
				}
			}
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void BCWaterfall::start()
{
	_fTimer = getTriggerTime();
	_bStart = true;
	addWaterfall();
}

//--------------------------------------------------------------
void BCWaterfall::stop()
{
	_bStart = false;
}

//--------------------------------------------------------------
float BCWaterfall::getTriggerTime()
{
	return _fDuratcion / 8;
}

//--------------------------------------------------------------
void BCWaterfall::addWaterfall()
{
	stBCFallList _newFall;
	_WaterfallList.push_back(_newFall);
}