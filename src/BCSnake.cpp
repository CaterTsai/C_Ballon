#include "BCSnake.h"

#pragma region Snake
//--------------------------------------------------------------
Snake::Snake(int maxTurn, ofColor color, ofVec2f StartPos, ofVec2f Velocity)
	:_isDie(false)
	,_CanDie(false)
	,_timer(ofRandom(0.2, 0.5))
	,_iTurnNum(0)
	,_maxTurn(maxTurn)
	,_Vel(Velocity)
	,_color(color)
	,_length(ofRandom(cCANVAS_HEIGHT, cCANVAS_WIDTH))
{
	
	_posList.push_front(StartPos);
	ofVec2f TailPos_ = StartPos;
	if(_Vel.x > 0 && _Vel.y == 0)
	{
		//Left
		TailPos_.x -= _length;
	}
	else if(_Vel.x < 0 && _Vel.y == 0)
	{
		//Right
		TailPos_.x += _length;
	}
	else if(_Vel.y > 0 && _Vel.x == 0)
	{
		//Top
		TailPos_.y -= _length;
	}
	else if(_Vel.y < 0 && _Vel.x == 0)
	{
		//Down
		TailPos_.y += _length;
	}
	_posList.push_front(TailPos_);
	_moveLength = _Vel.length();
}

//--------------------------------------------------------------
void Snake::update(float fDelta)
{
	if(_isDie)
	{
		return;
	}

	if(_iTurnNum < _maxTurn)
	{
		_timer -= fDelta;
		if(_timer <= 0.0)
		{
			turn();
			_timer = ofRandom(0.2, 0.5);
		}
	}

	//Update Position
	_posList.back() += _Vel * fDelta;

	if(_posList.size() > 2)
	{
		auto endposIter_ = _posList.begin();
		auto nextposIter_ = endposIter_;
		nextposIter_++;
		ofVec2f endpos_ = *endposIter_;
		ofVec2f nextpos_ = *nextposIter_;

		auto TailVel_ = (nextpos_ - endpos_).normalized() * _moveLength;
		(endpos_) += TailVel_ * fDelta;

		if(endpos_.distance(nextpos_) < _moveLength * 0.03)
		{
			endpos_ = nextpos_;
			_posList.erase(endposIter_);
		}
		(*_posList.begin()) = endpos_;
	}
	else
	{
		(*_posList.begin()) += _Vel * fDelta;
	}
	
	if(!_CanDie)
	{
		auto endpos_ = (*_posList.begin());
		if(endpos_.x >= 0 && endpos_.x < cCANVAS_WIDTH && endpos_.y >= 0 && endpos_.y < cCANVAS_HEIGHT)
		{
			_CanDie = true;
		}
	}
	else
	{
		auto endpos_ = (*_posList.begin());
		if(endpos_.x < 0 || endpos_.x >= cCANVAS_WIDTH || endpos_.y < 0 || endpos_.y >= cCANVAS_HEIGHT)
		{
			_isDie = true;
		}
	}
}

//--------------------------------------------------------------
void Snake::draw()
{
	if(_isDie)
	{
		return;
	}

	ofPushStyle();
	ofSetColor(_color);
	{
		auto Iter_ = _posList.begin();
		Iter_++;
		for( ;Iter_ != _posList.end() ; ++Iter_)
		{
			auto before_ = Iter_;
			before_--;
			
			ofLine(*Iter_, *before_);
		}		
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void Snake::turn()
{
	if(_Vel.x == 0)
	{
		//Top or Down
		_Vel.x = _Vel.y; 
		_Vel.y = 0;
		_Vel.x *= ofRandom(1, 1) > 0 ? -1 : 1;
	}
	else
	{
		//Left or Right
		_Vel.y = _Vel.x; 
		_Vel.x = 0;
		_Vel.y *= ofRandom(1, 1) > 0 ? -1 : 1;
	}
	_iTurnNum++;
	auto insertiter_ = _posList.end();
	insertiter_--;
	_posList.insert(insertiter_, _posList.back());
}
#pragma endregion

#pragma region BCSnake
BCSnake::BCSnake()
	:BCBase(eBC_SNAKE)
	,_fTimer(0.0)
{}

//--------------------------------------------------------------
void BCSnake::update(const float fDelta)
{
	auto Iter_ = _SnakeMgr.begin();
	while(Iter_ != _SnakeMgr.end())
	{
		Iter_->update(fDelta);

		if(Iter_->isDie())
		{
			Iter_ = _SnakeMgr.erase(Iter_);
		}
		else
		{
			Iter_++;
		}
	}

	if(_bStart)
	{
		_fTimer -= fDelta;
		if(_fTimer <= 0.0)
		{
			addSnake();
			_fTimer = _fDuratcion;
		}
	}
}

//--------------------------------------------------------------
void BCSnake::draw()
{
	ofPushStyle();
	ofSetLineWidth(cSNAKE_WIDTH);
	{
		for(auto& Iter_ : _SnakeMgr)
		{
			Iter_.draw();
		}
	}	
	ofPopStyle();
}

//--------------------------------------------------------------
void BCSnake::start()
{
	_fTimer = getTriggerTime();
	_bStart = true;
	addSnake();
}

//--------------------------------------------------------------
void BCSnake::stop()
{
	_SnakeMgr.clear();
	_bStart = false;
}

//--------------------------------------------------------------
float BCSnake::getTriggerTime()
{
	return _fDuratcion;
}

//--------------------------------------------------------------
void BCSnake::addSnake()
{
	int maxTurn_ = static_cast<int>(ofRandom(1, 5) + 0.5);
	ofVec2f startPos_(0), vel_(0);
	float fSpeed_ = cCANVAS_WIDTH / (getTriggerTime() * 4.0);
	if(ofRandom(-1, 1) > 0)
	{
		startPos_.x = ofRandom(0, cCANVAS_WIDTH);
		vel_.x = 0;
		if(ofRandom(-1, 1) > 0)
		{
			startPos_.y = 0;
			vel_.y = fSpeed_;
		}
		else
		{
			startPos_.y = cCANVAS_HEIGHT;
			vel_.y = -fSpeed_;
		}
	}
	else
	{
		startPos_.y = ofRandom(0, cCANVAS_HEIGHT);
		vel_.y = 0;
		if(ofRandom(-1, 1) > 0)
		{
			startPos_.x = 0;
			vel_.x = fSpeed_;
		}
		else
		{
			startPos_.x = cCANVAS_WIDTH;
			vel_.x = -fSpeed_;
		}
	}

	ofColor color_(0, 255, 64);
	Snake newSnake_(maxTurn_, color_, startPos_, vel_);
	_SnakeMgr.push_back(newSnake_);
}
#pragma endregion
