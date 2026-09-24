//-----------------------------------------------------------------------------
// CLineSensor.h
// A line sensor mounted somewhere on the robot, looking straight down. Says
// whether the floor under it is line or not.
//
// Written by Dangaroo and Ivy :D
//-----------------------------------------------------------------------------

#ifndef CLINESENSOR_H
#define CLINESENSOR_H

#include "CSensor.h"
#include "Geometry.h"   // Vec2D, CPose
#include <vector>

//-----------------------------------------------------------------------------
class CLineSensor : public CSensor
{
    public:
        //---Ctor---
        CLineSensor( Vec2D aMountOffset );   // from the centre, in the robot's frame

        //---Reading---
        // True if the sensor is within half the line width of any segment.
        // The distance itself stays in here; the robot only gets the bool.
        bool IsOverLine( const CPose& aRobotPose, const std::vector<Vec2D>& aLine ) const;

    private:
        static const int kLineWidth = 5;       // units, from the spec
        static const int kMaxRange  = 10000;   // further than anything in the map
};

#endif
