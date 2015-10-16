#include "ColorSet.h"

//--------------------------------------------------------------
void ColorSet::setup()
{
	//Color set 1
	vector<ofColor> colorset1_;
	colorset1_.push_back(ofColor(47, 138, 138));
	colorset1_.push_back(ofColor(242, 202, 4));
	colorset1_.push_back(ofColor(216, 142, 4));
	colorset1_.push_back(ofColor(191, 53, 3));
	colorset1_.push_back(ofColor(114, 22, 2));

	_colorManager.push_back(colorset1_);

	_setIdx = 0;
}

//--------------------------------------------------------------
ofColor ColorSet::getRandomColor() const
{
	int size_ = _colorManager[_setIdx].size();
	return _colorManager[_setIdx][rand() % size_];
}

//--------------------------------------------------------------
ofColor ColorSet::getColor(int idx) const
{
	int returnId_ = 0;
	if(idx >= 0 && idx < _colorManager[_setIdx].size())
	{
		returnId_ = idx;
	}
	else
	{
		returnId_ = 0;
	}
	return _colorManager[_setIdx][returnId_];
}

//--------------------------------------------------------------
void ColorSet::changeColorSet(int idx)
{
	if(idx >= 0 && idx < _colorManager.size())
	{
		_setIdx  = idx;
	}
}

//--------------------------------------------------------------
ColorSet* ColorSet::_pInstance = nullptr;
ColorSet* ColorSet::GetInstance()
{
	if(_pInstance == nullptr)
	{
		_pInstance = new ColorSet();
	}
	return _pInstance;
}

//--------------------------------------------------------------
void ColorSet::Destory()
{
	if(_pInstance != nullptr)
	{
		delete _pInstance;
		_pInstance = nullptr;
	}
}