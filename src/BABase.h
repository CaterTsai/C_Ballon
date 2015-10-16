#ifndef OFX_BALLON_ACCESS_BASE
#define OFX_BALLON_ACCESS_BASE

#include "constParameter.h"
#include "Ballon.h"
#include "ofxAnimatableFloat.h"

enum eBA_TYPE : int
{
	eBA_OPEN_H	=	0
	,eBA_TYPE_NUM
};

class BABase
{
public:
	BABase(eBA_TYPE type)
		:_eType(type)
		,_bStart(false)
		,_fTimer(0.0)
		,_fIntervalTime(1.0)
	{}
	virtual ~BABase(){}

	//virtual void setup(){}
	virtual void update(const float fDelta, vector<Ballon>& source){}
	virtual void start(){}
	virtual void stop(){}

	inline void setIntervalTime(float IntervalT)
	{
		_fIntervalTime = IntervalT;
	}

protected:
	bool		_bStart;
	eBA_TYPE	_eType;

	float		_fTimer, _fIntervalTime;
};

#endif // !OFX_BALLON_ACCESS_BASE
