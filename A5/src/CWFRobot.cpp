//-----------------------------------------------------------------------------
// CWFRobot.cpp
// See CWFRobot.h.
//-----------------------------------------------------------------------------

#include "CWFRobot.h"
#include "CLoopReader.h"
#include "Helper.h"   // Clamp

//---When parallel to a wall the 45 degree ray reads root two times the 90.----
static const float kRootTwo = 1.41421356f;

//-----------------------------------------------------------------------------
CWFRobot::CWFRobot( const std::string& aName, const CLoopReader& aWalls, int aRadius, Color aTrailColor, Color aBodyColor )
    : CRobot( aName, aWalls, aWalls, aRadius, aTrailColor, aBodyColor ),   // senses the walls and can hit them
      mSensor90( 90 ),
      mSensor45( 45 ),
      mTargetWallDistance( float( aRadius + kWallMargin ) )
{
}

//-----------------------------------------------------------------------------
// Two-term steering. Both errors are signed so positive means turn right,
// toward the wall.
//-----------------------------------------------------------------------------
void CWFRobot::Update( float aTimeStep )
{
    const std::vector<Vec2D>& Walls = GetMap().GetVertices();

    float D90 = mSensor90.GetReading( GetPose(), Walls );
    float D45 = mSensor45.GetReading( GetPose(), Walls );

    // Too far from the wall is positive
    float DistanceError = D90 - mTargetWallDistance;

    // Angled away from the wall is positive. This is what stops the distance
    // term overshooting: it limits how steeply the robot can approach.
    float HeadingError = D45 - kRootTwo * D90;

    float TurnRate = kDistanceGain * DistanceError + kHeadingGain * HeadingError;

    // Near a corner a ray can slip past the wall end and read the far side of
    // the room. Cap the turn so the robot keeps rolling and drives out of it.
    TurnRate = Clamp( TurnRate, -kMaxTurnRate, kMaxTurnRate );

    Drive( float( kCruiseSpeed ), TurnRate, aTimeStep );
}
