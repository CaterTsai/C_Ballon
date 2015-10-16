#ifndef OFX_BALLON_CANVAS_SNAKE
#define OFX_BALLON_CANVAS_SNAKE

#include "BCBase.h"
#include "ofxAnimatableFloat.h"

class Snake
{
public:
	Snake(int maxTurn, ofColor color, ofVec2f StartPos, ofVec2f Vel);
	void update(float fDelta);
	void draw();
	
public:
	inline bool isDie()
	{
		return _isDie;
	}
private:
	void turn();

private:
	bool						_isDie, _CanDie;
	int							_iTurnNum;
	const int				_maxTurn;
	float						_length, _timer, _moveLength;
	ofColor					_color;

	ofVec2f					_Vel;
	list<ofVec2f>		_posList;
};

class BCSnake : public BCBase
{
public:
	BCSnake();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;
	float getTriggerTime() override;

private:
	void addSnake();

private:
	list<Snake>	_SnakeMgr;
	float				_fTimer;
	
};

#endif // !OFX_BALLON_CANVAS_SNAKE
