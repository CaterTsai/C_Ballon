#ifndef OFX_COLOR_SET
#define OFX_COLOR_SET

#include "ofMain.h"
#include "BCprotocol.h"

class ColorSet
{
public:
	ColorSet();

	~ColorSet()
	{
		Destory();
	}

	ofColor getColor(int iType);

	void setHue(float Hue);
	void setLight(float fLight);

private:
	ofColor										_MainColor;
	map<eBC_TYPE, ofColor>	_ColorMap;	

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
