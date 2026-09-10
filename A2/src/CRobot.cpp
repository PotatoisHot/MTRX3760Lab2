//-----------------------------------------------------------------------------
// CRobot.cpp
// See CRobot.h.
//-----------------------------------------------------------------------------

#include "CRobot.h"
#include "CLoopReader.h"
#include <cmath>

//-----------------------------------------------------------------------------
CRobot::CRobot( const std::string& aName, const CLoopReader& aMap, int aRadius, Color aTrailColor, Color aBodyColor )
    : mName( aName ),
      mRadius( aRadius ),
      mMap( aMap ),
      mStartPose( aMap.GetStartPose() ),
      mPose( aMap.GetStartPose() ),
      mLeftMotor( "Left motor" ),
      mRightMotor( "Right motor" ),
      mTrailColor( aTrailColor ),
      mBodyColor( aBodyColor )
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
const CLoopReader& CRobot::GetMap() const
{
    return mMap;
}

//-----------------------------------------------------------------------------
const Color& CRobot::GetTrailColor() const
{
    return mTrailColor;
}

//-----------------------------------------------------------------------------
const Color& CRobot::GetBodyColor() const
{
    return mBodyColor;
}

//-----------------------------------------------------------------------------
// Differential drive. Wheels sit on the rim either side, so the wheel base is
// the diameter and turn rate = ( left - right ) / wheel base. With y down and
// headings clockwise, a faster left wheel turns the robot right.
//-----------------------------------------------------------------------------
void CRobot::Drive( float aSpeed, float aTurnRate, float aTimeStep )
{
    float WheelBase      = 2.0f * float( mRadius );
    float HalfDifference = aTurnRate * WheelBase / 2.0f;

    mLeftMotor.SetSpeed(  int( aSpeed + HalfDifference ) );
    mRightMotor.SetSpeed( int( aSpeed - HalfDifference ) );

    // Use what the motors actually did after clamping, not what was asked
    float LeftSpeed  = float( mLeftMotor.GetSpeed() );
    float RightSpeed = float( mRightMotor.GetSpeed() );
    float Speed      = ( LeftSpeed + RightSpeed ) / 2.0f;
    float TurnRate   = ( LeftSpeed - RightSpeed ) / WheelBase;

    // Step along the heading at the middle of the update, so arcs stay arcs
    float MidHeading = mPose.mHeading + TurnRate * aTimeStep / 2.0f;

    mTrail.push_back( mPose.mPosition );
    mPose.mPosition.x += Speed * std::cos( MidHeading ) * aTimeStep;
    mPose.mPosition.y += Speed * std::sin( MidHeading ) * aTimeStep;
    mPose.mHeading    += TurnRate * aTimeStep;
}
