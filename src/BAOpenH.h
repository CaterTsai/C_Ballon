#ifndef OFX_BALLON_ACCESS_OPEN
#define OFX_BALLON_ACCESS_OPEN

#include "BABase.h"

class BAOpenH : public BABase
{
public:
	BAOpenH();

	void update(const float fDelta, vector<Ballon>& source) override;
	void start() override;
	void stop() override;

private:
	void setColor(vector<Ballon>& source);
	
private:
	ofColor		_NowColor;
	int			_iStartL, _iStartR;
	int			_iEndL, _iEndR;
	int			_iIdxL, _iIdxR;
};

#endif // !OFX_BALLON_ACCESS_OPEN