//-----------------------------------------------------------------------------
// CSensor.h

// A range sensor fixed to the robot at an angle from its heading. Casts a ray
// from the robot's position and reports the distance to the first wall it
// meets.

// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef CSENSOR_H
#define CSENSOR_H

#include "Geometry.h"   // Vec2D, CPose, CRayHit, RayHitsWall2D
#include <vector>

//-----------------------------------------------------------------------------
class CSensor
{
    public:
        //---Ctor---
        // aAngleDegrees is measured clockwise from the robot's heading, so 90
        // points straight out to the robot's right.
        CSensor( int aAngleDegrees );

        //---Reading---
        // Distance to the nearest wall along the sensor's ray, or kMaxRange if
        // the ray leaves the map without meeting one.
        float GetReading( const CPose& aRobotPose, const std::vector<Vec2D>& aWalls ) const;

        static const int kMaxRange = 10000;

    private:
        float mAngle;   // radians, clockwise from the robot's heading
};

#endif
