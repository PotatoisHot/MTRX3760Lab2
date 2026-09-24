//-----------------------------------------------------------------------------
// CWallSensor.h
// A range sensor at the robot's centre, aimed at an angle from its heading.
// Casts a ray and reports the distance to the first wall it meets.
//
// Written by Dangaroo and Ivy :D
//-----------------------------------------------------------------------------

#ifndef CWALLSENSOR_H
#define CWALLSENSOR_H

#include "CSensor.h"
#include "Geometry.h"   // Vec2D, CPose
#include <vector>

//-----------------------------------------------------------------------------
class CWallSensor : public CSensor
{
    public:
        //---Ctor---
        CWallSensor( int aAngleDegrees );   // clockwise from the heading; 90 is straight right

        //---Reading---
        // Distance to the nearest wall along the ray, or kMaxRange if none.
        float GetReading( const CPose& aRobotPose, const std::vector<Vec2D>& aWalls ) const;

        static const int kMaxRange = 10000;
};

#endif
