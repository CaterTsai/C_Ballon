#include "MyoCtrl.h"

void MyoCtrl::setup()
{
	_pHub = new myo::Hub("com.artgital.testMyo");
	_pHub->addListener(this);
	_pMyo = _pHub->waitForMyo(1000);
	_bIsSetup = true;
}

//--------------------------------------------------------------
void MyoCtrl::update()
{
	if(!_bIsSetup)
	{
		return;
	}
	_pHub->run(1000/60);
}