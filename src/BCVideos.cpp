#include "BCVideos.h"

BCVideos::BCVideos(string VideoFolder)
	:BCBase(eBC_VIDEO, eG_BACKGROUND)
	,_VideoIdx(0)
{
	ofDirectory	dir_(VideoFolder);
	dir_.allowExt("mov");
	int iNum_ = dir_.listDir();

	_VideoList.resize(iNum_);

	for(int idx_ = 0; idx_ < iNum_; ++idx_)
	{
		string videoPath_ = VideoFolder + dir_.getName(idx_);

		_VideoList[idx_].setPlayer(ofPtr<ofxHapPlayer>(new ofxHapPlayer));
		_VideoList[idx_].setLoopState(ofLoopType::OF_LOOP_NORMAL);
		
		_VideoList[idx_].loadMovie(videoPath_);
		_VideoList[idx_].setVolume(0);
	}
}

//--------------------------------------------------------------
void BCVideos::update(const float fDelta)
{
	if(!_bStart)
	{
		return;
	}

	_VideoList[_VideoIdx].update();
}

//--------------------------------------------------------------
void BCVideos::draw()
{
	ofPushStyle();
	{
		ofSetColor(255);
		if(_VideoList[_VideoIdx].isPlaying())
		{
			_VideoList[_VideoIdx].draw(0, 0, cCANVAS_WIDTH, cCANVAS_HEIGHT);
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void BCVideos::start()
{
	if(_VideoList.size() == 0)
	{
		return;
	}
	_VideoIdx = 0;
	_VideoList[0].play();
	_bStart = true;
}

//--------------------------------------------------------------
void BCVideos::stop()
{
	for(auto& Iter_ : _VideoList)
	{
		Iter_.stop();
	}
	_bStart = false;
}

//--------------------------------------------------------------
void BCVideos::next()
{
	_VideoList[_VideoIdx].stop();

	_VideoIdx++;
	_VideoIdx %= _VideoList.size();

	_VideoList[_VideoIdx].play();
}