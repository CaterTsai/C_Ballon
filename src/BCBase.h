#ifndef OFX_BALLON_CANVAS_BASE
#define OFX_BALLON_CANVAS_BASE

#include "constParameter.h"
#include "ColorSet.h"
#include "Ballon.h"

enum eBC_TYPE : int
{
	eBC_BACKGROUND  = 0
	,eBC_ROTATE_RECT	=	0	
	,eBC_BLINK
	,eBC_NOISE
	,eBC_VIDEO
	,eBC_RAIN
	,eBC_SPLIT_BALL
	,eBC_WAVE
	,eBC_OPEN
	,eBC_SNAKE
	,eBC_FIREWORK
	,eBC_SCANNER
	,eBC_WATERFALL
	,eBC_CROSS	
	,eBC_TYPE_NUM
};

class BCBase
{
public:
	BCBase(eBC_TYPE type)
		:_eType(type)
		,_bStart(false)
		,_fDuratcion(0.0)
	{}
	virtual ~BCBase(){}

	//virtual void setup(){}
	virtual void update(const float fDelta){}
	virtual void draw(){}
	virtual void start(){}
	virtual void stop(){}
	virtual void next(){}

	//ctrl interface
	virtual void setParam1(int value){}
	virtual void setParam2(int value){}
	virtual void setParam3(int value){}

	virtual float getTriggerTime()
	{
		return _fDuratcion;
	}

	virtual void setDuratcionTime(float duratctionT)
	{
		_fDuratcion = duratctionT;
	}

	inline bool getIsStart() const
	{
		return _bStart;
	}
protected:
	bool		_bStart;
	eBC_TYPE	_eType;

	float		_fDuratcion;
};

#endif // !OFX_BALLON_CANVAS_BASE
