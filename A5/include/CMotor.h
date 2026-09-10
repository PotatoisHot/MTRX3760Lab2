//-----------------------------------------------------------------------------
// CMotor.h
// One drive wheel. Holds a speed, clamped to what the motor can do.
//
// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef CMOTOR_H
#define CMOTOR_H

#include "Helper.h"   // Clamp
#include <string>

//-----------------------------------------------------------------------------
class CMotor
{
    public:
        //---Ctor---
        CMotor( const std::string& aName );

        //---Speed---
        void SetSpeed( int aSpeed );   // clamped to [kMinSpeed, kMaxSpeed]
        int  GetSpeed() const;

        //---Debug---
        void Report() const;

    private:
        std::string mName;
        int         mSpeed;

        static const int kMaxSpeed =  20;
        static const int kMinSpeed = -20;   // reverse allowed, so the robot can turn on the spot
};

#endif
