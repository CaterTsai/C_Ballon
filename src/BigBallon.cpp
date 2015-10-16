#include "BigBallon.h"

void BigBallon::setup()
{
	//Big Ballon left
	_BallonPosList.push_back(ofPoint(cBIG_BALLON_R, cWINDOW_HEIGHT - cBIG_BALLON_R));

	//Big Ballon right
	_BallonPosList.push_back(ofPoint(cWINDOW_WIDTH - cBIG_BALLON_R, cWINDOW_HEIGHT - cBIG_BALLON_R));
}

//--------------------------------------------------------------
void BigBallon::update(float fDelta)
{
}

//--------------------------------------------------------------
void BigBallon::draw()
{
	for(auto& Iter_ : _BallonPosList)
	{
		ofPushMatrix();
		ofTranslate(Iter_);
		
		
		
		//Debug
		if(_bShowRange)
		{
			ofPushStyle();
			{
				ofSetColor(255, 255, 0);
				ofSetLineWidth(3);
				ofNoFill();

				ofCircle(0, 0, cBIG_BALLON_R);
			}
			ofPopStyle();
		}
		ofPopMatrix();
	}
}