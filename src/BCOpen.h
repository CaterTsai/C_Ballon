#ifndef OFX_BALLON_CANVAS_OPEN
#define OFX_BALLON_CANVAS_OPEN

#include "BCBase.h"
#include "ofxAnimatableFloat.h"

class BCOpen : public BCBase
{
public:
	BCOpen();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;
	float getTriggerTime() override;

private:
	void open();
private:
	
	float		_fOpenAngle, _fOpenDist;
	ofVec2f _OpenSize;
	ofxAnimatableFloat	_AnimOpenDist;
	ofColor	_NowColor, _NextColor;
};

#endif // !OFX_BALLON_CANVAS_OPEN
