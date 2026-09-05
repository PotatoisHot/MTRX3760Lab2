#include "CSimulator.h"


CSimulator::CSimulator(int aTimeStep)
    :mCurrentTime(0), mTimeStep(aTimeStep)
{
    std::cout << "Simulator has been intialised!" << std::endl;
    std::cout << "Current speed (time step size):" << mTimeStep << std::endl;
    std::cout << "Please finish the configuration before RunSimulator() with SetMap() and AddRobot()" << std::endl;
    std::cout << "If you are unsure about your configurations. You can check it with CheckConfig(), which will return a boolean value" << std::endl;
    std::cout << "Enjoy your simulation! - From Dang and Ivy :3" << std::endl;
};


CSimulator::~CSimulator()
{
    std::cout << "Simulator is being removed" << std::endl;
};


bool CSimulator::SetMap( std::string aFileName )
{
    bool ReadSuccess = mLoopReader.ReadFile( aFileName );
    if ( ReadSuccess )
    {
        std::cout << "Read "<< aFileName << " sucessfully";
    }
    else 
    {
        std::cout << "Read "<< aFileName << " unsucessfully! Please check the input file name or the file format.";
    }

    return ReadSuccess;
}

bool CSimulator::AddRobot(CRobot* aRobot, int aID)
{   
    bool AddSuccess = true;
    if ( aRobot == nullptr )
    {
        std::cout << "Robot is a nullptr! Please check the input robot pointer." << std::endl;
        AddSuccess = false;
    }
    else
    {
        mRobots.push_back(aRobot);
        std::cout << "Robot has been added to the simulator!" << std::endl;
    }

    return AddSuccess;
}



bool CSimulator::RemoveRobot( int aID )
{
    bool DeleteSuccess = false;
    for ( int i=0; i < mRobots.size(); i++ )
    {
        if ( mRobots[i]->GetID() == aID )
        {   
            mRobots.erase(mRobots.begin() + i);
            std::cout << "Robot with ID= " << aID << " has been deleted." <<std::endl;
            DeleteSuccess = true;
        }
    }
    
    if ( !DeleteSuccess )
    {
        std::cout << "There is not any robots in the system assigned with the given ID= " << aID << "." << std::endl;
    }

    return DeleteSuccess;
}


void CSimulator::RunSimulator()
{   

    while( !mRender.WindowShouldClose() )
    {
        // Window has not been closed yet
        CSimulator::Update();
    }

    mRender.CloseWindow();
    std::cout << "Simulator has been closed!" << std::endl;
};


void CSimulator::Update()
{   
    // Dang's Note: Add Robot Update
    for ( int i = 0; i < mRobots.size(); i++)
    {
        Vec2D CurrentPosition = mRobots[i]->GetCurrentPosition();
        int Radius = mRobots[i]->GetRadius();

        mRender.BeginDrawing();
        mRender.DrawLoop( mLoopReader.GetVertices(), 2.0, BLUE );
        mRender.DrawCircle(CurrentPosition, Radius, RED);
        mRender.EndDrawing();

        mRobots[i]->Update(); // Just increase x-coordinates for now
    }
    //mCurrentTime += mTimeStep;
}

