//-----------------------------------------------------------------------------
// CMotor.cpp
// See CMotor.h.
//-----------------------------------------------------------------------------

#include "CMotor.h"
#include <iostream>

//-----------------------------------------------------------------------------
CMotor::CMotor( const std::string& aName )
    : mName( aName ),
      mSpeed( 0 )
{
}

//-----------------------------------------------------------------------------
void CMotor::SetSpeed( int aSpeed )
{
    mSpeed = Clamp( aSpeed, kMinSpeed, kMaxSpeed );
}

//-----------------------------------------------------------------------------
int CMotor::GetSpeed() const
{
    return mSpeed;
}

//-----------------------------------------------------------------------------
void CMotor::Report() const
{
    std::cout << mName << " is currently set at speed: " << mSpeed << std::endl;
}
