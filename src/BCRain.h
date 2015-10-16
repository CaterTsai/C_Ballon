#ifndef OFX_BALLON_CANVAS_RAIN
#define OFX_BALLON_CANVAS_RAIN

#include "BCBase.h"
#include "ofxAnimatableFloat.h"

typedef struct _stRain
{
	_stRain(float fDurction);
	void update(float fDelta);
	void draw();

	ofxAnimatableFloat	_AnimDrop;
	float				_PosX;
	bool				_bDie;
	float				_fSize;
	ofColor			_Color;
}stRain;

class BCRain : public BCBase
{
public:
	BCRain();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;
	float getTriggerTime() override;

private:
	void addRain();
private:
	float			_fTimer, _fFadeAmnt;
	list<stRain>	_RainList;
};

#endif // !OFX_BALLON_CANVAS_RAIN
