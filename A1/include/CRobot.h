//-----------------------------------------------------------------------------
// CRobot.h

// Base class for every robot in the simulator. Owns the pose, the two drive
// wheels, and the kinematics that turn wheel speeds into motion. A derived
// class adds its sensors and a control law by implementing Update().

// Written by Dangaroo :D 
//-----------------------------------------------------------------------------

#ifndef CROBOT_H
#define CROBOT_H

#include "Geometry.h"   // Vec2D, CPose
#include "CMotor.h"
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
class CRobot
{
    public:
        //---Ctor/Dtor---
        CRobot( const std::string& aName, const CPose& aStartPose, int aRadius );
        virtual ~CRobot();

        //---Access---
        const std::string& GetName() const;
        int                GetRadius() const;
        const CPose&       GetStartPose() const;
        const CPose&       GetPose() const;
        const std::vector<Vec2D>& GetTrail() const;

        //---Simulation---
        // Advance the robot by one fixed timestep. aWalls is the closed loop
        // of wall vertices the sensors can see.
        virtual void Update( float aTimeStep, const std::vector<Vec2D>& aWalls ) = 0;

    protected:
        // Ask for a forward speed and a turn rate (radians per unit time,
        // positive is clockwise on screen). Converts them to wheel speeds,
        // clamps through the motors, then moves the pose by what the wheels
        // actually did.
        void Drive( float aSpeed, float aTurnRate, float aTimeStep );

    private:
        std::string mName;
        int         mRadius;
        CPose       mStartPose;
        CPose       mPose;

        CMotor mLeftMotor;
        CMotor mRightMotor;

        // Log the robot's previous coordinates for trail plotting
        std::vector<Vec2D> mTrail;
};

#endif
