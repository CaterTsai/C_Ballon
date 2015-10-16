#ifndef OFX_BALLON_CANVAS_BLINK
#define OFX_BALLON_CANVAS_BLINK

#include "BCBase.h"

class BCBlink : public BCBase
{
public:
	BCBlink();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;

private:
	bool					_bBlink;
	ofColor				_color;
	float					_Timer;
};

#endif // !OFX_BALLON_CANVAS_BLINK
