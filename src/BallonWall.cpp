#include "BallonWall.h"

#pragma region Basic function
BallonWall::~BallonWall()
{
	releaseBA();
}

//--------------------------------------------------------------
void BallonWall::setup()
{
	initialBA();
	initialCanvas();	
	initialConvert();
	initialBallon();

	if(cUSE_LED_CTRL)
	{
		_LedCtrl.setup();
	}	
}

//--------------------------------------------------------------
void BallonWall::update(float fDelta)
{	
	switch(_eWallType)
	{
	case eBALLON_ACCESS:
		{
			_BAMap[_BAType]->update(fDelta, _BallonList);
		}
		break;
	case eBALLON_CANVAS:
		{
			convert();
		}
		break;
	case eBALLON_FIXED:
		{
		}
		break;
	}
	
	if(cUSE_LED_CTRL)
	{
		_LedCtrl.update();
	}
}

//--------------------------------------------------------------
void BallonWall::draw(int x, int y)
{
	ofPushMatrix();
	ofTranslate(ofVec2f(x, y));
	{
		drawBallon();

		//Debug
		if(_bShowRange)
		{
			ofPushStyle();
			{
				ofSetColor(255, 255, 0);
				ofSetLineWidth(3);
				ofNoFill();

				ofRect(0, 0, cWALL_WIDTH, cWALL_HEIGHT);
			}
			ofPopStyle();
		}
	}
	ofPopMatrix();


	if(cUSE_LED_CTRL)
	{
		_LedCtrl.setColor(_PixelList);
	}
}

//--------------------------------------------------------------
void BallonWall::setWallType(eBALLON_WALL_TYPE eType)
{
	if(_eWallType == eBALLON_ACCESS)
	{
		_BAMap[_BAType]->stop();
	}

	_eWallType = eType;
}

#pragma endregion

#pragma region Ballon
//--------------------------------------------------------------
void BallonWall::clearBallon()
{
	//Draw Ballon
	for(auto& Iter_ : _BallonList)
	{
		Iter_.setColor(ofColor(0));
	}
}
//--------------------------------------------------------------
void BallonWall::initialBallon()
{
	float fInvW_ = (cWALL_WIDTH - (cBALLON_R * cCOL_NUM * 2)) / (cCOL_NUM + 1);
	float fInvH_ = (cWALL_HEIGHT - (cBALLON_R * cROW_NUM * 2)) / (cROW_NUM + 1);

	float fOddX_ = fInvW_ + cBALLON_R;
	float fEvenX_ = fOddX_ + cBALLON_R + fInvW_/2;
	float fY_ = fInvH_ + cBALLON_R;

	fInvW_ += cBALLON_R * 2;
	fInvH_ += cBALLON_R * 2;

	//Method 1 Cube
	if(cBALL_TYPE == 0)
	{
		for(int y = 0; y < cROW_NUM; y++)
		{
			for(int x = 0; x < cCOL_NUM; x++)
			{
				Ballon newBallon_(ofVec2f(fOddX_ + x * fInvW_, fY_ + y * fInvW_));
				_BallonList.push_back(newBallon_);
			}
		}
	}

	//Method 2
	else {
		for(int y = 0; y < cROW_NUM; y++)
		{
			float fDrawX_;
			int iColNum_;
			if((y + 1) % 2 == 0)
			{
				//Even
				fDrawX_ = fEvenX_;
				iColNum_ = cCOL_NUM - 1;
			}
			else
			{
				//Odd
				fDrawX_ = fOddX_;
				iColNum_ = cCOL_NUM;
			}
		
			for(int x = 0; x < iColNum_; x++)
			{
				Ballon newBallon_(ofVec2f(fDrawX_ + x * fInvW_, fY_ + y * fInvW_));
				_BallonList.push_back(newBallon_);
			}
		}
	}	
}


//--------------------------------------------------------------
void BallonWall::drawBallon()
{
	//Draw Ballon
	for(auto& Iter_ : _BallonList)
	{
		Iter_.draw();
	}
}
#pragma endregion

#pragma region Ballon Access
//--------------------------------------------------------------
void BallonWall::startBA()
{
	clearBallon();
	_BAMap[_BAType]->start();
}

//--------------------------------------------------------------
void BallonWall::initialBA()
{	
	BABase*	pBAOpenH_ = new BAOpenH();
	pBAOpenH_->setIntervalTime(0.05);
	_BAMap.insert(make_pair(eBA_OPEN_H, pBAOpenH_));
}

//--------------------------------------------------------------
void BallonWall::releaseBA()
{
	for(auto& Iter_ : _BAMap)
	{
		delete Iter_.second;
	}

	_BAMap.clear();
}
#pragma endregion

#pragma region Canvas
//--------------------------------------------------------------
void BallonWall::beginCanvas()
{
	if(_Canvas.isAllocated())
	{
		_Canvas.begin();		
	}
}

//--------------------------------------------------------------
void BallonWall::endCanvas()
{
	if(_Canvas.isAllocated())
	{
		_Canvas.end();
	}
}

//--------------------------------------------------------------
void BallonWall::drawCanvas()
{
	if(_Canvas.isAllocated())
	{
		_Canvas.draw(0, 0);
	}
}

//--------------------------------------------------------------
void BallonWall::initialCanvas()
{
	_Canvas.allocate(cCANVAS_WIDTH, cCANVAS_HEIGHT, GL_RGB);
	_SmellCanvas.allocate(cCOL_NUM*2, cROW_NUM*2, GL_RGB);

}
#pragma endregion

#pragma region Convert
//--------------------------------------------------------------
void BallonWall::initialConvert()
{
	_PixelList.resize(cROW_NUM * cCOL_NUM);

	//Initial Pixel to Bollen map
	if(cBALL_TYPE == 0)
	{
		for(int y = 0; y < cROW_NUM; y++)
		{
			for(int x = 0; x < cCOL_NUM; x++)
			{
				int iPindex_ = y * cCOL_NUM + x;
				vector<int> M2Bindex_;
				M2Bindex_.push_back(iPindex_);
				//Insert
				_Canvas2Ballon.insert(make_pair(iPindex_, M2Bindex_));
			}
		}
	}
	else
	{
		int iNumOfEven_ = 0;
		for(int y = 0; y < cROW_NUM; y++)
		{
			if((y + 1) % 2 == 0)
			{
				iNumOfEven_++;
			}

			for(int x = 0; x < cCOL_NUM; x++)
			{
				int iPindex_ = y * cCOL_NUM + x;
				vector<int> M2Bindex_;
				if((y + 1) % 2 != 0)
				{
					//Odd
					M2Bindex_.push_back(iPindex_ - iNumOfEven_);
				}
				else
				{
					//Even
					int value1_ = iPindex_ - iNumOfEven_;
					int value2_ = iPindex_ - iNumOfEven_ + 1;

					if((iPindex_) % cCOL_NUM != 0)
					{
						M2Bindex_.push_back(value1_);
					}

					if((iPindex_ + 1) % cCOL_NUM != 0)
					{
						M2Bindex_.push_back(value2_);
					}
				}

				//Insert
				_Canvas2Ballon.insert(make_pair(iPindex_, M2Bindex_));
			}
		}
	}
}

//--------------------------------------------------------------
void BallonWall::convert()
{
	//Canvas to Smell Canvass	
	_SmellCanvas.begin();
	{
		ofClear(0);
		_Canvas.draw(0, 0, cCOL_NUM, cROW_NUM);

	}
	_SmellCanvas.end();
	
	ofPixels CanvasPixel_;
	_SmellCanvas.readToPixels(CanvasPixel_);
	for(int y = 0; y < cROW_NUM; y++)
	{
		for(int x = 0; x < cCOL_NUM; x++)
		{
			ofColor c_ = CanvasPixel_.getColor(x, y);
			int iIndex_ = y * cCOL_NUM + x;

			//Set Ballon Color
			auto BallonList_ = _Canvas2Ballon[iIndex_];
			for(auto& BIter_ : BallonList_)
			{
				_BallonList[BIter_].setColor(c_);
			}

			if(cUSE_LED_CTRL)
			{
				//Set Pixel
				_PixelList[iIndex_].set(c_);
			}
		}
	}
}
#pragma endregion
