#ifndef OFX_BALLON_CANVAS_CROSS
#define OFX_BALLON_CANVAS_CROSS

#include "BCBase.h"

class BCCross : public BCBase
{
public:
	BCCross();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;
	void setDuratcionTime(float duratctionT) override;
	float getTriggerTime() override;

private:
	const ofVec2f	_UnitSize;
	ofColor				_color;
	deque<int>		_CrossMap[cROW_NUM];
	float					_Timer[cROW_NUM];
	float					_BaseTimer[cROW_NUM];

};

#endif // !OFX_BALLON_CANVAS_CROSS
