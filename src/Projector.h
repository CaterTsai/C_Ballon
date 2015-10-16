#ifndef OFX_PROJECOTR
#define OFX_PROJECOTR

#include "constParameter.h"

class Projector
{
public:
	Projector()
		:_bShowRange(false)
	{}

	void setup();
	void update(float fDelta);
	void draw(int x = 0, int y = 0);

public:
	inline void troggleRange()
	{
		_bShowRange ^= true;
	}

private:
	bool	_bShowRange;
private:
};

#endif // !OFX_PROJECOTR
