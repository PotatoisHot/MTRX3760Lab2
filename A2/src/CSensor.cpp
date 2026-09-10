//-----------------------------------------------------------------------------
// CSensor.cpp
// See CSensor.h.
//-----------------------------------------------------------------------------

#include "CSensor.h"
#include <cmath>

//---Angles come in as degrees and are kept as radians.------------------------
static const float kDegreesToRadians = float( M_PI ) / 180.0f;

//-----------------------------------------------------------------------------
CSensor::CSensor( Vec2D aMountOffset, int aMountAngleDegrees )
    : mMountOffset( aMountOffset ),
      mMountAngle( float( aMountAngleDegrees ) * kDegreesToRadians )
{
}

//-----------------------------------------------------------------------------
CSensor::~CSensor()
{
}

//-----------------------------------------------------------------------------
// Rotate the mount offset by the heading, then add the robot's position.
//-----------------------------------------------------------------------------
Vec2D CSensor::GetSensorPosition( const CPose& aRobotPose ) const
{
    float Cos = std::cos( aRobotPose.mHeading );
    float Sin = std::sin( aRobotPose.mHeading );

    Vec2D World = { aRobotPose.mPosition.x + mMountOffset.x * Cos - mMountOffset.y * Sin,
                    aRobotPose.mPosition.y + mMountOffset.x * Sin + mMountOffset.y * Cos };

    return World;
}

//-----------------------------------------------------------------------------
float CSensor::GetSensorAngle( const CPose& aRobotPose ) const
{
    return aRobotPose.mHeading + mMountAngle;
}
