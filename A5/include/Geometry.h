//-----------------------------------------------------------------------------
// Geometry.h
// Plain 2D types and the vector maths shared by the map, sensors and robots.
// Nothing in here knows about rendering or robots.
//
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
    float mHeading;   // radians, clockwise from +x (0 right, PI/2 down)
};

//-----------------------------------------------------------------------------
// What a ray cast against one wall gives back.
//-----------------------------------------------------------------------------
struct CRayHit
{
    bool  mHit;        // did the ray meet the wall in front of its origin
    float mDistance;   // how far along the ray; only meaningful if mHit
};

//---Vector maths---
float DotProduct2D( const Vec2D& aVector1, const Vec2D& aVector2 );
float CrossProduct2D( const Vec2D& aVector1, const Vec2D& aVector2 );
bool  ParallelVectors2D( const Vec2D& aVector1, const Vec2D& aVector2 );
float Vec2DMagnitude( const Vec2D& aVector );

//---Ray casting---
// aRayDirection must be a unit vector so the distance comes out in map units.
// The wall runs from aWallStart to aWallStart + aWallVector.
CRayHit RayHitsWall2D( const Vec2D& aRayOrigin, const Vec2D& aRayDirection,
                       const Vec2D& aWallStart,  const Vec2D& aWallVector );

//---Point to wall---
// Shortest distance from a point to a wall segment, ends included.
float PointToWallDistance2D( const Vec2D& aPoint, const Vec2D& aWallStart, const Vec2D& aWallVector );

#endif
