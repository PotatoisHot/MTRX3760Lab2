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
    std::cout << "Please finish the configuration with SetMap() and AddRobot() before RunSimulator()" << std::endl;
    std::cout << "Enjoy your simulation! - From Dang and Ivy :3" << std::endl;
}

//-----------------------------------------------------------------------------
CSimulator::~CSimulator()
{
    std::cout << "Simulator is being removed" << std::endl;
}

//-----------------------------------------------------------------------------
bool CSimulator::SetMap( const std::string& aFileName )
{
    bool ReadSuccess = mLoopReader.ReadFile( aFileName );

    if ( ReadSuccess )
    {
        std::cout << "Read " << aFileName << " successfully" << std::endl;
    }
    else
    {
        std::cout << "Could not read " << aFileName
                  << "! Please check the file name and format." << std::endl;
    }

    return ReadSuccess;
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
    return !mRobots.empty() && !mLoopReader.GetVertices().empty();
}

//-----------------------------------------------------------------------------
const CPose& CSimulator::GetStartPose() const
{
    return mLoopReader.GetStartPose();
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
    std::cout << "Simulator has been closed after " << mUpdateCount << " updates" << std::endl;
}

//-----------------------------------------------------------------------------
// One fixed step of simulated time for every robot.
//-----------------------------------------------------------------------------
void CSimulator::Update()
{
    int NumRobots = int( mRobots.size() );

    for ( int i = 0; i < NumRobots; i++ )
    {
        mRobots[i]->Update( float( mTimeStep ), mLoopReader.GetVertices() );
    }

    mCurrentTime += mTimeStep;
    mUpdateCount++;
}

//-----------------------------------------------------------------------------
// One frame: the room, then every robot as a disc with a heading line.
//-----------------------------------------------------------------------------
void CSimulator::Draw()
{
    mRender.BeginDrawing();
    mRender.DrawLoop( mLoopReader.GetVertices(), 2.0f, BLUE );

    int NumRobots = int( mRobots.size() );

    for ( int i = 0; i < NumRobots; i++ )
    {
        const CPose& Pose   = mRobots[i]->GetPose();
        float        Radius = float( mRobots[i]->GetRadius() );
        const std::vector<Vec2D>& Trail = mRobots[i]->GetTrail();

        Vec2D HeadingEnd = { Pose.mPosition.x + Radius * std::cos( Pose.mHeading ),
                             Pose.mPosition.y + Radius * std::sin( Pose.mHeading ) };

        mRender.DrawCircle( Pose.mPosition, mRobots[i]->GetRadius(), RED );
        mRender.DrawLine( Pose.mPosition, HeadingEnd, 2.0f, WHITE );
        mRender.DrawTrail( Trail, 2.0f, PURPLE );
    }

    mRender.EndDrawing();
}
