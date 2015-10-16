#include "Projector.h"

void Projector::setup()
{
}

//--------------------------------------------------------------
void Projector::update(float fDelta)
{
}

//--------------------------------------------------------------
void Projector::draw(int x, int y)
{
	ofPushMatrix();
	ofTranslate(x, y);
	{
		if(_bShowRange)
		{
			ofPushStyle();
			{
				ofSetColor(255, 0, 255);
				ofSetLineWidth(3);
				ofNoFill();

				ofRect(0, 0, cPROJECOTR_WIDTH, cPROJECOTR_HEIGHT);
			}
			ofPopStyle();
		}
	}
	ofPopMatrix();
}