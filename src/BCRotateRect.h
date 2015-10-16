#ifndef OFX_BALLON_CANVAS_ROTATE_RECT
#define OFX_BALLON_CANVAS_ROTATE_RECT

#include "BCBase.h"
#include "ofxAnimatableFloat.h"

typedef struct _stRotateRect
{
	_stRotateRect(float fDurction, ofVec2f Central);
	void update(float fDelta);
	void draw();

	ofxAnimatableFloat	_AnimRotate;
	ofxAnimatableFloat	_AnimSize;
	ofVec2f				_Central;
	bool				_bDie;
	ofColor				_Color;
}stRotateRect;

class BCRotateRect : public BCBase
{
public:
	BCRotateRect();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;
	float getTriggerTime() override;

private:
	void addRect();
private:
	ofColor			_Background;
	float				_fTimer;
	list<stRotateRect>	_RectList;
};
#endif // !OFX_BALLON_CANVAS_ROTATE_RECT
