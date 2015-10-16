#include "ofApp.h"

#pragma region Base function
//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetCircleResolution(50);
	_iBPM = 120;

	//Color Set
	ColorSet::GetInstance()->setup();

	//Ballon 
	//Ballon Wall
	_BallonWall.setup();
	_BallonWall.setWallType(eBALLON_CANVAS);

	//Ballon Canvas
	initialBC();
	
	//GUI
	initialGUI();

	//Midi Ctrl
	initialMidi();

	_BallonWall.clearBallon();


	_fTimer = ofGetElapsedTimef();
	
	_bDrawCanvas = false;

}

//--------------------------------------------------------------
void ofApp::update()
{
	float fDelta_ = ofGetElapsedTimef() - _fTimer;
	_fTimer += fDelta_;

	//Draw on Canvas
	updateBC(fDelta_);
	drawOnBC();

	_BallonWall.update(fDelta_);

	updateGUI();

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//Draw Ballon wall
	_BallonWall.draw(cGUI_WIDTH, 0);
	if(_bDrawCanvas)
	{
		_BallonWall.drawCanvas();
	}

	drawGUI();
}

//--------------------------------------------------------------
void ofApp::exit()
{
	releaseBC();
	releaseMidi();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch(key)
	{
	case 'c':
		{
			_bDrawCanvas ^= true;
		}
		break;
	case 'g':
		{
			_bDisplayGUI ^= true;
		}
		break;
	}
}
//--------------------------------------------------------------
float ofApp::BPM2Time(int bpm)
{
	return (60.0 / bpm);
}

//--------------------------------------------------------------
int ofApp::Time2BPM(float time)
{
	return static_cast<int>(60.0/time);
}
#pragma endregion

#pragma region Ballon Wall
//--------------------------------------------------------------
void ofApp::updateBC(float fDelta)
{
	for(auto& Iter_ : _BCDisplayList)
	{
		if(_BCMap[Iter_]->getIsStart())
		{
			_BCMap[Iter_]->update(fDelta);
		}
	}
}

//--------------------------------------------------------------
void ofApp::drawOnBC()
{
	ofPushStyle();
	_BallonWall.beginCanvas();
	{
		ofClear(0);

		for(auto& Iter_ : _BCDisplayList)
		{
			if(_BCMap[Iter_]->getIsStart())
			{
				_BCMap[Iter_]->draw();
			}
		}

		//manual Blick
		if(_bBlink)
		{
			ofClear(255);
		}
	}
	_BallonWall.endCanvas();
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::initialBC()
{
	float fTime_ = BPM2Time(_iBPM);

	//------------------------
	//Background
	BCBase*	pBCBackground_ = new BCBackground();
	_BCMap.insert(make_pair(NAME_MGR::B1_BACKGROUND, pBCBackground_));

	BCBase* pBCVideo_ = new BCVideos("BCVideos_2/");
	_BCMap.insert(make_pair(NAME_MGR::B2_VIDEO_SET1, pBCVideo_));

	BCBase*	pBCRotateRect_ = new BCRotateRect();
	_BCMap.insert(make_pair(NAME_MGR::B5_ROTATE_RECT, pBCRotateRect_));
	
	BCBase* pBCOpen_ = new BCOpen();
	_BCMap.insert(make_pair(NAME_MGR::B6_OPEN, pBCOpen_));

	BCBase* pBCNoise_ = new BCNoise();
	_BCMap.insert(make_pair(NAME_MGR::B7_NOISE, pBCNoise_));

	//------------------------
	//Object
	BCBase* pBCRain_ = new BCRain();
	_BCMap.insert(make_pair(NAME_MGR::C1_RAIN, pBCRain_));

	BCBase* pBCSplitBall_ = new BCSplitBall();
	_BCMap.insert(make_pair(NAME_MGR::C2_SPLIT_BALL, pBCSplitBall_));
	
	vector<stSinWave> sinWave_;
	//sinWave_.push_back(stSinWave(0, 17, cCANVAS_HEIGHT * 0.2));
	sinWave_.push_back(stSinWave(60, 2, cCANVAS_HEIGHT * 0.3));
	BCBase* pBCWave_ = new BCWave(sinWave_);
	_BCMap.insert(make_pair(NAME_MGR::C3_WAVE, pBCWave_));
	
	BCBase* pBCSnake_ = new BCSnake();
	_BCMap.insert(make_pair(NAME_MGR::C4_SNAKE, pBCSnake_));

	BCBase* pBCFirework_ = new BCFirework();
	_BCMap.insert(make_pair(NAME_MGR::C5_FIREWORK, pBCFirework_));

	BCBase* pBCScannerH_ = new BCScanner(
		ofVec2f(cSCANNER_WIDTH/2, cCANVAS_HEIGHT/2)
		,ofVec2f(cCANVAS_WIDTH - cSCANNER_WIDTH/2, cCANVAS_HEIGHT/2)
		,cCANVAS_HEIGHT
	);
	_BCMap.insert(make_pair(NAME_MGR::C6_SCANNER_H, pBCScannerH_));

	BCBase* pBCScannerV_ = new BCScanner(
		ofVec2f(cCANVAS_WIDTH/2, cSCANNER_WIDTH/2)
		,ofVec2f(cCANVAS_WIDTH/2, cCANVAS_HEIGHT - cSCANNER_WIDTH/2)
		,cCANVAS_WIDTH
	);
	_BCMap.insert(make_pair(NAME_MGR::C7_SCANNER_V, pBCScannerV_));

	//------------------------
	//Foreground
	BCBase* pBCWaterfall_ = new BCWaterfall();
	_BCMap.insert(make_pair(NAME_MGR::F1_WATERFALL, pBCWaterfall_));

	BCBase* pBCCross_ = new BCCross();
	_BCMap.insert(make_pair(NAME_MGR::F2_CROSS, pBCCross_));
	
	BCBase* pBCBlink_ = new BCBlink();
	_BCMap.insert(make_pair(NAME_MGR::F3_SIMPLE_BLINK, pBCBlink_));

	//initial display order
	//Background
	_BCDisplayList.push_back(NAME_MGR::B1_BACKGROUND);
	_BCDisplayList.push_back(NAME_MGR::B2_VIDEO_SET1);
	_BCDisplayList.push_back(NAME_MGR::B5_ROTATE_RECT);
	_BCDisplayList.push_back(NAME_MGR::B6_OPEN);
	_BCDisplayList.push_back(NAME_MGR::B7_NOISE);
	
	//Full effect
	_BCDisplayList.push_back(NAME_MGR::C1_RAIN);
	_BCDisplayList.push_back(NAME_MGR::C2_SPLIT_BALL);
	_BCDisplayList.push_back(NAME_MGR::C3_WAVE);
	_BCDisplayList.push_back(NAME_MGR::C4_SNAKE);
	_BCDisplayList.push_back(NAME_MGR::C5_FIREWORK);
	_BCDisplayList.push_back(NAME_MGR::C6_SCANNER_H);	
	_BCDisplayList.push_back(NAME_MGR::C7_SCANNER_V);	
	
	//Foregound
	_BCDisplayList.push_back(NAME_MGR::F1_WATERFALL);
	_BCDisplayList.push_back(NAME_MGR::F2_CROSS);
	_BCDisplayList.push_back(NAME_MGR::F3_SIMPLE_BLINK);

	_NowCtrl = "";
	//sethighlight((*_NowCtrlIter), true);
	setSpeed();
	_bBlink = false;
}

//--------------------------------------------------------------
void ofApp::releaseBC()
{
	for(auto& Iter_ : _BCMap)
	{
		delete Iter_.second;
	}

	_BCMap.clear();
}

//--------------------------------------------------------------
void ofApp::setSpeed()
{
	float fTime_ = BPM2Time(_iBPM);
	for(auto& Iter_ : _BCMap)
	{
		if(Iter_.first != NAME_MGR::B7_NOISE)
		{
			Iter_.second->setDuratcionTime(fTime_);
		}
	}
}

//--------------------------------------------------------------
void ofApp::manualBlink(bool enable)
{
	_bBlink = enable;
}

//--------------------------------------------------------------
void ofApp::nextCtrl()
{
	bool bStart_ = false;
	for(auto& Iter_ : _BCDisplayList)
	{
		if(!bStart_ && Iter_ == _NowCtrl || _NowCtrl == "")
		{
			bStart_ = true;
		}
		
		if(bStart_ && _ToggleList[Iter_] && Iter_ != _NowCtrl)
		{
			sethighlight(_NowCtrl, false);
			sethighlight(Iter_, true);
			_NowCtrl = Iter_;
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::prevCtrl()
{
	string temp_ = "";
	for(auto& Iter_ : _BCDisplayList)
	{
		if(Iter_ == _NowCtrl)
		{
			break;
		}

		if(_ToggleList[Iter_] && Iter_ != _NowCtrl)
		{
			temp_ = Iter_;
			//break;
		}
	}

	if(temp_ != "")
	{
		sethighlight(_NowCtrl, false);
		sethighlight(temp_, true);
		_NowCtrl = temp_;
	}
}
#pragma endregion

#pragma region GUI
//--------------------------------------------------------------
void ofApp::initialGUI()
{
	_BPMSlider.addListener(this, &ofApp::BPMChanged);
	_NextCtrl.addListener(this, &ofApp::nextCtrl);
	_PrevCtrl.addListener(this, &ofApp::prevCtrl);
	_bDisplayGUI = true;
	_GUI.setup();

	_GUI.add(_NextCtrl.setup("Next Ctrl"));
	_GUI.add(_PrevCtrl.setup("Prev Ctrl"));

	for(auto& Iter_ : _BCDisplayList)
	{
		ofxToggle toggle_;
		_ToggleList.insert(make_pair(Iter_, toggle_));
	}

	for(auto& Iter_ : _ToggleList)
	{
		_GUI.add(Iter_.second.setup(Iter_.first, false));
	}

	_GUI.add(_BPMSlider.setup("BPM Slider", 120, cMIN_BPM, cMAX_BPM));
	_iBPM = 120;
}

//--------------------------------------------------------------
void ofApp::updateGUI()
{
	for(auto& Iter_ : _ToggleList)
	{
		if(Iter_.second && !_BCMap[Iter_.first]->getIsStart())
		{
			_BCMap[Iter_.first]->start();
		}
		else if(!Iter_.second && _BCMap[Iter_.first]->getIsStart())
		{
			_BCMap[Iter_.first]->stop();
		}
	}
}

//--------------------------------------------------------------
void ofApp::drawGUI()
{
	if(_bDisplayGUI)
	{
		_GUI.draw();
	}
}

//--------------------------------------------------------------
void ofApp::BPMChanged(int& BPM)
{
	_iBPM = BPM;
	setSpeed();
}

//--------------------------------------------------------------
void ofApp::sethighlight(string strName, bool value)
{
	if(strName == "")
	{
		return;
	}

	if(value)
	{
		_ToggleList[strName].setBackgroundColor(ofColor(255, 128, 0));
	}
	else
	{
		_ToggleList[strName].setBackgroundColor(ofColor(0, 0, 0));
	}
}
#pragma endregion

#pragma region Midi Ctrl
//--------------------------------------------------------------
void ofApp::initialMidi()
{
	if(!_midiIn.openPort())
	{	
		return;
	}
	_fTapTimer = ofGetElapsedTimef();
	_midiIn.ignoreTypes(false, false, false);
	_midiIn.addListener(this);
}

//--------------------------------------------------------------
void ofApp::releaseMidi()
{
	if(_midiIn.isOpen())
	{
		_midiIn.closePort();
		_midiIn.removeListener(this);
	}
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg)
{
	switch(msg.control)
	{
	case eMC_SPEED_SLIDER:
		{
			_BPMSlider = ofMap(msg.value, cMIDI_MIN_VALUE, cMIDI_MAX_VALUE, cMIN_BPM, cMAX_BPM, true);
		}
		break;
	case eMC_SPEED_TAP:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				TapBPM();
			}
		}
		break;
	case eMC_MANUAL_BLINK:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				manualBlink(true);
			}
			else if(msg.value == cMIDI_BTN_RELEASE)
			{
				manualBlink(false);
			}
		}
		break;
	case eMC_CTRL_NEXT:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				nextCtrl();
			}
		}
		break;
	case eMC_CTRL_PREV:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				prevCtrl();
			}
		}
		break;
	//--------------------------------------------------
	case eMC_BACKGROUND:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B1_BACKGROUND];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::B1_BACKGROUND, true);
					_NowCtrl = NAME_MGR::B1_BACKGROUND;
				}
			}
		}
		break;
	case eMC_VIDEO_SET1:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B2_VIDEO_SET1];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::B2_VIDEO_SET1, true);
					_NowCtrl = NAME_MGR::B2_VIDEO_SET1;
				}
			}
		}
		break;
	case eMC_ROTATE_TECT:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B5_ROTATE_RECT];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::B5_ROTATE_RECT, true);
					_NowCtrl = NAME_MGR::B5_ROTATE_RECT;
				}
			}
		}
		break;
	case eMC_OPEN:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B6_OPEN];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::B6_OPEN, true);
					_NowCtrl = NAME_MGR::B6_OPEN;
				}
			}
		}
		break;
	case eMC_NOISE:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B7_NOISE];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::B7_NOISE, true);
					_NowCtrl = NAME_MGR::B7_NOISE;
				}
			}
		}
		break;
	case eMC_RAIN:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C1_RAIN];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::C1_RAIN, true);
					_NowCtrl = NAME_MGR::C1_RAIN;
				}
			}
		}
		break;
	case eMC_SPLIT_BALL:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C2_SPLIT_BALL];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::C2_SPLIT_BALL, true);
					_NowCtrl = NAME_MGR::C2_SPLIT_BALL;
				}
			}
		}
		break;
	case eMC_WAVE:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C3_WAVE];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::C3_WAVE, true);
					_NowCtrl = NAME_MGR::C3_WAVE;
				}
			}
		}
		break;
	case eMC_SNAKE:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C4_SNAKE];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::C4_SNAKE, true);
					_NowCtrl = NAME_MGR::C4_SNAKE;
				}
			}
		}
		break;
	case eMC_FIREWORK:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C5_FIREWORK];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::C5_FIREWORK, true);
					_NowCtrl = NAME_MGR::C5_FIREWORK;
				}
			}
		}
		break;
	case eMC_SCANNER_H:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C6_SCANNER_H];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::C6_SCANNER_H, true);
					_NowCtrl = NAME_MGR::C6_SCANNER_H;
				}
			}
		}
		break;
	case eMC_SCANNER_V:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C7_SCANNER_V];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::C7_SCANNER_V, true);
					_NowCtrl = NAME_MGR::C7_SCANNER_V;
				}
			}
		}
		break;
	case eMC_WATERFALL:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::F1_WATERFALL];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::F1_WATERFALL, true);
					_NowCtrl = NAME_MGR::F1_WATERFALL;
				}
			}
		}
		break;
	case eMC_CROSS:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::F2_CROSS];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::F2_CROSS, true);
					_NowCtrl = NAME_MGR::F2_CROSS;
				}
			}
		}
		break;
	case eMC_SIMPLE_BLINK:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::F3_SIMPLE_BLINK];
				Toggle_ = !Toggle_;

				if(Toggle_)
				{
					sethighlight(_NowCtrl, false);
					sethighlight(NAME_MGR::F3_SIMPLE_BLINK, true);
					_NowCtrl = NAME_MGR::F3_SIMPLE_BLINK;
				}
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::TapBPM()
{
	float fDelta_ = ofGetElapsedTimef() - _fTapTimer;
	_fTapTimer += fDelta_;

	if(fDelta_ > 1.0)
	{
		return;
	}
	else
	{
		_iBPM = MAX(MIN(Time2BPM(fDelta_), cMAX_BPM), cMIN_BPM);
		_BPMSlider = _iBPM;		
	}
	

}
#pragma endregion