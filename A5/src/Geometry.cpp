//-----------------------------------------------------------------------------
// Geometry.cpp
// See Geometry.h.
//-----------------------------------------------------------------------------

#include "Geometry.h"
#include "Helper.h"   // Clamp
#include <cmath>

//---Cross products smaller than this count as parallel.-----------------------
static const float kParallelTolerance = 1e-6f;

//-----------------------------------------------------------------------------
float DotProduct2D( const Vec2D& aVector1, const Vec2D& aVector2 )
{
    return ( aVector1.x * aVector2.x ) + ( aVector1.y * aVector2.y );
}

//-----------------------------------------------------------------------------
float CrossProduct2D( const Vec2D& aVector1, const Vec2D& aVector2 )
{
    return ( aVector1.x * aVector2.y ) - ( aVector1.y * aVector2.x );
}

//-----------------------------------------------------------------------------
float Vec2DMagnitude( const Vec2D& aVector )
{
    return std::sqrt( aVector.x * aVector.x + aVector.y * aVector.y );
}

//-----------------------------------------------------------------------------
bool ParallelVectors2D( const Vec2D& aVector1, const Vec2D& aVector2 )
{
    float Cross = CrossProduct2D( aVector1, aVector2 );

    // Check both signs; a big negative cross product is not parallel either
    return ( Cross > -kParallelTolerance && Cross < kParallelTolerance );
}

//-----------------------------------------------------------------------------
// Ray is aRayOrigin + T * aRayDirection, wall is aWallStart + U * aWallVector.
// Crossing both with each direction in turn solves for T and U. It only counts
// as a hit if T > 0 (in front of the ray) and 0 <= U <= 1 (between the ends).
//-----------------------------------------------------------------------------
CRayHit RayHitsWall2D( const Vec2D& aRayOrigin, const Vec2D& aRayDirection,
                       const Vec2D& aWallStart,  const Vec2D& aWallVector )
{
    CRayHit Result = { false, 0.0f };

    if ( !ParallelVectors2D( aRayDirection, aWallVector ) )
    {
        Vec2D OriginToWall = { aWallStart.x - aRayOrigin.x,
                               aWallStart.y - aRayOrigin.y };

        float Denom = CrossProduct2D( aRayDirection, aWallVector );
        float T     = CrossProduct2D( OriginToWall, aWallVector ) / Denom;
        float U     = CrossProduct2D( OriginToWall, aRayDirection ) / Denom;

        if ( T > 0.0f && U >= 0.0f && U <= 1.0f )
        {
            Result.mHit      = true;
            Result.mDistance = T;
        }
    }

    return Result;
}

//-----------------------------------------------------------------------------
// Project the point onto the wall to find the nearest spot on it. Clamping the
// projection to [0, 1] keeps that spot on the segment, so past either end the
// answer is the distance to the end, not to the line's extension.
//-----------------------------------------------------------------------------
float PointToWallDistance2D( const Vec2D& aPoint, const Vec2D& aWallStart, const Vec2D& aWallVector )
{
    float Distance = 0.0f;

    Vec2D WallStartToPoint = { aPoint.x - aWallStart.x, aPoint.y - aWallStart.y };

    // How far along the wall the point projects, 0 at the start and 1 at the end
    float WallLengthSquared = DotProduct2D( aWallVector, aWallVector );
    float ProjectionRatio   = DotProduct2D( WallStartToPoint, aWallVector ) / WallLengthSquared;
    ProjectionRatio = Clamp( ProjectionRatio, 0.0f, 1.0f );

    // The nearest point on the wall, then the distance to it
    Vec2D ProjectionPoint = { aWallStart.x + ProjectionRatio * aWallVector.x, aWallStart.y + ProjectionRatio * aWallVector.y };

    Vec2D ProjectionToPoint = { aPoint.x - ProjectionPoint.x, aPoint.y - ProjectionPoint.y };

    Distance = Vec2DMagnitude( ProjectionToPoint );

    return Distance;
}
