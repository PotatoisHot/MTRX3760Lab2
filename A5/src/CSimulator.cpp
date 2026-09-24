//-----------------------------------------------------------------------------
// CSimulator.cpp
// See CSimulator.h.
//-----------------------------------------------------------------------------

#include "CSimulator.h"
#include <cmath>
#include <iostream>

//-----------------------------------------------------------------------------
CSimulator::CSimulator( float aTimeStep )
    : mTimeStep( aTimeStep ),
      mCurrentTime( 0 ),
      mUpdateCount( 0 )
{
    std::cout << "Simulator has been initialised!" << std::endl;
    std::cout << "Time step size: " << mTimeStep << std::endl;
    std::cout << "Please finish the configuration with AddMap() and AddRobot() before RunSimulator()" << std::endl;
    std::cout << "Enjoy your simulation! - From Dang and Ivy :3" << std::endl;
}

//-----------------------------------------------------------------------------
// The simulator only borrows its maps and robots, so it deletes nothing.
// Whoever created them is responsible for them; see main.cpp.
//-----------------------------------------------------------------------------
CSimulator::~CSimulator()
{
    std::cout << "Simulator is being removed" << std::endl;
}

//-----------------------------------------------------------------------------
bool CSimulator::AddMap( const CLoopReader& aMap )
{
    bool AddSuccess = false;

    if ( aMap.GetVertices().empty() )
    {
        std::cout << "Map '" << aMap.GetName() << "' has no vertices! Was ReadFile() called, and did it succeed?" << std::endl;
    }
    else
    {
        mMaps.push_back( &aMap );
        std::cout << "Added map '" << aMap.GetName() << "' to the simulator" << std::endl;
        AddSuccess = true;
    }

    return AddSuccess;
}

//-----------------------------------------------------------------------------
bool CSimulator::AddRobot( CRobot* apRobot )
{
    bool AddSuccess = false;

    if ( apRobot == nullptr )
    {
        std::cout << "Robot is a nullptr! Please check the input robot pointer." << std::endl;
    }
    else
    {
        mRobots.push_back( apRobot );
        std::cout << "Added robot '" << apRobot->GetName() << "' to the simulator" << std::endl;
        AddSuccess = true;
    }

    return AddSuccess;
}

//-----------------------------------------------------------------------------
bool CSimulator::RemoveRobot()
{
    return false;   // not written yet
}

//-----------------------------------------------------------------------------
bool CSimulator::CheckConfig()
{
    return !mMaps.empty() && !mRobots.empty();
}

//-----------------------------------------------------------------------------
void CSimulator::RunSimulator()
{
    while ( !mRender.WindowShouldClose() )
    {
        Update();
        Draw();
    }

    mRender.CloseWindow();

    // End of run summary
    int NumRobots       = int( mRobots.size() );
    int TotalCollisions = 0;

    std::cout << "Simulator has been closed after " << mUpdateCount << " updates" << std::endl;

    for ( int i = 0; i < NumRobots; i++ )
    {
        int Collisions = mRobots[i]->GetCollisionCount();
        TotalCollisions += Collisions;
        std::cout << "  " << mRobots[i]->GetName() << ": " << Collisions << " collisions" << std::endl;
    }

    std::cout << "  Total: " << TotalCollisions << " collisions" << std::endl;
}

//-----------------------------------------------------------------------------
// One fixed step of simulated time for every robot.
//-----------------------------------------------------------------------------
void CSimulator::Update()
{
    int NumRobots = int( mRobots.size() );

    for ( int i = 0; i < NumRobots; i++ )
    {
        mRobots[i]->Update( mTimeStep );
    }

    mCurrentTime += mTimeStep;
    mUpdateCount++;
}

//-----------------------------------------------------------------------------
// One frame: the maps, then each robot's trail, disc and heading line.
//-----------------------------------------------------------------------------
void CSimulator::Draw()
{
    mRender.BeginDrawing();

    int NumMaps = int( mMaps.size() );

    for ( int i = 0; i < NumMaps; i++ )
    {
        mRender.DrawLoop( mMaps[i]->GetVertices(), 2.0f, BLUE );
    }

    int NumRobots = int( mRobots.size() );

    for ( int i = 0; i < NumRobots; i++ )
    {
        const CPose& Pose   = mRobots[i]->GetPose();
        float        Radius = float( mRobots[i]->GetRadius() );
        const std::vector<Vec2D>& Trail = mRobots[i]->GetTrail();

        Vec2D HeadingEnd = { Pose.mPosition.x + Radius * std::cos( Pose.mHeading ),
                             Pose.mPosition.y + Radius * std::sin( Pose.mHeading ) };

        mRender.DrawTrail( Trail, 2.0f, mRobots[i]->GetTrailColor() );
        mRender.DrawCircle( Pose.mPosition, mRobots[i]->GetRadius(), mRobots[i]->GetBodyColor() );
        mRender.DrawLine( Pose.mPosition, HeadingEnd, 2.0f, WHITE );
    }

    mRender.EndDrawing();
}
