#include "BAOpenH.h"

BAOpenH::BAOpenH()
	:BABase(eBA_OPEN_H)
{
	_NowColor.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	
	if(cCOL_NUM % 2 == 0)
	{
		_iStartL = cCOL_NUM / 2.0 - 1;
		_iStartR = cCOL_NUM / 2.0;
	}
	else
	{
		_iStartL = _iStartR = floor(cCOL_NUM / 2.0);
	}
	_iEndL = 0;
	_iEndR = cCOL_NUM - 1;
}

//--------------------------------------------------------------
void BAOpenH::update(const float fDelta, vector<Ballon>& source)
{
	if(!_bStart)
	{
		return;
	}

	_fTimer -= fDelta;
	if(_fTimer <= 0.0)
	{
		_fTimer = _fIntervalTime;
		setColor(source);
		
		if(_iIdxL - 1 < _iEndL || _iIdxR + 1 > _iEndR)
		{
			_iIdxL = _iStartL;
			_iIdxR = _iStartR;
			_NowColor.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
		}
		else
		{
			_iIdxL--;
			_iIdxR++;
		}
	}
}

//--------------------------------------------------------------
void BAOpenH::start()
{
	_iIdxL = _iStartL;
	_iIdxR = _iStartR;
	_NowColor.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	_fTimer = _fIntervalTime;
	_bStart = true;

}

//--------------------------------------------------------------
void BAOpenH::stop()
{
	_bStart = false;
}

//--------------------------------------------------------------
void BAOpenH::setColor(vector<Ballon>& source)
{
	for(int idx_ = 0; idx_ < cROW_NUM; idx_++)
	{
		source.at(_iIdxL + idx_ * cCOL_NUM).setColor(_NowColor);
		source.at(_iIdxR + idx_ * cCOL_NUM).setColor(_NowColor);
	}


}