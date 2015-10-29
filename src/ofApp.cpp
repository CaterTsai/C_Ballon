#include "ofApp.h"

#pragma region Base function
//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);
	ofSetFrameRate(20);
	ofSetCircleResolution(50);
	_iBPM = 120;

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
	_BallonWall._LedCtrl.toggle();
	
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
		case 's':
		{
			_BallonWall._LedCtrl.toggle();
		}
		break;
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
	//clear all canvas
	for(auto& Iter_ : _GroupCanvas)
	{
		Iter_.second.begin();
		ofClear(0);
		Iter_.second.end();
	}
	
	for(auto& Iter_ : _BCDisplayList)
	{
		if(_BCMap[Iter_]->getIsStart())
		{
			ofPushStyle();
			ofSetColor(255);
			eBC_GROUP eGroup_ = _BCMap[Iter_]->getGroup();
			_GroupCanvas[eGroup_].begin();
			_BCMap[Iter_]->draw();
			_GroupCanvas[eGroup_].end();
			ofPopStyle();
		}
	}

	ofPushStyle();
	_BallonWall.beginCanvas();
	{
		ofClear(0);

		for(auto& Iter_ : _GroupCanvas)
		{
			ofPushStyle();
			ofSetColor(255, _GroupAlpha[Iter_.first]);
			Iter_.second.draw(0, 0);
			ofPopStyle();
		}		

		//manual Blick
		if(_bBlink)
		{
			ofClear(_manualBlinkColor);
		}
	}
	_BallonWall.endCanvas();
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::initialBC()
{
	float fTime_ = BPM2Time(_iBPM);

	ofFbo canvasB_, canvasC_, canvasF_;
	canvasB_.allocate(cCANVAS_WIDTH, cCANVAS_HEIGHT,GL_RGBA);
	canvasC_.allocate(cCANVAS_WIDTH, cCANVAS_HEIGHT,GL_RGBA);
	canvasF_.allocate(cCANVAS_WIDTH, cCANVAS_HEIGHT,GL_RGBA);

	_GroupCanvas.insert(make_pair(eG_BACKGROUND, canvasB_));
	_GroupCanvas.insert(make_pair(eG_OBJECT, canvasC_));
	_GroupCanvas.insert(make_pair(eG_FOREGROUND, canvasF_));

	_GroupAlpha[eG_BACKGROUND] = 255;
	_GroupAlpha[eG_OBJECT] = 255;
	_GroupAlpha[eG_FOREGROUND] = 255;

	//------------------------
	//Background
	BCBase*	pBCBackground_ = new BCBackground();
	_BCMap.insert(make_pair(NAME_MGR::B1_BACKGROUND, pBCBackground_));

	BCBase*	pBCRotateRect_ = new BCRotateRect();
	_BCMap.insert(make_pair(NAME_MGR::B2_ROTATE_RECT, pBCRotateRect_));
	
	BCBase* pBCOpen_ = new BCOpen();
	_BCMap.insert(make_pair(NAME_MGR::B3_OPEN, pBCOpen_));

	BCBase* pBCNoise_ = new BCNoise();
	_BCMap.insert(make_pair(NAME_MGR::B4_NOISE, pBCNoise_));

	BCBase* pBCVideo1_ = new BCVideos("VideoSet_1/");
	_BCMap.insert(make_pair(NAME_MGR::B5_VIDEO_SET1, pBCVideo1_));

	BCBase* pBCVideo2_ = new BCVideos("VideoSet_2/");
	_BCMap.insert(make_pair(NAME_MGR::B6_VIDEO_SET2, pBCVideo2_));

	BCBase* pBCVideo3_ = new BCVideos("VideoSet_3/");
	_BCMap.insert(make_pair(NAME_MGR::B7_VIDEO_SET3, pBCVideo3_));

	//------------------------
	//Object
	BCBase* pBCRain_ = new BCRain();
	_BCMap.insert(make_pair(NAME_MGR::C1_RAIN, pBCRain_));

	BCBase* pBCMetaball_ = new BCMetaball();
	_BCMap.insert(make_pair(NAME_MGR::C2_METABALL, pBCMetaball_));

	vector<stSinWave> sinWave_;
	//sinWave_.push_back(stSinWave(0, 17, cCANVAS_HEIGHT * 0.2));
	sinWave_.push_back(stSinWave(60, 2, cCANVAS_HEIGHT * 0.3));
	BCBase* pBCWave_ = new BCWave(sinWave_);
	_BCMap.insert(make_pair(NAME_MGR::C3_WAVE, pBCWave_));
	
	BCBase* pBCSnake_ = new BCSnake();
	_BCMap.insert(make_pair(NAME_MGR::C4_SNAKE, pBCSnake_));

	BCBase* pBCFirework_ = new BCFirework();
	_BCMap.insert(make_pair(NAME_MGR::C5_FIREWORK, pBCFirework_));

	BCBase* pBCTextBar_ = new BCTextBar();
	_BCMap.insert(make_pair(NAME_MGR::C6_TEXT_BAR, pBCTextBar_));

	BCBase* pBCScannerH_ = new BCScanner(
		ofVec2f(cSCANNER_WIDTH/2, cCANVAS_HEIGHT/2)
		,ofVec2f(cCANVAS_WIDTH - cSCANNER_WIDTH/2, cCANVAS_HEIGHT/2)
		,cCANVAS_HEIGHT
	);
	_BCMap.insert(make_pair(NAME_MGR::C7_SCANNER_H, pBCScannerH_));

	BCBase* pBCScannerV_ = new BCScanner(
		ofVec2f(cCANVAS_WIDTH/2, cSCANNER_WIDTH/2)
		,ofVec2f(cCANVAS_WIDTH/2, cCANVAS_HEIGHT - cSCANNER_WIDTH/2)
		,cCANVAS_WIDTH
	);
	_BCMap.insert(make_pair(NAME_MGR::C8_SCANNER_V, pBCScannerV_));

	//------------------------
	//Foreground
	BCBase* pBCWaterfall_ = new BCWaterfall();
	_BCMap.insert(make_pair(NAME_MGR::F1_WATERFALL, pBCWaterfall_));

	BCBase* pBCCross_ = new BCCross();
	_BCMap.insert(make_pair(NAME_MGR::F2_CROSS, pBCCross_));
	
	BCBase* pBCBlinkW_ = new BCBlink(ofColor(230, 230, 230));
	_BCMap.insert(make_pair(NAME_MGR::F3_SIMPLE_BLINK_W, pBCBlinkW_));

	BCBase* pBCBlinkB_ = new BCBlink(ofColor(0));
	_BCMap.insert(make_pair(NAME_MGR::F4_SIMPLE_BLINK_B, pBCBlinkB_));

	BCBase* pBCMyo_ = new BCMyo();
	_BCMap.insert(make_pair(NAME_MGR::F5_MYO_COLOR_BLINK, pBCMyo_));

	//initial display order
	//Background
	_BCDisplayList.push_back(NAME_MGR::B1_BACKGROUND);
	_BCDisplayList.push_back(NAME_MGR::B2_ROTATE_RECT);
	_BCDisplayList.push_back(NAME_MGR::B3_OPEN);
	_BCDisplayList.push_back(NAME_MGR::B4_NOISE);
	_BCDisplayList.push_back(NAME_MGR::B5_VIDEO_SET1);
	_BCDisplayList.push_back(NAME_MGR::B6_VIDEO_SET2);
	_BCDisplayList.push_back(NAME_MGR::B7_VIDEO_SET3);
	
	//Full effect
	_BCDisplayList.push_back(NAME_MGR::C1_RAIN);
	_BCDisplayList.push_back(NAME_MGR::C2_METABALL);	
	_BCDisplayList.push_back(NAME_MGR::C3_WAVE);
	_BCDisplayList.push_back(NAME_MGR::C4_SNAKE);
	_BCDisplayList.push_back(NAME_MGR::C5_FIREWORK);
	_BCDisplayList.push_back(NAME_MGR::C6_TEXT_BAR);
	_BCDisplayList.push_back(NAME_MGR::C7_SCANNER_H);	
	_BCDisplayList.push_back(NAME_MGR::C8_SCANNER_V);		
	
	//Foregound
	_BCDisplayList.push_back(NAME_MGR::F1_WATERFALL);
	_BCDisplayList.push_back(NAME_MGR::F2_CROSS);
	_BCDisplayList.push_back(NAME_MGR::F3_SIMPLE_BLINK_W);
	_BCDisplayList.push_back(NAME_MGR::F4_SIMPLE_BLINK_B);
	_BCDisplayList.push_back(NAME_MGR::F5_MYO_COLOR_BLINK);

	_NowCtrl = "";
	_mainColor.set(255, 0, 0);
	//sethighlight((*_NowCtrlIter), true);
	setSpeed();
	setColor();
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
		if(Iter_.first != NAME_MGR::B4_NOISE)
		{
			Iter_.second->setDuratcionTime(fTime_);
		}
	}
}

//--------------------------------------------------------------
void ofApp::setColor()
{
	for(auto& Iter_ : _BCMap)
	{
		if(Iter_.first != NAME_MGR::B4_NOISE)
		{
			Iter_.second->setBaseColor(_mainColor);
		}
	}
}
//--------------------------------------------------------------
void ofApp::manualBlink(bool enable, ofColor color)
{
	_bBlink = enable;
	_manualBlinkColor.set(color);
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
	_GUIFont.loadFont("bold.otf", cGUI_FONT_SIZE);
	_NextCtrl.setDefaultHeight(20);
	_NextCtrl.addListener(this, &ofApp::nextCtrl);
	_PrevCtrl.setDefaultHeight(20);
	_PrevCtrl.addListener(this, &ofApp::prevCtrl);
	_bDisplayGUI = true;
	_GUI.loadFont("bold.otf", 16);
	_GUI.setup();

	_GUI.add(_NextCtrl.setup("Next Ctrl"));
	_GUI.add(_PrevCtrl.setup("Prev Ctrl"));

	for(auto& Iter_ : _BCDisplayList)
	{
		ofxToggle toggle_;
		toggle_.setDefaultHeight(20);
		_ToggleList.insert(make_pair(Iter_, toggle_));
	}

	for(auto& Iter_ : _ToggleList)
	{
		_GUI.add(Iter_.second.setup(Iter_.first, false));
	}
	_iBPM = 120;
	_bHaveNext = false;
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
		ofPushStyle();
		_GUI.draw();
		
		int tmpY_ = _GUI.getHeight() + cGUI_FONT_SIZE * 2;
		_GUIFont.drawString(ofToString(_iBPM), 0, tmpY_);

		ofColor _BC, _OC, _FC;
		_BC = _mainColor;
		_OC = _BC;
		_OC.setHueAngle(_BC.getHueAngle() + 180);
		_FC = _BC;
		_FC.setHueAngle(_BC.getHueAngle() + 240);

		ofSetColor(_BC);
		ofRect(0, tmpY_, 30, 30);
		ofSetColor(_OC);
		ofRect(30, tmpY_, 30, 30);
		ofSetColor(_FC);
		ofRect(60, tmpY_, 30, 30);

		if(_bHaveNext)
		{
			ofSetColor(255, 255, 0);
			_GUIFont.drawString("Have Next", 0, tmpY_ + 30 + _GUIFont.getSize());
		}

		ofPopStyle();
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
	if(strName == NAME_MGR::B5_VIDEO_SET1 || strName == NAME_MGR::B6_VIDEO_SET2 ||
		strName == NAME_MGR::B7_VIDEO_SET3 || strName == NAME_MGR::C6_TEXT_BAR)
	{
		_bHaveNext = value;
	}
	
	//if(strName == "")
	//{
	//	return;
	//}

	//if(value)
	//{
	//	_ToggleList[strName].setBackgroundColor(ofColor(255, 128, 0));
	//}
	//else
	//{
	//	_ToggleList[strName].setBackgroundColor(ofColor(0, 0, 0));
	//}
}
#pragma endregion

#pragma region Midi Ctrl
//--------------------------------------------------------------
void ofApp::initialMidi()
{
	if(!_midiIn.openPort())
	{	
		ofLog(OF_LOG_ERROR, "[MIDI] open midi in port failed");
		return;		
	}
	_fTapTimer = ofGetElapsedTimef();
	_midiIn.ignoreTypes(false, false, false);
	_midiIn.addListener(this);

	if(!_midiOut.openPort("nanoKONTROL2 1 CTRL"))
	{
		ofLog(OF_LOG_ERROR, "[MIDI] open midi out port failed");
		return;
	}
	
	resetMidiLED();
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
			int newSpeed_ = static_cast<int>(ofMap(msg.value, cMIDI_MIN_VALUE, cMIDI_MAX_VALUE, cMIN_BPM, cMAX_BPM, true));
			//_BPMSlider = ofMap(msg.value, cMIDI_MIN_VALUE, cMIDI_MAX_VALUE, cMIN_BPM, cMAX_BPM, true);
			BPMChanged(newSpeed_);
		}
		break;
	case eMC_B_ALPHA_LEVEL:
		{
			_GroupAlpha[eG_BACKGROUND] = ofMap(msg.value, cMIDI_MIN_VALUE, cMIDI_MAX_VALUE, 0, 255, true);
		}
		break;
	case eMC_C_ALPHA_LEVEL:
		{
			_GroupAlpha[eG_OBJECT] = ofMap(msg.value, cMIDI_MIN_VALUE, cMIDI_MAX_VALUE, 0, 255, true);
		}
		break;
	case eMC_F_ALPHA_LEVEL:
		{
			_GroupAlpha[eG_FOREGROUND] = ofMap(msg.value, cMIDI_MIN_VALUE, cMIDI_MAX_VALUE, 0, 255, true);
		}
		break;
	case eMC_COLOR_HUE:
		{
			float fHue_ = ofMap(msg.value, cMIDI_MIN_VALUE, cMIDI_MAX_VALUE, 0, 255, true);
			_mainColor.setHue(fHue_);
			setColor();
		}
		break;
	case eMC_COLOR_LIGHT:
		{
			float fLight_ = ofMap(msg.value, cMIDI_MIN_VALUE, cMIDI_MAX_VALUE, 1, 255, true);
			_mainColor.setBrightness(fLight_);
			setColor();
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
	case eMC_MANUAL_BLINK_B:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				manualBlink(true, ofColor(0));
			}
			else if(msg.value == cMIDI_BTN_RELEASE)
			{
				manualBlink(false);
			}
		}
		break;
	case eMC_MANUAL_BLINK_W:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				manualBlink(true, ofColor(255));
			}
			else if(msg.value == cMIDI_BTN_RELEASE)
			{
				manualBlink(false);
			}
		}
		break;
	//case eMC_CTRL_NEXT:
	//	{
	//		if(msg.value == cMIDI_BTN_PRESS)
	//		{
	//			nextCtrl();
	//		}
	//	}
	//	break;
	//case eMC_CTRL_PREV:
	//	{
	//		if(msg.value == cMIDI_BTN_PRESS)
	//		{
	//			prevCtrl();
	//		}
	//	}
	//	break;
	case eMC_CTRL_TRIGGER:
		{
			if(msg.value == cMIDI_BTN_PRESS && _NowCtrl != "")
			{
				auto Iter_ = _BCMap.find(_NowCtrl);
				if(Iter_ != _BCMap.end())
				{
					Iter_->second->next();
				}
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

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::B1_BACKGROUND, true);
					_NowCtrl = NAME_MGR::B1_BACKGROUND;					
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);				
			}
		}
		break;
	case eMC_VIDEO_SET1:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B5_VIDEO_SET1];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{	
					sethighlight(NAME_MGR::B5_VIDEO_SET1, true);
					_NowCtrl = NAME_MGR::B5_VIDEO_SET1;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);		
			}
		}
		break;
	case eMC_VIDEO_SET2:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B6_VIDEO_SET2];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{	
					sethighlight(NAME_MGR::B6_VIDEO_SET2, true);
					_NowCtrl = NAME_MGR::B6_VIDEO_SET2;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);		
			}
		}
		break;
	case eMC_VIDEO_SET3:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B7_VIDEO_SET3];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{	
					sethighlight(NAME_MGR::B7_VIDEO_SET3, true);
					_NowCtrl = NAME_MGR::B7_VIDEO_SET3;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);		
			}
		}
		break;
	case eMC_ROTATE_TECT:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B2_ROTATE_RECT];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::B2_ROTATE_RECT, true);
					_NowCtrl = NAME_MGR::B2_ROTATE_RECT;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);		
			}
		}
		break;
	case eMC_OPEN:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B3_OPEN];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::B3_OPEN, true);
					_NowCtrl = NAME_MGR::B3_OPEN;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);		
			}
		}
		break;
	case eMC_NOISE:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::B4_NOISE];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::B4_NOISE, true);
					_NowCtrl = NAME_MGR::B4_NOISE;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);		
			}
		}
		break;
	case eMC_RAIN:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C1_RAIN];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::C1_RAIN, true);
					_NowCtrl = NAME_MGR::C1_RAIN;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_METABALL:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C2_METABALL];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::C2_METABALL, true);
					_NowCtrl = NAME_MGR::C2_METABALL;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_WAVE:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C3_WAVE];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::C3_WAVE, true);
					_NowCtrl = NAME_MGR::C3_WAVE;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_SNAKE:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C4_SNAKE];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::C4_SNAKE, true);
					_NowCtrl = NAME_MGR::C4_SNAKE;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_FIREWORK:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C5_FIREWORK];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::C5_FIREWORK, true);
					_NowCtrl = NAME_MGR::C5_FIREWORK;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_TEXT_BAR:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C6_TEXT_BAR];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::C6_TEXT_BAR, true);
					_NowCtrl = NAME_MGR::C6_TEXT_BAR;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_SCANNER_H:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C7_SCANNER_H];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::C7_SCANNER_H, true);
					_NowCtrl = NAME_MGR::C7_SCANNER_H;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_SCANNER_V:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::C8_SCANNER_V];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::C8_SCANNER_V, true);
					_NowCtrl = NAME_MGR::C8_SCANNER_V;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_WATERFALL:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::F1_WATERFALL];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::F1_WATERFALL, true);
					_NowCtrl = NAME_MGR::F1_WATERFALL;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_CROSS:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::F2_CROSS];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::F2_CROSS, true);
					_NowCtrl = NAME_MGR::F2_CROSS;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_SIMPLE_BLINK_W:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::F3_SIMPLE_BLINK_W];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::F3_SIMPLE_BLINK_W, true);
					_NowCtrl = NAME_MGR::F3_SIMPLE_BLINK_W;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_SIMPLE_BLINK_B:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::F4_SIMPLE_BLINK_B];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::F4_SIMPLE_BLINK_B, true);
					_NowCtrl = NAME_MGR::F4_SIMPLE_BLINK_B;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	case eMC_MYO_BLINK:
		{
			if(msg.value == cMIDI_BTN_PRESS)
			{
				auto& Toggle_ = _ToggleList[NAME_MGR::F5_MYO_COLOR_BLINK];
				Toggle_ = !Toggle_;

				sethighlight(_NowCtrl, false);
				if(Toggle_)
				{					
					sethighlight(NAME_MGR::F5_MYO_COLOR_BLINK, true);
					_NowCtrl = NAME_MGR::F5_MYO_COLOR_BLINK;
				}

				//set midi light
				_midiOut.sendControlChange(msg.channel, msg.control, Toggle_?127:0);	
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::resetMidiLED()
{
	_midiOut.sendControlChange(1, eMC_BACKGROUND, 0);	
	_midiOut.sendControlChange(1, eMC_ROTATE_TECT, 0);	
	_midiOut.sendControlChange(1, eMC_OPEN, 0);	
	_midiOut.sendControlChange(1, eMC_NOISE, 0);	
	_midiOut.sendControlChange(1, eMC_VIDEO_SET1, 0);	
	_midiOut.sendControlChange(1, eMC_VIDEO_SET2, 0);
	_midiOut.sendControlChange(1, eMC_VIDEO_SET3, 0);
	_midiOut.sendControlChange(1, eMC_RAIN, 0);	
	_midiOut.sendControlChange(1, eMC_TEXT_BAR, 0);	
	_midiOut.sendControlChange(1, eMC_WAVE, 0);	
	_midiOut.sendControlChange(1, eMC_SNAKE, 0);	
	_midiOut.sendControlChange(1, eMC_FIREWORK, 0);	
	_midiOut.sendControlChange(1, eMC_SCANNER_H, 0);	
	_midiOut.sendControlChange(1, eMC_SCANNER_V, 0);	
	_midiOut.sendControlChange(1, eMC_WATERFALL, 0);	
	_midiOut.sendControlChange(1, eMC_CROSS, 0);	
	_midiOut.sendControlChange(1, eMC_SIMPLE_BLINK_W, 0);	
	_midiOut.sendControlChange(1, eMC_SIMPLE_BLINK_B, 0);	
	_midiOut.sendControlChange(1, eMC_MYO_BLINK, 0);	
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
		int newBGM_	= MAX(MIN(Time2BPM(fDelta_), cMAX_BPM), cMIN_BPM);
		BPMChanged(newBGM_);

		//_BPMSlider = _iBPM;		
	}
}
#pragma endregion