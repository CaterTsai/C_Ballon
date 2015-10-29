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
	void setBaseColor(ofColor c) override;
	float getTriggerTime() override;

private:
	void open();
private:
	
	float		_fOpenAngle, _fOpenDist;
	ofVec2f _OpenSize;
	ofxAnimatableFloat	_AnimOpenDist;
	int			_iColorFlag;
};

#endif // !OFX_BALLON_CANVAS_OPEN
