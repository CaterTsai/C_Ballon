#ifndef OFX_BALLON_CANVAS_BACKGROUND
#define OFX_BALLON_CANVAS_BACKGROUND

#include "BCBase.h"

class BCBackground : public BCBase
{
public:
	BCBackground();	

	void draw() override;
};

#endif // !OFX_BALLON_CANVAS_BACKGROUND
