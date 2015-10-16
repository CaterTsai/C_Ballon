#include "ledColor.h"

ofColor ledColorMap::getNearColor(const ofColor& c)
{
	float h_, s_, b_;
	c.getHsb(h_, s_, b_);

	int nearH_, nearS_, nearB_, nearG_, index_;

	ofColor nearColor_(0);
	
	if(s_ == 0.f)
	{
		//near gray
		index_ = static_cast<int>(b_ / cGRAY_INTERVAL);
		if(index_ >= cCOLOR_GRAY_NUM)
		{
			index_ = cCOLOR_GRAY_NUM - 1;
		}
		nearG_ = GRAYLEVEL_CODETABLE[index_];
		nearColor_.set(nearG_);
	}
	else
	{
		//near hue
		index_ = static_cast<int>(h_ / cHUE_INTERVAL);
		if(index_ >= cCOLOR_HUE_NUM - 1)
		{
			index_ = cCOLOR_HUE_NUM - 2;
		}
		nearH_ = HUE_CODETABLE[index_];

		//near saturation
		index_ = static_cast<int>(s_ / cSATURATION_INTERVAL);
		if(index_ >= cCOLOR_SATURATION_NUM)
		{
			index_ = cCOLOR_SATURATION_NUM - 1;
		}
		nearS_ = SATURATION_CODETABLE[index_];

		//near Light
		index_ = static_cast<int>(b_ / cLIGHT_INTERVAL);
		if(index_ >= cCOLOR_LIGHT_NUM)
		{
			index_ = cCOLOR_LIGHT_NUM - 1;
		}
		nearB_ = LIGHT_CODETABLE[index_];

		nearColor_.setHsb(nearH_, nearS_, nearB_);
	}
	return nearColor_;
}

//--------------------------------------------------------------
unsigned char ledColorMap::encode(const ofColor& c)
{
	float h_, s_, b_;
	c.getHsb(h_, s_, b_);

	int hcode_, scode_, bcode_, gcode_;
	unsigned char code_ ;

	if(s_ == 0.f)
	{
		//gray
		hcode_ = 15 << 4;

		//near gray
		gcode_ = static_cast<int>(b_ / cGRAY_INTERVAL);
		if(gcode_ >= cCOLOR_GRAY_NUM)
		{
			gcode_ = cCOLOR_GRAY_NUM - 1;
		}
		code_ = hcode_ + gcode_;
	}
	else
	{
		//hue code
		hcode_ = static_cast<int>(h_ / cHUE_INTERVAL);
		if(hcode_ >= cCOLOR_HUE_NUM - 1)
		{
			hcode_ = cCOLOR_HUE_NUM - 2;
		}

		//saturation code
		scode_ = static_cast<int>(s_ / cSATURATION_INTERVAL);
		if(scode_ >= cCOLOR_SATURATION_NUM)
		{
			scode_ = cCOLOR_SATURATION_NUM - 1;
		}

		//Light code
		bcode_ = static_cast<int>(b_ / cLIGHT_INTERVAL);
		if(bcode_ >= cCOLOR_LIGHT_NUM)
		{
			bcode_ = cCOLOR_LIGHT_NUM - 1;
		}

		hcode_ = hcode_  << 4;
		scode_ = scode_ << 2;
		code_ = hcode_ + scode_ + bcode_;
	}

	return code_;
}

//--------------------------------------------------------------
ofColor ledColorMap::decode(unsigned char code)
{
	int hcode_ = (int)((code & cHUE_MASK) >> 4);
	int scode_  = (int)((code & cSATURATION_MASK) >> 2);
	int bcode_ = (int)((code & cLIGHT_MASK));
	int gcode_ = (int)((code & cGRAY_MASK));

	ofColor decodeColor_;
	if(hcode_ == 15)
	{
		int g_ = GRAYLEVEL_CODETABLE[gcode_];
		decodeColor_.set(g_);
	}
	else
	{
		int h_ = HUE_CODETABLE[hcode_];
		int s_ = SATURATION_CODETABLE[scode_];
		int b_ = LIGHT_CODETABLE[bcode_];
	
		decodeColor_.setHsb(h_, s_, b_);
	}
	return decodeColor_;
}