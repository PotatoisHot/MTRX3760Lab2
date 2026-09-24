//-----------------------------------------------------------------------------
// CLFRobot.cpp
// See CLFRobot.h.
//-----------------------------------------------------------------------------

#include "CLFRobot.h"
#include "CLoopReader.h"
#include <cmath>

//---Angles come in as degrees and are kept as radians.------------------------
static const float kDegreesToRadians = float( M_PI ) / 180.0f;

//-----------------------------------------------------------------------------
// Offsets are from the centre in the robot's own frame, x forward and y right.
// CSensor turns them with the robot, so the start pose plays no part here.
//-----------------------------------------------------------------------------
CLFRobot::CLFRobot( const std::string& aName, const CLoopReader& aLine, const CLoopReader& aRoom,
                    int aRadius, Color aTrailColor, Color aBodyColor )
    : CRobot( aName, aLine, aRoom, aRadius, aTrailColor, aBodyColor ),
      mCentreSensor( Vec2D{ float( aRadius ), 0.0f } ),
      mRightSensor(  Vec2D{ float( aRadius ) * std::cos( kRightSensorAngle * kDegreesToRadians ),
                            float( aRadius ) * std::sin( kRightSensorAngle * kDegreesToRadians ) } )
{
}

//-----------------------------------------------------------------------------
// Two bits in, one turn rate out. Whichever sensor changed says which way the
// line has moved under the robot.
//
//   centre  right   action
//     Yes      No     straight
//     Yes      Yes     turn right, gently
//     No       Yes     turn right, hard
//     No       No     turn left
//-----------------------------------------------------------------------------
void CLFRobot::Update( float aTimeStep )
{
    const std::vector<Vec2D>& Line = GetMap().GetVertices();

    bool CentreOnLine = mCentreSensor.IsOverLine( GetPose(), Line );
    bool RightOnLine  = mRightSensor.IsOverLine( GetPose(), Line );

    float TurnRate = 0.0f;

    if ( CentreOnLine && !RightOnLine )
    {
        TurnRate = 0.0f;
    }
    else if ( CentreOnLine && RightOnLine )
    {
        TurnRate = kGentleTurn;
    }
    else if ( !CentreOnLine && RightOnLine )
    {
        TurnRate = kHardTurn;
    }
    else
    {
        TurnRate = -kHardTurn;
    }

    Drive( float( kCruiseSpeed ), TurnRate, aTimeStep );
}
