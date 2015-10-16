#ifndef OFX_BALLON_CANVAS_BACKGROUND
#define OFX_BALLON_CANVAS_BACKGROUND

#include "BCBase.h"

class BCBackground : public BCBase
{
public:
	BCBackground();	

	void draw() override;
	void start() override;
	void stop() override;

	inline void setColor(ofColor color)
	{
		_color = color;
	}

private:
	ofColor				_color;
};

#endif // !OFX_BALLON_CANVAS_BACKGROUND
