//-----------------------------------------------------------------------------
// CWFRobot.h
// Wall follower. Two range sensors aimed to the right, at 90 and 45 degrees,
// and a controller that holds a set distance from the wall on that side.
//
// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef CWFROBOT_H
#define CWFROBOT_H

#include "CRobot.h"
#include "CWallSensor.h"

//-----------------------------------------------------------------------------
class CWFRobot : public CRobot
{
    public:
        //---Ctor---
        CWFRobot( const std::string& aName, const CLoopReader& aWalls, int aRadius, Color aTrailColor, Color aBodyColor );

        //---Simulation---
        void Update( float aTimeStep ) override;

    private:
        //---Sensors---
        CWallSensor mSensor90;   // straight out to the right
        CWallSensor mSensor45;   // forward and to the right

        //---Controller---
        // Distances are in map units and turn rate in radians per unit time,
        // so the gains are small.
        const float mTargetWallDistance;      // centre to wall, set from the radius
        static const int kWallMargin  = 30;   // gap between rim and wall
        static const int kCruiseSpeed = 10;   // units per unit time
        const float kDistanceGain = 0.01f;
        const float kHeadingGain  = 0.04f;
        const float kMaxTurnRate  = 0.9f;     // so a hard turn never stops forward motion
};

#endif
