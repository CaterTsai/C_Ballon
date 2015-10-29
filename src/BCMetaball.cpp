#include "BCMetaball.h"

float BallBoid::REFLECT=2.0;
float BallGroup::THRES=.1;
float BallGroup::DEGREE=3;

int BallGroup::M_GROUP=5;
int BallGroup::MAX_BALL_COUNT=150;

BCMetaball::BCMetaball()
	:BCBase(eBC_METABALL, eG_OBJECT)
{
	ball_group.setup();
}

//--------------------------------------------------------------
void BCMetaball::update(const float fDelta)
{
	if(!_bStart)
	{
		return;
	}
	ball_group.update();
}

//--------------------------------------------------------------
void BCMetaball::draw()
{
	if(!_bStart)
	{
		return;
	}

	ofPushStyle();
	{
		ball_group.draw();
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void BCMetaball::start()
{
	_bStart = true;
	ball_group.reset(50);	
}

//--------------------------------------------------------------
void BCMetaball::setBaseColor(ofColor c)
{
	_baseColor.set(c);
	_baseColor.setHueAngle(c.getHueAngle() + 150);
	ball_group.setBallColor(_baseColor);
}