//-----------------------------------------------------------------------------
// CWallSensor.cpp
// See CWallSensor.h.
//-----------------------------------------------------------------------------

#include "CWallSensor.h"
#include <cmath>

//-----------------------------------------------------------------------------
CWallSensor::CWallSensor( int aAngleDegrees )
    : CSensor( Vec2D{ 0.0f, 0.0f }, aAngleDegrees )   // at the centre
{
}

//-----------------------------------------------------------------------------
// Test every wall and keep the nearest hit, so a near wall hides a far one.
//-----------------------------------------------------------------------------
float CWallSensor::GetReading( const CPose& aRobotPose, const std::vector<Vec2D>& aWalls ) const
{
    Vec2D RayOrigin    = GetSensorPosition( aRobotPose );
    float RayAngle     = GetSensorAngle( aRobotPose );
    Vec2D RayDirection = { std::cos( RayAngle ), std::sin( RayAngle ) };

    float Nearest  = float( kMaxRange );
    int   NumWalls = int( aWalls.size() );

    for ( int i = 0; i < NumWalls; i++ )
    {
        const Vec2D& WallStart = aWalls[i];
        const Vec2D& WallEnd   = aWalls[( i + 1 ) % NumWalls];   // last joins back to first
        Vec2D WallVector = { WallEnd.x - WallStart.x, WallEnd.y - WallStart.y };

        CRayHit Hit = RayHitsWall2D( RayOrigin, RayDirection, WallStart, WallVector );

        if ( Hit.mHit && Hit.mDistance < Nearest )
        {
            Nearest = Hit.mDistance;
        }
    }

    return Nearest;
}
