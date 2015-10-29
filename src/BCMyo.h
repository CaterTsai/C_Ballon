#ifndef OFX_BALLON_CANVAS_MYO
#define OFX_BALLON_CANVAS_MYO

#include "BCBase.h"
#include "ofxAnimatableFloat.h"
#include "MyoCtrl.h"

class BCMyo : public BCBase
{
public:
	BCMyo();
	void update(const float fDelta) override;
	void draw() override;

private:
	bool									_isTrigger;
	float									_fTimer;
	MyoCtrl								_CTMyo;
	const ofVec2f					_UnitSize;
};

#endif // !OFX_BALLON_CANVAS_MYO
