#ifndef OFX_BALLON_CANVAS_METABALL
#define OFX_BALLON_CANVAS_METABALL

#include "BCBase.h"
#include "BallGroup.h"

class BCMetaball : public BCBase
{
public:
	BCMetaball();

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void setBaseColor(ofColor c) override;
private:	
	//Metaball
	BallGroup			ball_group;
};

#endif //OFX_BALLON_CANVAS_METABALL