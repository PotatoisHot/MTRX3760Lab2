
#include "CWFRobot.h"

//---When parallel to a wall, the 45 degree ray reads root two times the 90.---
static const float kRootTwo = 1.41421356f;

//-----------------------------------------------------------------------------
CWFRobot::CWFRobot( const std::string& aName, const CPose& aStartPose, int aRadius )
    : CRobot( aName, aStartPose, aRadius ),
      mSensor90( 90 ),
      mSensor45( 45 ),
      mTargetWallDistance( float( aRadius + kWallMargin ) )
{
}

//-----------------------------------------------------------------------------
// Two-term steering. Both errors are signed so that positive means "turn
// right, toward the wall", which is a positive turn rate on screen.
//-----------------------------------------------------------------------------
void CWFRobot::Update( float aTimeStep, const std::vector<Vec2D>& aWalls )
{
    float D90 = mSensor90.GetReading( GetPose(), aWalls );
    float D45 = mSensor45.GetReading( GetPose(), aWalls );

    // Too far from the wall is positive.
    float DistanceError = D90 - mTargetWallDistance;

    // Angled away from the wall is positive. This is what stops the distance
    // term from overshooting: it limits how steeply the robot may approach.
    float HeadingError = D45 - kRootTwo * D90;

    float TurnRate = kDistanceGain * DistanceError + kHeadingGain * HeadingError;

    // Near a corner one ray can slip past the wall end and read the far side
    // of the room, which asks for a wild turn. Cap it so the robot keeps
    // rolling forward and drives itself out of the situation.
    if ( TurnRate > kMaxTurnRate )
    {
        TurnRate = kMaxTurnRate;
    }
    else if ( TurnRate < -kMaxTurnRate )
    {
        TurnRate = -kMaxTurnRate;
    }

    Drive( float( kCruiseSpeed ), TurnRate, aTimeStep );
}
