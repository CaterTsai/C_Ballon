#ifndef OFX_BALLON_CANVAS_FIREWORK
#define OFX_BALLON_CANVAS_FIREWORK

#include "BCBase.h"
#include "ofxAnimatableFloat.h"

class Firework
{
public:
	Firework(float fDurction, int SparkNum, int height);
	void update(float fDelta);
	void draw();
	
	inline bool isDie() const
	{
		return _IsDie;
	}

private:
	bool								_IsDie, _bExplode;

	int									_iSparkNum, _iHeight;
	ofVec2f							_pos;
	ofColor							_Color;
	ofxAnimatableFloat	_AnimUp, _AnimExplode;
};

class BCFirework : public BCBase
{
public:
	BCFirework();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;

private:
	void addFirework();
private:
	float	_fTimer;
	list<Firework>		_FireworkList;
};

#endif // !OFX_BALLON_CANVAS_FIREWORK
