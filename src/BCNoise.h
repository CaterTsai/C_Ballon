#ifndef OFX_BALLON_CANVAS_NOISE
#define OFX_BALLON_CANVAS_NOISE

#include "BCBase.h"
#include "ofxAnimatableFloat.h"

typedef struct _stColorUnit
{
	_stColorUnit()
		:H(ofRandom(0, 255))
		,V(ofRandom(0, 255))
	{
		HDelta = 255.0/ ofRandom(3.0, 10.0) * (ofRandom(-1, 1) > 0?1:-1);
		VDelta = 255.0/ ofRandom(3.0, 10.0) * (ofRandom(-1, 1) > 0?1:-1);
		
		//HDelta = 255.0/ ofRandom(3.0, 10.0)  *ofRandom(-1, 1) > 0?1:-1;
		//VDelta = 255.0/ ofRandom(3.0, 10.0) * ofRandom(-1, 1) > 0?1:-1;
	}

	void update(float fDelta)
	{
		H += fDelta * HDelta;
		if(H > 255)
		{
			H = 255;
			HDelta = -HDelta;
		}
		else if(H < 0)
		{
			H = 0;
			HDelta = -HDelta;
		}

		V += fDelta * VDelta;
		if(V > 255)
		{
			V = 255;
			VDelta = -VDelta;
		}
		else if(V < 0)
		{
			V = 0;
			VDelta = -VDelta;
		}
	}

	float	H, V;
	float HDelta, VDelta;
}stColorUnit;

class BCNoise : public BCBase
{
public:
	BCNoise();

	void update(const float fDelta) override;
	void draw() override;

private:
	const ofVec2f					_UnitSize;
	float									_fTimer;
	ofColor								_color;

	stColorUnit						_colorMap[cROW_NUM * cCOL_NUM];
};

#endif // !OFX_BALLON_CANVAS_NOISE
