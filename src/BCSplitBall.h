#ifndef OFX_BALLON_CANVAS_SPLIT_BALL
#define OFX_BALLON_CANVAS_SPLIT_BALL


#include "BCBase.h"

static const int cBALL_SIZE = 20;
static const int cMAX_LIFT_TIME = 10;
static const int cMAX_BALL_NUM = 100;
typedef struct _stSplitBall
{
	ofVec2f		pos, vel;
	//float		speed;
	float		lifeT, maxLiftT;
	ofColor		color;
	bool		firstTouch, canSplit;

	_stSplitBall(ofVec2f p, ofVec2f v, int num = 0);
	void update(float fDelta);
	void draw();

	bool getSplit();
	bool getAlive();

}SplitBall;

class BCSplitBall : public BCBase
{
public:
	BCSplitBall();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;

private:
	list<SplitBall>		_SplitBallList;

};

#endif // !OFX_BALLON_CANVAS_SPLIT_BALL
