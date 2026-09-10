//-----------------------------------------------------------------------------
// CLineSensor.cpp
// See CLineSensor.h.
//-----------------------------------------------------------------------------

#include "CLineSensor.h"

//-----------------------------------------------------------------------------
CLineSensor::CLineSensor( Vec2D aMountOffset )
    : CSensor( aMountOffset, 0 )   // looks down, so the angle doesn't matter
{
}

//-----------------------------------------------------------------------------
// Test every segment and keep the nearest, then compare to half the width.
//-----------------------------------------------------------------------------
bool CLineSensor::IsOverLine( const CPose& aRobotPose, const std::vector<Vec2D>& aLine ) const
{
    Vec2D Here             = GetSensorPosition( aRobotPose );
    float SmallestDistance = float( kMaxRange );
    int   NumSegments      = int( aLine.size() );

    for ( int i = 0; i < NumSegments; i++ )
    {
        const Vec2D& SegStart = aLine[i];
        const Vec2D& SegEnd   = aLine[( i + 1 ) % NumSegments];   // last joins back to first
        Vec2D SegVector = { SegEnd.x - SegStart.x, SegEnd.y - SegStart.y };

        float Distance = PointToWallDistance2D( Here, SegStart, SegVector );

        if ( Distance < SmallestDistance )
        {
            SmallestDistance = Distance;
        }
    }

    return SmallestDistance < float( kLineWidth ) / 2.0f;
}
