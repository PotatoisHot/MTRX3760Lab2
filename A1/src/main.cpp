// It finally runs T_T, It costs me a whole night - Sad and Sleepy Dangaroo T_T zzzz
#include "CSimulator.h"
#include "CWFRobot.h"

//---The assignment specifies the robot in A1 has a radius of 15 pixels-------------
static const int kRobotRadius = 15;

//-----------------------------------------------------------------------------
int main()
{
    CSimulator TronsSim( 0.3 );   

    if ( TronsSim.SetMap( "../../ExampleCode/SimpleWalls.map" ) )
    {
        // The robot starts where the map says. It lives on the stack here and
        // outlives the simulator's use of it, so no new/delete is needed.

        CWFRobot WallFollower( "Wall follower", TronsSim.GetStartPose(), kRobotRadius );

        TronsSim.AddRobot( &WallFollower );
        TronsSim.RunSimulator();
    }

    return 0;
}