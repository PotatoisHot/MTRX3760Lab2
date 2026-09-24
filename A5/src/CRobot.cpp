//-----------------------------------------------------------------------------
// CRobot.cpp
// See CRobot.h.
//-----------------------------------------------------------------------------

#include "CRobot.h"
#include "CLoopReader.h"
#include <cmath>
#include <cstdlib>    // rand, RAND_MAX
#include <iostream>

//---The heading noise is given in degrees and applied in radians.-------------
static const float kDegreesToRadians = float( M_PI ) / 180.0f;

//-----------------------------------------------------------------------------
// Start where the map says, then nudge the position and heading a little so
// no two robots begin in quite the same place.
//-----------------------------------------------------------------------------
CRobot::CRobot( const std::string& aName, const CLoopReader& aMap, const CLoopReader& aRoom,
                int aRadius, Color aTrailColor, Color aBodyColor )
    : mName( aName ),
      mRadius( aRadius ),
      mMap( aMap ),
      mRoom( aRoom ),
      mStartPose( aMap.GetStartPose() ),
      mPose( aMap.GetStartPose() ),
      mLeftMotor( "Left motor" ),
      mRightMotor( "Right motor" ),
      mTrailColor( aTrailColor ),
      mBodyColor( aBodyColor ),
      mCollisionCount( 0 ),
      mTouchingWall( false )
{
    mStartPose.mPosition.x += RandomOffset( float( kPositionNoise ) );
    mStartPose.mPosition.y += RandomOffset( float( kPositionNoise ) );
    mStartPose.mHeading    += RandomOffset( float( kHeadingNoise ) ) * kDegreesToRadians;

    mPose = mStartPose;
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
const CLoopReader& CRobot::GetMap() const
{
    return mMap;
}

//-----------------------------------------------------------------------------
const Color& CRobot::GetTrailColor() const
{
    return mTrailColor;
}

//-----------------------------------------------------------------------------
const Color& CRobot::GetBodyColor() const
{
    return mBodyColor;
}

//-----------------------------------------------------------------------------
// rand() gives 0 to RAND_MAX. Scale to 0..1, shift to -1..1, then scale to
// the range asked for. main() seeds it once with srand().
//-----------------------------------------------------------------------------
float CRobot::RandomOffset( float aRange )
{
    float Unit = float( rand() ) / float( RAND_MAX );

    return ( 2.0f * Unit - 1.0f ) * aRange;
}

//-----------------------------------------------------------------------------
// Differential drive. Wheels sit on the rim either side, so the wheel base is
// the diameter and turn rate = ( left - right ) / wheel base. With y down and
// headings clockwise, a faster left wheel turns the robot right.
//
// Each wheel gets its own bit of noise on top of what the motor was set to,
// so the robot never turns quite as commanded.
//-----------------------------------------------------------------------------
void CRobot::Drive( float aSpeed, float aTurnRate, float aTimeStep )
{
    float WheelBase      = 2.0f * float( mRadius );
    float HalfDifference = aTurnRate * WheelBase / 2.0f;

    mLeftMotor.SetSpeed(  int( aSpeed + HalfDifference ) );
    mRightMotor.SetSpeed( int( aSpeed - HalfDifference ) );

    // Use what the motors actually did after clamping, plus a little noise
    float LeftSpeed  = float( mLeftMotor.GetSpeed() )  + RandomOffset( float( kWheelNoise ) );
    float RightSpeed = float( mRightMotor.GetSpeed() ) + RandomOffset( float( kWheelNoise ) );
    float Speed      = ( LeftSpeed + RightSpeed ) / 2.0f;
    float TurnRate   = ( LeftSpeed - RightSpeed ) / WheelBase;

    // Step along the heading at the middle of the update, so arcs stay arcs
    float MidHeading = mPose.mHeading + TurnRate * aTimeStep / 2.0f;

    mTrail.push_back( mPose.mPosition );
    mPose.mPosition.x += Speed * std::cos( MidHeading ) * aTimeStep;
    mPose.mPosition.y += Speed * std::sin( MidHeading ) * aTimeStep;
    mPose.mHeading    += TurnRate * aTimeStep;

    HandleCollision( mRoom.GetVertices() );
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
