#include "CRobot.h"
#include <cmath>

//-----------------------------------------------------------------------------
CRobot::CRobot( const std::string& aName, const CPose& aStartPose, int aRadius )
    : mName( aName ),
      mRadius( aRadius ),
      mStartPose( aStartPose ),
      mPose( aStartPose ),
      mLeftMotor( "Left motor" ),
      mRightMotor( "Right motor" )
{
}

//-----------------------------------------------------------------------------
CRobot::~CRobot()
{
}

//-----------------------------------------------------------------------------
const std::string& CRobot::GetName() const
{
    return mName;
}

//-----------------------------------------------------------------------------
int CRobot::GetRadius() const
{
    return mRadius;
}

//-----------------------------------------------------------------------------
const CPose& CRobot::GetStartPose() const
{
    return mStartPose;
}

//-----------------------------------------------------------------------------
const CPose& CRobot::GetPose() const
{
    return mPose;
}


//-----------------------------------------------------------------------------
const std::vector<Vec2D>& CRobot::GetTrail() const
{
    return mTrail;
}

//-----------------------------------------------------------------------------
// Differential drive. The wheels sit at the rim, one either side, so the
// wheel base is the diameter. The turn rate comes from the difference in
// wheel speeds:  turn = ( left - right ) / wheel base.
//
// With y down and headings measured clockwise, a faster LEFT wheel turns the
// robot clockwise, so left gets the positive half of the difference.
//-----------------------------------------------------------------------------
void CRobot::Drive( float aSpeed, float aTurnRate, float aTimeStep )
{
    float WheelBase      = 2.0f * float( mRadius );
    float HalfDifference = aTurnRate * WheelBase / 2.0f;

    mLeftMotor.SetSpeed(  int( aSpeed + HalfDifference ) );
    mRightMotor.SetSpeed( int( aSpeed - HalfDifference ) );

    // Move by what the motors actually did after clamping, not what was asked.
    float LeftSpeed  = float( mLeftMotor.GetSpeed() );
    float RightSpeed = float( mRightMotor.GetSpeed() );
    float Speed      = ( LeftSpeed + RightSpeed ) / 2.0f;
    float TurnRate   = ( LeftSpeed - RightSpeed ) / WheelBase;

    // Midpoint integration: step along the heading at the middle of the
    // update rather than the start, so arcs do not spiral outward.
    float MidHeading = mPose.mHeading + TurnRate * aTimeStep / 2.0f;

    mTrail.push_back( mPose.mPosition );   // log the old position before moving
    mPose.mPosition.x += Speed * std::cos( MidHeading ) * aTimeStep;
    mPose.mPosition.y += Speed * std::sin( MidHeading ) * aTimeStep;
    mPose.mHeading    += TurnRate * aTimeStep;
}
