//-----------------------------------------------------------------------------
// CLFRobot.h
// Line follower. Two line sensors on the front rim, one dead ahead over the
// line and one a little round to the right, and a controller that keeps the
// centre sensor on the line.
//
// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef CLFROBOT_H
#define CLFROBOT_H

#include "CRobot.h"
#include "CLineSensor.h"

//-----------------------------------------------------------------------------
class CLFRobot : public CRobot
{
    public:
        //---Ctor---
        CLFRobot( const std::string& aName, const CLoopReader& aLine, int aRadius );

        //---Simulation---
        void Update( float aTimeStep ) override;

    private:
        //---Sensors---
        CLineSensor mCentreSensor;   // front of the rim
        CLineSensor mRightSensor;    // kRightSensorAngle round the rim to the right

        // The right sensor's sideways offset is radius * sin( angle ). Keep
        // that under the line width or the line can hide between the sensors.
        static const int kRightSensorAngle = 20;   // degrees

        //---Controller---
        static const int kCruiseSpeed = 5;    // units per unit time
        const float kGentleTurn = 0.3f;       // radians per unit time
        const float kHardTurn   = 0.5f;
};

#endif
