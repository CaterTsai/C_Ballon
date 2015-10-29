#ifndef OFX_MYO_CTRL
#define OFX_MYO_CTRL

#include <myo/myo.hpp>
#include "ofMain.h"

using namespace myo;

#pragma region Myo
class MyoCtrl : public DeviceListener
{
public:
	MyoCtrl()
		:_bIsSetup(false)
		,_bArm(false)
		,_bFist(false)
		,_bOpen(false)
		,_pHub(nullptr)
		,_EularShift(0)
	{}

	~MyoCtrl()
	{	
		_pMyo->lock();
		delete _pHub;
	}

	void setup();
	void update();

private:
	bool	_bIsSetup;
	Myo*	_pMyo;
	Hub*	_pHub;

public:
	inline void resetEulat()
	{
		_EularShift = _Eular;
	}
	inline ofVec3f getAcc() const
	{
		return _Acc;
	}

	inline ofVec3f getGyros() const
	{
		return _Gyros;
	}

	inline ofVec3f getEular() const
	{
		return _Eular - _EularShift;
	}

	inline bool getFist() const
	{
		return _bFist;
	}

	inline bool getOpen() const
	{
		return _bOpen;
	}

	inline bool isLeft() const
	{
		return _whichArm == Arm::armLeft;
	}

private:
	bool _bArm;
    myo::Arm _whichArm;
	myo::Pose	_Pose;
	bool	_bFist, _bOpen;
	ofVec3f _Acc, _Gyros, _Eular;
	ofVec3f _EularShift;
//--------------------------------------------------------------
#pragma region Myo callback
public:
	void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
    {
		ofQuaternion Q_(quat.x(), quat.y(), quat.z(), quat.w());
		_Eular = Q_.getEuler();
		
		//_fRoll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
  //                         1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y())) * RAD_TO_DEG;
  //      _fPitch = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x())))) * RAD_TO_DEG;
  //      _fYaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
  //                      1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z())) * RAD_TO_DEG;
    }

	//--------------------------------------------------------------
	void onPose(Myo* myo, uint64_t timestamp, Pose pose)
	{
		_bFist = (pose == Pose::fist);
		_bOpen = (pose == Pose::fingersSpread);
	}

	//--------------------------------------------------------------
	void onAccelerometerData(Myo* myo, uint64_t timestamp, const Vector3<float>& accel)
	{
		_Acc.set(accel.x(), accel.y(), accel.z());
	}

	//--------------------------------------------------------------
	void onGyroscopeData(Myo* myo, uint64_t timestamp, const Vector3<float>& gyro)
	{
		_Gyros.set(gyro.x(), gyro.y(), gyro.z());
	}

	//--------------------------------------------------------------
	void onConnect(Myo* myo, uint64_t timestamp, FirmwareVersion firmwareVersion)
	{	
		_bIsSetup &= true;
		myo->unlock(myo::Myo::unlockHold);			
	}

	//--------------------------------------------------------------
    void onArmSync(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection, float rotation,
                   myo::WarmupState warmupState)
    {
        _bArm = true;
        _whichArm = arm;
    }

	//--------------------------------------------------------------
    void onArmUnsync(myo::Myo* myo, uint64_t timestamp)
    {
        _bArm = false;
    }

#pragma endregion


#pragma endregion

};

#endif // !OFX_MYO_CTRL
