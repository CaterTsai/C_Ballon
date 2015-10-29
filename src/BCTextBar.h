#ifndef OFX_BALLON_CANVAS_TEXTBAR
#define OFX_BALLON_CANVAS_TEXTBAR

#include "BCBase.h"
#include "ofxXmlSettings.h"
class BCTextBar : public BCBase
{
public:
	BCTextBar();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;
	void next() override;
	void setBaseColor(ofColor c) override;
	float getTriggerTime() override;

private:
	void loadText();
	void initialText(int idx);

private:
	ofTrueTypeFont		_font;
	int								_iDisplayIdx;

	ofVec2f						_StartTextPos;
	float							_PosX, _EndX;
	float							_VecX;
	vector<string>			_DisplayText;
};

#endif // !OFX_BALLON_CANVAS_TEXTBAR
