#include "CSensor.h"
#include <cmath>

//---Degrees given to the constructor are stored as radians.--------------------
static const float kDegreesToRadians = float( M_PI ) / 180.0f;

//-----------------------------------------------------------------------------
CSensor::CSensor( int aAngleDegrees )
    : mAngle( float( aAngleDegrees ) * kDegreesToRadians )
{
}

//-----------------------------------------------------------------------------
// Every wall is tested and the nearest hit kept, so a near wall always hides
// a far one behind it.
//-----------------------------------------------------------------------------
float CSensor::GetReading( const CPose& aRobotPose, const std::vector<Vec2D>& aWalls ) const
{
    float RayAngle     = aRobotPose.mHeading + mAngle;
    Vec2D RayDirection = { std::cos( RayAngle ), std::sin( RayAngle ) };

    float Nearest  = float( kMaxRange );
    int   NumWalls = int( aWalls.size() );

    for ( int i = 0; i < NumWalls; i++ )
    {
        const Vec2D& WallStart = aWalls[i];
        const Vec2D& WallEnd   = aWalls[( i + 1 ) % NumWalls];   // last joins back to first
        Vec2D WallVector = { WallEnd.x - WallStart.x, WallEnd.y - WallStart.y };

        CRayHit Hit = RayHitsWall2D( aRobotPose.mPosition, RayDirection, WallStart, WallVector );

        if ( Hit.mHit && Hit.mDistance < Nearest )
        {
            Nearest = Hit.mDistance;
        }
    }

    return Nearest;
}
