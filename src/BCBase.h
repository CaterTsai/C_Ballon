#ifndef OFX_BALLON_CANVAS_BASE
#define OFX_BALLON_CANVAS_BASE

#include "constParameter.h"
#include "BCprotocol.h"
#include "Ballon.h"

class BCBase
{
public:
	BCBase(eBC_TYPE type, eBC_GROUP group)
		:_eType(type)
		,_eGroup(group)
		,_bStart(false)
		,_fDuratcion(0.0)
		,_baseColor(ofColor(0))
	{}
	virtual ~BCBase(){}

	//virtual void setup(){}
	virtual void update(const float fDelta){}
	virtual void draw(){}
	virtual void start()
	{
		_bStart = true;
	}
	
	virtual void stop()
	{
		_bStart = false;
	}
	
	virtual void next(){}
	
	virtual void setDuratcionTime(float duratctionT)
	{
		_fDuratcion = duratctionT;
	}

	virtual void setBaseColor(ofColor c)
	{
		_baseColor.set(c);
	}

	virtual float getTriggerTime()
	{
		return _fDuratcion;
	}

	//ctrl interface
	virtual void setParam1(int value){}
	virtual void setParam2(int value){}
	virtual void setParam3(int value){}
	
	inline bool getIsStart() const
	{
		return _bStart;
	}

	inline eBC_GROUP getGroup() const
	{
		return _eGroup;
	}
protected:
	bool					_bStart;
	ofColor				_baseColor;
	eBC_TYPE			_eType;
	eBC_GROUP		_eGroup;
	float					_fDuratcion;
};

#endif // !OFX_BALLON_CANVAS_BASE
