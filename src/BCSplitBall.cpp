#include "BCSplitBall.h"

#pragma region struct Split Ball
SplitBall::_stSplitBall(ofVec2f p, ofVec2f d, int num)
	:pos(p)
	,vel(d * ofRandom(200, 300))
	,canSplit(false)
	,firstTouch(true)
{
	//color.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	color.set(255, 0, 0);
	lifeT = cMAX_LIFT_TIME * pow(0.99, num);
	maxLiftT = lifeT;
}

//--------------------------------------------------------------
void SplitBall::update(float fDelta)
{
	if(lifeT <= 0.0)
	{
		return;
	}
	lifeT -= fDelta;

	color.r = (lifeT/maxLiftT) * 255;
	color.b = (1 - lifeT/maxLiftT) * 255;

	ofVec2f newPos_ = pos + vel * fDelta;
	bool isTouch = false;
	if(	newPos_.x < 0 + cBALL_SIZE)
	{
		newPos_.x = cBALL_SIZE;
		vel.x = -vel.x;
		isTouch = true;
	}
	else if( newPos_.x >= cCANVAS_WIDTH - cBALL_SIZE)
	{
		newPos_.x = cCANVAS_WIDTH - cBALL_SIZE;
		vel.x = -vel.x;
		isTouch = true;
	}
	
	if(newPos_.y < 0 + cBALL_SIZE)
	{
		newPos_.y = cBALL_SIZE;
		vel.y = -vel.y;
		isTouch = true;
	}
	else if(newPos_.y >= cCANVAS_HEIGHT - cBALL_SIZE)
	{
		newPos_.y = cCANVAS_HEIGHT - cBALL_SIZE;
		vel.y = -vel.y;
		isTouch = true;
	}

	canSplit = !firstTouch && isTouch;
	firstTouch = isTouch;

	pos.set(newPos_);

}

//--------------------------------------------------------------
void SplitBall::draw()
{
	ofPushMatrix();
	ofTranslate(pos);
	{
		ofPushStyle();
		ofFill();
		//ofSetColor(color, lifeT/maxLiftT * 255);
		ofSetColor(color);
		{
			ofCircle(0, 0, cBALL_SIZE);
		}
		ofPopStyle();
	}
	ofPopMatrix();
}


//--------------------------------------------------------------
bool SplitBall::getSplit()
{	
	bool bResult_ = canSplit && getAlive();
	canSplit = false;
	return bResult_;
}

//--------------------------------------------------------------
bool SplitBall::getAlive()
{
	return lifeT > 0;
}
#pragma endregion

#pragma region Ballon Split Ball
BCSplitBall::BCSplitBall()
	:BCBase(eBC_SPLIT_BALL)
{}

//--------------------------------------------------------------
void BCSplitBall::update(const float fDelta)
{
	if(!_bStart)
	{
		return;
	}

	list<SplitBall> newSplitBallList_;
	auto Iter_ = _SplitBallList.begin();
	while(Iter_ != _SplitBallList.end())
	{
		Iter_->update(fDelta);
		if(Iter_->getAlive())
		{
			if(Iter_->getSplit())
			{
				ofVec2f newDir_ = Iter_->vel.normalized().rotate(ofRandom(-5, 5));
				SplitBall newSplitBall_(Iter_->pos, newDir_, _SplitBallList.size());
				newSplitBallList_.push_back(newSplitBall_);
			}
			Iter_++;
		}
		else
		{
			Iter_ = _SplitBallList.erase(Iter_);
		}
	}

	_SplitBallList.splice(_SplitBallList.end(), newSplitBallList_);
}

//--------------------------------------------------------------
void BCSplitBall::draw()
{
	if(!_bStart)
	{
		return;
	}
	for(auto& Iter_ : _SplitBallList)
	{
		Iter_.draw();
	}
}

//--------------------------------------------------------------
void BCSplitBall::start()
{
	SplitBall newSplitBall_(
		//ofVec2f(ofRandom(0, cCANVAS_WIDTH), ofRandom(0, cCANVAS_HEIGHT)),
		ofVec2f(cCANVAS_WIDTH/2, cCANVAS_HEIGHT/2),
		ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)).normalized()
	);

	_SplitBallList.push_back(newSplitBall_);

	_bStart = true;

}

//--------------------------------------------------------------
void BCSplitBall::stop()
{
	_bStart = false;
	_SplitBallList.clear();
}

#pragma endregion
