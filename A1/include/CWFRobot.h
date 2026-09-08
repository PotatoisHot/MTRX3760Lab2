//-----------------------------------------------------------------------------
// CWFRobot.h

// Wall-following robot. Carries two range sensors aimed to its right, at 90
// and 45 degrees, and steers to hold a fixed distance from the wall on that
// side.

// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef CWFROBOT_H
#define CWFROBOT_H

#include "CRobot.h"
#include "CSensor.h"

//-----------------------------------------------------------------------------
class CWFRobot : public CRobot
{
    public:
        //---Ctor---
        CWFRobot( const std::string& aName, const CPose& aStartPose, int aRadius );

        //---Simulation---
        void Update( float aTimeStep, const std::vector<Vec2D>& aWalls ) override;

    private:
        //---Sensors---
        CSensor mSensor90;   // straight out to the right
        CSensor mSensor45;   // forward and to the right

        //---Controller---
        // Distances are in map units and the turn rate is in radians per unit
        // time, so the gains are small. Tune here.
        const float mTargetWallDistance;                // robot centre to wall; set from the radius
        static const int kWallMargin  = 30;             // clearance between rim and wall
        static const int kCruiseSpeed = 10;             // forward speed, units per unit time
        const float kDistanceGain = 0.01f;              // turn rate per unit of distance error
        const float kHeadingGain  = 0.04f;              // turn rate per unit of heading error
        const float kMaxTurnRate  = 0.9f;               // cap so a hard turn never stops forward motion
};

#endif
