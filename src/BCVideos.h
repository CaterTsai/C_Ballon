#ifndef OFX_BALLON_CANVAS_VIDEOS
#define OFX_BALLON_CANVAS_VIDEOS

#include "BCBase.h"
#include "ofxHapPlayer.h"

class BCVideos : public BCBase
{
public:
	BCVideos(string VideoFolder);

	void update(const float fDelta) override;
	void draw() override;
	void start() override;
	void stop() override;
	void next() override;
private:
	int						_VideoIdx;
	vector<ofVideoPlayer>	_VideoList;
};

#endif // !OFX_BALLON_CANVAS_VIDEOS
