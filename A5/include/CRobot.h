//-----------------------------------------------------------------------------
// CRobot.h
// Base class for every robot. Owns the pose, the two wheels and the kinematics
// that turn wheel speeds into motion. A robot is given the map it senses when
// it is built and starts where that map says. Derived classes add sensors and
// a control law in Update().
//
// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef CROBOT_H
#define CROBOT_H

#include "raylib.h"
#include "Geometry.h"   // Vec2D, CPose
#include "CMotor.h"
#include <string>
#include <vector>
#include <random>


class CLoopReader;   // only a reference is kept here

//-----------------------------------------------------------------------------
class CRobot
{
    public:
        //---Ctor/Dtor---
        // The robot keeps a reference to aMap, so the map must outlive it.
        CRobot( const std::string& aName, const CLoopReader& aMap, int aRadius, Color aTrailColor, Color aBodyColor );
        virtual ~CRobot();

        //---Access---
        const std::string& GetName() const;
        int                GetRadius() const;
        const CPose&       GetStartPose() const;
        const CPose&       GetPose() const;
        const std::vector<Vec2D>& GetTrail() const;
        
        const Color& GetTrailColor() const;
        const Color& GetBodyColor() const;

        //---Simulation---
        virtual void Update( float aTimeStep ) = 0;

    protected:
        const CLoopReader& GetMap() const;

        // Ask for a forward speed and a turn rate (radians per unit time,
        // positive turns right). The motors clamp what they can, and the pose
        // moves by what the wheels actually did.
        void Drive( float aSpeed, float aTurnRate, float aTimeStep );

    private:
        std::string        mName;
        int                mRadius;
        const CLoopReader& mMap;
        CPose              mStartPose;
        CPose              mPose;

        CMotor mLeftMotor;
        CMotor mRightMotor;

        // For easier recognitions, especially in A5 where we have multiple robots
        Color mTrailColor;
        Color mBodyColor;

        std::vector<Vec2D> mTrail;   // everywhere the robot has been

        
        // Constants for Random Offset Generation
        std::mt19937 mRandomGenerator;               // Mersenne Twister random number generator
        std::uniform_real_distribution<float> mRandomdRealDistribution;
        static const int kPositionOffsetRange = 40;  // Range for random position offset
        static const int kHeadingOffsetRange = 8;    // Range for random heading offset
        static const int kSpeedOffsetRange = 5;     // Scale for wheel rotation offset
};

#endif
