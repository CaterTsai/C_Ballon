#ifndef OFX_BALLON_CANVAS_WAVE
#define OFX_BALLON_CANVAS_WAVE

#include "BCBase.h"

static const int cWAVE_DENSITY = 40;

typedef struct _stSinWave
{
	_stSinWave(float p = 0.0, int f = 1, float a = 1.0)
		:phase(p)
		,feq(f)
		,amplitude(a)
	{}

	float getValue(float degree)
	{
		return sin( ((degree * feq) + phase) * DEG_TO_RAD) * amplitude;
	}

	float phase, amplitude;
	int feq;
}stSinWave;

class BCWave : public BCBase
{
public:
	BCWave(vector<stSinWave>& wg);

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void setBaseColor(ofColor c) override;
	float getTriggerTime() override;

private:
	float					_Degree, _DegreeDelta, _DegreeInterval;
	float					_WaveUnitSize;
	ofVec2f				_WavePosList[cWAVE_DENSITY];
	vector<stSinWave>		_WaveGenerator;
};

#endif // !OFX_BALLON_CANVAS_WAVE
