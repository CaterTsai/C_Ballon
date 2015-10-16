#ifndef OFX_BIG_BALLON
#define OFX_BIG_BALLON

#include "constParameter.h"

class BigBallon
{
public:
	BigBallon()
		:_bShowRange(false)
	{}
	void setup();
	void update(float fDelta);
	void draw();

public:
	inline void troggleRange()
	{
		_bShowRange ^= true;
	}

private:
	bool	_bShowRange;

private:
	vector<ofPoint>		_BallonPosList;
};

#endif // !OFX_BIG_BALLON
