//-----------------------------------------------------------------------------
// CSensor.h
// Base class for anything bolted to the robot that senses the map. It owns the
// mounting (an offset from the centre and an angle from the heading) and works
// out where that is in the world for the current pose. What to do there is up
// to the derived class.
//
// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef CSENSOR_H
#define CSENSOR_H

#include "Geometry.h"   // Vec2D, CPose

//-----------------------------------------------------------------------------
class CSensor
{
    public:
        //---Ctor/Dtor---
        // Offset is in the robot's frame (x forward, y right), angle is
        // clockwise from the heading.
        CSensor( Vec2D aMountOffset, int aMountAngleDegrees );
        virtual ~CSensor() = 0;   // abstract; still needs a body in the .cpp

    protected:
        //---Where the sensor is right now---
        Vec2D GetSensorPosition( const CPose& aRobotPose ) const;   // map units
        float GetSensorAngle( const CPose& aRobotPose ) const;      // radians

    private:
        Vec2D mMountOffset;   // robot frame
        float mMountAngle;    // radians, clockwise from the heading
};

#endif
