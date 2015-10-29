#include "BCTextBar.h"

BCTextBar::BCTextBar()
	:BCBase(eBC_TEXTBAR, eG_OBJECT)
	,_EndX(0)
	,_PosX(0)
	,_VecX(0)
{
	_font.loadFont("bold.otf", cTEXT_FONT_SIZE);
	loadText();
	_iDisplayIdx = 0;


	_StartTextPos.set(cCANVAS_WIDTH, cCANVAS_HEIGHT/2 + cTEXT_FONT_SIZE/2);
}

//--------------------------------------------------------------
void BCTextBar::update(const float fDelta)
{
	if(!_bStart)
	{
		return;
	}

	_PosX += fDelta *_VecX;
	if(_PosX < _EndX)
	{
		_PosX = _StartTextPos.x;
	}

	//Update Vec
	_VecX = (_EndX -  _StartTextPos.x) / getTriggerTime();
}

//--------------------------------------------------------------
void BCTextBar::draw()
{
	ofPushStyle();
	ofSetColor(_baseColor);
	{
		_font.drawString(_DisplayText[_iDisplayIdx], _PosX, _StartTextPos.y);
	}		
	ofPopStyle();
}

//--------------------------------------------------------------
void BCTextBar::start()
{
	_bStart = true;
	initialText(0);
}

//--------------------------------------------------------------
void BCTextBar::stop()
{
	_bStart = false;

}

//--------------------------------------------------------------
void BCTextBar::next()
{
	initialText(_iDisplayIdx + 1);
}

//--------------------------------------------------------------
void BCTextBar::setBaseColor(ofColor c)
{
	_baseColor = c;
	_baseColor.setHueAngle(c.getHueAngle() + 180 + ofRandom(-30, 30));
	_baseColor.setSaturation(ofRandom(200, 255));
}

//--------------------------------------------------------------
float BCTextBar::getTriggerTime()
{
	return _fDuratcion * 16;
}

//--------------------------------------------------------------
void BCTextBar::loadText()
{
	ofxXmlSettings	xml_;
	if(!xml_.loadFile("TextBar.xml"))
	{
		ofLog(OF_LOG_WARNING, "[BCTextBar]Loading text xml failed");
		_DisplayText.push_back("HELLO");
		_DisplayText.push_back("CATER");
		_DisplayText.push_back("HI HI HI");

	}
	else
	{
		auto num_ = xml_.getNumTags("TEXT");
		for(int idx_ = 0; idx_ < num_; idx_++)
		{
			_DisplayText.push_back(xml_.getValue("TEXT", "", idx_));
		}
	}
}

//--------------------------------------------------------------
void BCTextBar::initialText(int idx)
{
	_iDisplayIdx = idx;
	if(_iDisplayIdx >= _DisplayText.size())
	{
		_iDisplayIdx = 0; 
	}

	float fDist_ = _font.getStringBoundingBox(_DisplayText[_iDisplayIdx], 0, 0).width + cCANVAS_WIDTH;
	_VecX = -(fDist_ / getTriggerTime());
	_EndX = _StartTextPos.x - fDist_;
	_PosX = _StartTextPos.x;
	
}