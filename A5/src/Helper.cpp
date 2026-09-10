//-----------------------------------------------------------------------------
// Helper.cpp
// See Helper.h.
//-----------------------------------------------------------------------------

#include "Helper.h"

//-----------------------------------------------------------------------------
int Clamp( int aValue, int aMin, int aMax )
{
    int Clamped = aValue;

    if ( aValue < aMin )
    {
        Clamped = aMin;
    }
    else if ( aValue > aMax )
    {
        Clamped = aMax;
    }

    return Clamped;
}

//-----------------------------------------------------------------------------
float Clamp( float aValue, float aMin, float aMax )
{
    float Clamped = aValue;

    if ( aValue < aMin )
    {
        Clamped = aMin;
    }
    else if ( aValue > aMax )
    {
        Clamped = aMax;
    }

    return Clamped;
}
