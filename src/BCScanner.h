#ifndef OFX_BALLON_CANVAS_SCANNER
#define OFX_BALLON_CANVAS_SCANNER

#include "BCBase.h"
#include "ofxAnimatableFloat.h"

class BCScanner : public BCBase
{
public:
	BCScanner(ofVec2f Start, ofVec2f End, int iLength);

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;
	float getTriggerTime() override;

private:
	void scan();
private:
	bool								_bFlip;
	ofVec2f							_Start, _End;
	int									_iLength;
	int									_iLineNum;
	ofColor							_lineColor;
	ofxAnimatableFloat	_AnimScan;

};

#endif // !OFX_BALLON_CANVAS_SCANNER
