#ifndef OFX_BALLON_CANVAS_ROTATE_RECT
#define OFX_BALLON_CANVAS_ROTATE_RECT

#include "BCBase.h"
#include "ofxAnimatableFloat.h"

typedef struct _stRotateRect
{
	_stRotateRect(ofColor c, float fDurction, ofVec2f Central);
	void update(float fDelta);
	void draw();

	ofxAnimatableFloat	_AnimRotate;
	ofxAnimatableFloat	_AnimSize;
	ofVec2f				_Central;
	bool					_bDie;
	ofColor				_Color;
}stRotateRect;

class BCRotateRect : public BCBase
{
public:
	BCRotateRect();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void setBaseColor(ofColor c) override;
	float getTriggerTime() override;

private:
	void addRect();
private:
	ofColor			_Background;
	float				_fTimer;
	list<stRotateRect>	_RectList;
	int					_iColorFlag;
};
#endif // !OFX_BALLON_CANVAS_ROTATE_RECT
