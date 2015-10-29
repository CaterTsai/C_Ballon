#pragma once

#include "constParameter.h"
#include "midiCtrlParameter.h"
#include "ColorSet.h"

#include "ofxAnimatableFloat.h"
#include "ofxMidi.h"
#include "ofxGui.h"

#include "MyoCtrl.h"
#include "NameManager.h"
#include "BallonWall.h"
#include "BallonCanvas.h"

class ofApp : public ofBaseApp, public ofxMidiListener 
{
public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);

private:
	float BPM2Time(int bpm);
	int Time2BPM(float time);

private:
	float			_fTimer;
	int				_iBPM;

#pragma region Ballon Wall
//Ballon Wall
public:
	void updateBC(float fDelta);
	void drawOnBC();
	void initialBC();
	void releaseBC();

private:
	void setSpeed();
	void setColor();
	void manualBlink(bool enable, ofColor color = ofColor(0));

	void nextCtrl();
	void prevCtrl();

private:
	bool					_bDrawCanvas, _bBlink;
	ofColor				_manualBlinkColor, _mainColor;
	BallonWall		_BallonWall;

	string									_NowCtrl;
	list<string>						_BCDisplayList;
	map<string, BCBase*>	_BCMap;
		
	map<eBC_GROUP, ofFbo>	_GroupCanvas;
	map<eBC_GROUP, int> _GroupAlpha;
#pragma endregion

#pragma region GUI
private:
	void initialGUI();
	void updateGUI();
	void drawGUI();

	void BPMChanged(int& BPM);
private:
	void sethighlight(string strName, bool value);

private:
	bool			_bDisplayGUI, _bHaveNext;

	ofxButton									_NextCtrl, _PrevCtrl;
	map<string, ofxToggle>		_ToggleList;
	//ofxIntSlider _BPMSlider;
	ofxPanel									_GUI;
	ofTrueTypeFont						_GUIFont;
#pragma endregion
	
#pragma region Midi Ctrl
public:
	void initialMidi();
	void releaseMidi();
	void newMidiMessage(ofxMidiMessage& msg) override;

private:
	void resetMidiLED();
	void TapBPM();

private:
	float				_fTapTimer;
	ofxMidiIn		_midiIn;
	ofxMidiOut	_midiOut;	
#pragma endregion

};
