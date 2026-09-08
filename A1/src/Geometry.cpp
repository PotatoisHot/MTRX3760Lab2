#include "Geometry.h"

//---Two directions whose cross product is smaller than this are parallel.------
static const float kParallelTolerance = 1e-6f;

//-----------------------------------------------------------------------------
float CrossProduct2D( const Vec2D& aVector1, const Vec2D& aVector2 )
{
    return ( aVector1.x * aVector2.y ) - ( aVector1.y * aVector2.x );
}

//-----------------------------------------------------------------------------
bool ParallelVectors2D( const Vec2D& aVector1, const Vec2D& aVector2 )
{
    float Cross = CrossProduct2D( aVector1, aVector2 );

    // Compare both ways so a large negative cross product is not mistaken
    // for parallel.
    return ( Cross > -kParallelTolerance && Cross < kParallelTolerance );
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
