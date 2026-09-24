//-----------------------------------------------------------------------------
// CRobot.h
// Base class for every robot. Owns the pose, the two wheels and the kinematics
// that turn wheel speeds into motion. A robot is given the map it senses when
// it is built and starts near where that map says. Derived classes add sensors
// and a control law in Update().
//
// For A5 the start pose and the wheels are given a little random noise, so
// twenty robots of the same kind take twenty different paths.
//
// Written by Dangaroo and Ivy :D
//-----------------------------------------------------------------------------

#ifndef CROBOT_H
#define CROBOT_H

#include "raylib.h"
#include "Geometry.h"   // Vec2D, CPose
#include "CMotor.h"
#include <string>
#include <vector>

class CLoopReader;   // only a reference is kept here

//-----------------------------------------------------------------------------
class CRobot
{
    public:
        //---Ctor/Dtor---
        // aMap is what the robot senses, aRoom is what it can bump into. For a
        // wall follower they are the same loop. The robot keeps references to
        // both, so they must outlive it.
        CRobot( const std::string& aName, const CLoopReader& aMap, const CLoopReader& aRoom,
                int aRadius, Color aTrailColor, Color aBodyColor );
        virtual ~CRobot();

        //---Access---
        const std::string& GetName() const;
        int                GetRadius() const;
        const CPose&       GetStartPose() const;
        const CPose&       GetPose() const;
        const std::vector<Vec2D>& GetTrail() const;
        int                GetCollisionCount() const;

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
        // A random number between -aRange and +aRange
        static float RandomOffset( float aRange );

        // Keep the robot inside the walls; count and report each new contact
        void HandleCollision( const std::vector<Vec2D>& aWalls );

        std::string        mName;
        int                mRadius;
        const CLoopReader& mMap;
        const CLoopReader& mRoom;
        CPose              mStartPose;
        CPose              mPose;

        CMotor mLeftMotor;
        CMotor mRightMotor;

        // For easier recognitions, especially in A5 where we have multiple robots
        Color mTrailColor;
        Color mBodyColor;

        std::vector<Vec2D> mTrail;   // everywhere the robot has been

        int  mCollisionCount;
        bool mTouchingWall;          // so a long scrape counts as one collision

        //---Noise, all symmetric about zero---
        static const int kPositionNoise = 20;   // units, applied to x and y separately
        static const int kHeadingNoise  = 10;   // degrees
        static const int kWheelNoise    = 30;    // speed units, per wheel, per update
};

#endif
