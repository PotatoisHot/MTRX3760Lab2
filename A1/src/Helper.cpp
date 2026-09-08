#include "Helper.h"

int ClampInt( const int aValue, const int aMin, const int aMax )
{
    int Clamped = aValue;   // in range unless one of the checks below says otherwise

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