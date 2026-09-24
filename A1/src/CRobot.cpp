#include "CRobot.h"
#include <cmath>
#include <iostream>

//-----------------------------------------------------------------------------
CRobot::CRobot( const std::string& aName, const CPose& aStartPose, int aRadius )
    : mName( aName ),
      mRadius( aRadius ),
      mStartPose( aStartPose ),
      mPose( aStartPose ),
      mLeftMotor( "Left motor" ),
      mRightMotor( "Right motor" ),
      mCollisionCount( 0 ),
      mTouchingWall( false )
{
}

//-----------------------------------------------------------------------------
CRobot::~CRobot()
{
    std::cout << "Robot " << mName << " is destroyed." << std::endl;
}

//-----------------------------------------------------------------------------
const std::string& CRobot::GetName() const
{
    return mName;
}

//-----------------------------------------------------------------------------
int CRobot::GetRadius() const
{
    return mRadius;
}

//-----------------------------------------------------------------------------
const CPose& CRobot::GetStartPose() const
{
    return mStartPose;
}

//-----------------------------------------------------------------------------
const CPose& CRobot::GetPose() const
{
    return mPose;
}


//-----------------------------------------------------------------------------
const std::vector<Vec2D>& CRobot::GetTrail() const
{
    return mTrail;
}

//-----------------------------------------------------------------------------
int CRobot::GetCollisionCount() const
{
    return mCollisionCount;
}

//-----------------------------------------------------------------------------
// Walls are solid. If the last move left the centre closer to a wall than one
// radius, the robot is pushed back out along the wall's normal, so it slides
// along the wall rather than passing through it. Contact is counted once, on
// the update it starts, so a scrape along the wall is one collision.
//-----------------------------------------------------------------------------
void CRobot::HandleCollision( const std::vector<Vec2D>& aWalls )
{
    int   NumWalls     = int( aWalls.size() );
    float Nearest      = 0.0f;
    Vec2D NearestPoint = mPose.mPosition;

    for ( int i = 0; i < NumWalls; i++ )
    {
        const Vec2D& WallStart = aWalls[i];
        const Vec2D& WallEnd   = aWalls[( i + 1 ) % NumWalls];   // last joins back to first
        Vec2D WallVector = { WallEnd.x - WallStart.x, WallEnd.y - WallStart.y };

        Vec2D Point    = NearestPointOnWall2D( mPose.mPosition, WallStart, WallVector );
        Vec2D ToCentre = { mPose.mPosition.x - Point.x, mPose.mPosition.y - Point.y };
        float Distance = Vec2DMagnitude( ToCentre );

        if ( i == 0 || Distance < Nearest )
        {
            Nearest      = Distance;
            NearestPoint = Point;
        }
    }

    bool Touching = ( NumWalls > 0 && Nearest <= float( mRadius ) );

    if ( Touching && !mTouchingWall )
    {
        mCollisionCount++;
        std::cout << "Robot " << mName << " hit a wall at ("
                  << mPose.mPosition.x << ", " << mPose.mPosition.y
                  << "), collision " << mCollisionCount << std::endl;
    }

    mTouchingWall = Touching;

    // Push the centre back out to exactly one radius from the wall
    if ( Touching && Nearest > 0.0f )
    {
        float Overlap = float( mRadius ) - Nearest;

        mPose.mPosition.x += ( mPose.mPosition.x - NearestPoint.x ) / Nearest * Overlap;
        mPose.mPosition.y += ( mPose.mPosition.y - NearestPoint.y ) / Nearest * Overlap;
    }
}

//-----------------------------------------------------------------------------
// Differential drive. The wheels sit at the rim, one either side, so the
// wheel base is the diameter. The turn rate comes from the difference in
// wheel speeds:  turn = ( left - right ) / wheel base.
//
// With y down and headings measured clockwise, a faster LEFT wheel turns the
// robot clockwise, so left gets the positive half of the difference.
//-----------------------------------------------------------------------------
void CRobot::Drive( float aSpeed, float aTurnRate, float aTimeStep )
{
    float WheelBase      = 2.0f * float( mRadius );
    float HalfDifference = aTurnRate * WheelBase / 2.0f;

    mLeftMotor.SetSpeed(  int( aSpeed + HalfDifference ) );
    mRightMotor.SetSpeed( int( aSpeed - HalfDifference ) );

    // Move by what the motors actually did after clamping, not what was asked.
    float LeftSpeed  = float( mLeftMotor.GetSpeed() );
    float RightSpeed = float( mRightMotor.GetSpeed() );
    float Speed      = ( LeftSpeed + RightSpeed ) / 2.0f;
    float TurnRate   = ( LeftSpeed - RightSpeed ) / WheelBase;

    // Midpoint integration: step along the heading at the middle of the
    // update rather than the start, so arcs do not spiral outward.
    float MidHeading = mPose.mHeading + TurnRate * aTimeStep / 2.0f;

    mTrail.push_back( mPose.mPosition );   // log the old position before moving
    mPose.mPosition.x += Speed * std::cos( MidHeading ) * aTimeStep;
    mPose.mPosition.y += Speed * std::sin( MidHeading ) * aTimeStep;
    mPose.mHeading    += TurnRate * aTimeStep;
}
