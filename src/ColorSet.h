#ifndef OFX_COLOR_SET
#define OFX_COLOR_SET

#include "ofMain.h"

const static int cMAX_COLOR_SET_SIZE = 10;

class ColorSet
{
public:
	ColorSet()
		:_setIdx(0)
	{};
	~ColorSet()
	{
		Destory();
	}

	void setup();
	
	ofColor getRandomColor() const;
	ofColor getColor(int idx) const;
	void changeColorSet(int idx);

private:
	int												_setIdx;
	vector<vector<ofColor>>		_colorManager;

//-------------------
//Singleton
//-------------------
public:
	static ColorSet* GetInstance();
	static void Destory();

private:
	static ColorSet* _pInstance;
};

#endif // !OFX_COLOR_SET
