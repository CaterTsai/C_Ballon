#include "BCScanner.h"

//--------------------------------------------------------------
BCScanner::BCScanner(ofVec2f Start, ofVec2f End, int iLength)
	:BCBase(eBC_SCANNER)
	,_Start(Start)
	,_End(End)
	,_iLength(iLength)
	,_iLineNum(5)
{
	_AnimScan.setCurve(AnimCurve::EASE_IN_EASE_OUT);
}

//--------------------------------------------------------------
void BCScanner::update(const float fDelta)
{
	_AnimScan.update(fDelta);

	if(_bStart)
	{
		if(_AnimScan.hasFinishedAnimating() && _AnimScan.getPercentDone() == 1.0)
		{
			scan();
		}
	}
}

//--------------------------------------------------------------
void BCScanner::draw()
{
	ofVec2f DrawPos_ = _Start.getInterpolated(_End, _AnimScan.getCurrentValue());
	float fAngle_ = (_End - _Start).angle(ofVec2f(0, 1));
	
	ofPushStyle();

	ofSetLineWidth(cSCANNER_WIDTH);
	ofPushMatrix();
	ofTranslate(DrawPos_);
	ofRotateZ(-fAngle_);
	{
		for(int idx_ = 0; idx_ < _iLineNum; idx_++)
		{
			ofSetColor(_lineColor, 255 - (255 * idx_  / (float)_iLineNum) );
			int iPos_ = 0;

			if(_AnimScan.getTargetValue() == 1.0)
			{
				iPos_ -=  (idx_ * cSCANNER_WIDTH);
			}
			else
			{
				iPos_ +=  (idx_ * cSCANNER_WIDTH);
			}
			ofLine(-_iLength/2, iPos_, _iLength/2, iPos_);

		}
	}
	ofPopMatrix();
	ofPopStyle();
}

//--------------------------------------------------------------
void BCScanner::start()
{
	_lineColor.set(ColorSet::GetInstance()->getRandomColor());
	_bStart = true;
	_bFlip = true;
	scan();
}

//--------------------------------------------------------------
void BCScanner::stop()
{
	_bStart = false;
}

//--------------------------------------------------------------
float BCScanner::getTriggerTime()
{
	return _fDuratcion * 2;
}

//--------------------------------------------------------------
void BCScanner::scan()
{
	_AnimScan.setDuration(getTriggerTime());
	
	if(_bFlip)
	{
		_AnimScan.animateFromTo(0.0, 1.0);
	}
	else
	{
		_AnimScan.animateFromTo(1.0, 0.0);
	}
	_bFlip ^= true;
}