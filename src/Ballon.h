#ifndef OFX_BALLON
#define OFX_BALLON

#include "constParameter.h"
#include "ofxAnimatableFloat.h"

class Ballon
{
public:
	Ballon(ofVec2f pos, float R = cBALLON_R)
		:_fR(R)
		,_Position(pos)
	{
		_Color = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));		

		//_AnimColorHue.setDuration(10);
		//_AnimColorHue.setRepeatType(AnimRepeat::LOOP);
		//_AnimColorHue.animateFromTo(0, 1);
		//_fBaseAngle = _Color.getHueAngle();
	}

	void update(float fDelta)
	{
		//_AnimColorHue.update(fDelta);
		//float newAngle_ = _fBaseAngle + _AnimColorHue.getCurrentValue() * 360.0;
		//if(newAngle_ > 360)
		//{
		//	newAngle_ -= 360;
		//}

		//_Color.setHueAngle(newAngle_);
	}

	void draw()
	{
		ofPushStyle();
		ofSetColor(_Color);
		ofFill();
		ofPushMatrix();
		ofTranslate(_Position);
		{
			ofCircle(0, 0, _fR);
		}
		ofPopMatrix();
		ofPopStyle();
	}

	void setColor(ofColor newColor)
	{
		_Color = newColor;
	}

	ofColor getColor()
	{
		return _Color;
	}

private:
	float		_fR;
	ofVec2f		_Position;
	ofColor		_Color;
	float		_fBaseAngle;
	ofxAnimatableFloat	_AnimColorHue;
};

#endif // !OFX_BALLON
