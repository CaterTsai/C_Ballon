#ifndef OFX_BALLON_WALL
#define OFX_BALLON_WALL

#include "constParameter.h"
#include "BAOpenH.h"
#include "LEDCtrl.h"

#pragma region enum
enum eBALLON_WALL_TYPE
{
	eBALLON_ACCESS = 0
	,eBALLON_CANVAS
	,eBALLON_FIXED	
};

#pragma endregion

class BallonWall
{
public:
	BallonWall()
		:_bShowRange(false)
		,_eWallType(eBALLON_ACCESS)
		,_BAType(eBA_OPEN_H)
	{}
	~BallonWall();

	void setup();
	void update(float fDelta);
	void draw(int x = 0, int y = 0);

	void setWallType(eBALLON_WALL_TYPE eType);


public:
	inline void troggleRange()
	{
		_bShowRange ^= true;
	}

private:
	eBALLON_WALL_TYPE	_eWallType;
	bool	_bShowRange;

#pragma region Ballon
//--------------------------------------------------------------
public:
	void clearBallon();
private:
	void initialBallon();
	void drawBallon();

private:
	int				_iRowN, _iColN;			
	vector<Ballon>	_BallonList;
#pragma endregion

#pragma region Ballon Access
//--------------------------------------------------------------
public:
	void startBA();
private:
	void initialBA();
	void releaseBA();

private:
	eBA_TYPE					_BAType;
	map<eBA_TYPE, BABase*>		_BAMap;
#pragma endregion


#pragma region Canvas
//--------------------------------------------------------------
public:
	void beginCanvas();
	void endCanvas();
	void drawCanvas();
private:
	void initialCanvas();

private:	
	ofFbo			_Canvas;
	ofFbo			_SmellCanvas;
#pragma endregion

#pragma region Convert
//--------------------------------------------------------------
private:
	void initialConvert();
	void convert();
private:
	map<int, vector<int>>	_Canvas2Ballon;
#pragma endregion

#pragma region LED Ctrl
private:
	vector<ofColor>	_PixelList;
	LEDCtrl			_LedCtrl;
#pragma endregion

};

#endif // !OFX_BALLON_WALL

