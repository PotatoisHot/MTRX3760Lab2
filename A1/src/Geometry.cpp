#include "Geometry.h"
#include <cmath>

//---Two directions whose perp dot product is smaller than this are parallel.---
static const float kParallelTolerance = 1e-6f;

//-----------------------------------------------------------------------------
float DotProduct2D( const Vec2D& aVector1, const Vec2D& aVector2 )
{
    return ( aVector1.x * aVector2.x ) + ( aVector1.y * aVector2.y );
}

//-----------------------------------------------------------------------------
float Vec2DMagnitude( const Vec2D& aVector )
{
    return std::sqrt( aVector.x * aVector.x + aVector.y * aVector.y );
}

//-----------------------------------------------------------------------------
float PerpDotProduct2D( const Vec2D& aVector1, const Vec2D& aVector2 )
{
    return ( aVector1.x * aVector2.y ) - ( aVector1.y * aVector2.x );
}

//-----------------------------------------------------------------------------
bool ParallelVectors2D( const Vec2D& aVector1, const Vec2D& aVector2 )
{
    float PerpDot = PerpDotProduct2D( aVector1, aVector2 );

    // Compare both ways so a large negative perp dot product is not mistaken
    // for parallel.
    return ( PerpDot > -kParallelTolerance && PerpDot < kParallelTolerance );
}

//-----------------------------------------------------------------------------
// The ray is  aRayOrigin + T * aRayDirection  for T > 0.
// The segment is  aSegStart + U * aSegVector  for 0 <= U <= 1.
//
// Setting the two equal and crossing with each direction in turn eliminates
// one unknown each time, giving T and U directly. It is only a hit if the
// crossing is in front of the ray (T > 0) and between the segment's two ends
// (0 <= U <= 1).
//-----------------------------------------------------------------------------
CRayHit RayHitsWall2D( const Vec2D& aRayOrigin, const Vec2D& aRayDirection,
                          const Vec2D& aWallStart,  const Vec2D& aWallVector )
{
    CRayHit Result = { false, 0.0f };

    if ( !ParallelVectors2D( aRayDirection, aWallVector ) )
    {
        Vec2D OriginToWall = { aWallStart.x - aRayOrigin.x,
                              aWallStart.y - aRayOrigin.y };

        float Denom = PerpDotProduct2D( aRayDirection, aWallVector );
        float T     = PerpDotProduct2D( OriginToWall, aWallVector ) / Denom;
        float U     = PerpDotProduct2D( OriginToWall, aRayDirection ) / Denom;

        if ( T > 0.0f && U >= 0.0f && U <= 1.0f )
        {
            Result.mHit      = true;
            Result.mDistance = T;
        }
    }

    return Result;
}

//-----------------------------------------------------------------------------
// Project the point onto the wall to find the nearest spot on it. Holding the
// projection inside [0, 1] keeps that spot on the segment, so past either end
// the answer is the end itself, not a point on the line's extension.
//-----------------------------------------------------------------------------
Vec2D NearestPointOnWall2D( const Vec2D& aPoint, const Vec2D& aWallStart, const Vec2D& aWallVector )
{
    Vec2D WallStartToPoint = { aPoint.x - aWallStart.x, aPoint.y - aWallStart.y };

    // How far along the wall the point projects, 0 at the start and 1 at the end
    float WallLengthSquared = DotProduct2D( aWallVector, aWallVector );
    float ProjectionRatio   = DotProduct2D( WallStartToPoint, aWallVector ) / WallLengthSquared;

    if ( ProjectionRatio < 0.0f )
    {
        ProjectionRatio = 0.0f;
    }
    else if ( ProjectionRatio > 1.0f )
    {
        ProjectionRatio = 1.0f;
    }

    Vec2D Nearest = { aWallStart.x + ProjectionRatio * aWallVector.x,
                      aWallStart.y + ProjectionRatio * aWallVector.y };

    return Nearest;
}

//-----------------------------------------------------------------------------
float PointToWallDistance2D( const Vec2D& aPoint, const Vec2D& aWallStart, const Vec2D& aWallVector )
{
    Vec2D Nearest = NearestPointOnWall2D( aPoint, aWallStart, aWallVector );
    Vec2D ToPoint = { aPoint.x - Nearest.x, aPoint.y - Nearest.y };

    return Vec2DMagnitude( ToPoint );
}
