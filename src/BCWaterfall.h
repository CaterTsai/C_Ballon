#ifndef OFX_BALLON_CANVAS_WATERFALL
#define OFX_BALLON_CANVAS_WATERFALL

#include "BCBase.h"
#include "ofxAnimatableFloat.h"

typedef struct _stBCFallList
{
	_stBCFallList()
		:iIndex(0)
	{
		for(int idx_ = 0; idx_ < cCOL_NUM; idx_++)
		{
			bDisplayArray[idx_] = ofRandom(-1, 1) > 0;
			fAlpha[idx_] = ofRandom(0, 255);
		}
	}

	inline void next()
	{
		iIndex++;
	}

	inline bool isDie()
	{
		return (iIndex >= cROW_NUM);
	}

	int		iIndex;
	bool	bDisplayArray[cCOL_NUM];
	float	fAlpha[cCOL_NUM];
}stBCFallList;

class BCWaterfall : public BCBase
{
public:
	BCWaterfall();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void setBaseColor(ofColor c) override;
	float getTriggerTime() override;

private:
	void addWaterfall();

private:
	const ofVec2f					_UnitSize;
	float									_fTimer;
	list<stBCFallList>				_WaterfallList;
};

#endif // !OFX_BALLON_CANVAS_WATERFALL
