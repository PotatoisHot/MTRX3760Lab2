//-----------------------------------------------------------------------------
// Geometry.h

// Plain geometry types and the 2D vector maths shared by the map, the sensors
// and the robot. Nothing in here knows about rendering, raylib or robots.

// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef GEOMETRY_H
#define GEOMETRY_H

//-----------------------------------------------------------------------------
struct Vec2D
{
    float x;
    float y;
};

//-----------------------------------------------------------------------------
struct CPose
{
    Vec2D mPosition;
    float mHeading;   // radians; 0 faces +x (right), PI/2 faces +y (down)
};

//-----------------------------------------------------------------------------
// Result of casting a ray against one wall segment.
//-----------------------------------------------------------------------------
struct CRayHit
{
    bool  mHit;        // true if the ray meets the segment in front of its origin
    float mDistance;   // distance along the ray to the hit; only valid if mHit
};

//---Vector maths---
float CrossProduct2D( const Vec2D& aVector1, const Vec2D& aVector2 );
bool  ParallelVectors2D( const Vec2D& aVector1, const Vec2D& aVector2 );

//---Ray casting---
// The ray starts at aRayOrigin and points along aRayDirection, which must be a
// unit vector so that mDistance comes out in map units. The wall runs from
// aWallStart to aWallStart + aWallVector.
CRayHit RayHitsWall2D( const Vec2D& aRayOrigin, const Vec2D& aRayDirection,
                          const Vec2D& aWallStart,  const Vec2D& aWallVector );

#endif
