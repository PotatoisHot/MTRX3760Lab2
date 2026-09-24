// It finally runs T_T, It costs me a whole night - Sad and Sleepy Dangaroo T_T zzzz
//-----------------------------------------------------------------------------
// main.cpp
// A2: a wall follower and a line follower in the same room at the same time.
// Each robot gets the map it senses and starts where that map says.
//-----------------------------------------------------------------------------

#include "CSimulator.h"
#include "raylib.h"
#include "CWFRobot.h"
#include "CLFRobot.h"
#include "CLoopReader.h"
#include <iostream>

//---Every robot is a disc of this radius, from the spec.----------------------
static const int kRobotRadius = 15;

//-----------------------------------------------------------------------------
int main()
{
    CSimulator TronsSim( 0.3f );

    // The maps live here and are lent to the simulator to draw and to the
    // robots to sense, so they outlive everything that uses them.
    CLoopReader Walls;
    CLoopReader Line;

    bool WallsOk = Walls.ReadFile( "../../ExampleCode/SimpleWalls.map" );
    bool LineOk  = Line.ReadFile(  "../../ExampleCode/SimpleLine.map" );
    

    if ( WallsOk && LineOk )
    {
        TronsSim.AddMap( Walls );
        TronsSim.AddMap( Line );


        CWFRobot WallFollower( "Wall follower", Walls, kRobotRadius, YELLOW, ORANGE );
        CLFRobot LineFollower( "Line follower", Line, Walls, kRobotRadius, GREEN, BLUE );   // follows the line, can hit the walls

        TronsSim.AddRobot( &WallFollower );
        TronsSim.AddRobot( &LineFollower );

        TronsSim.RunSimulator();
    }
    else
    {
        std::cout << "Could not read one of the map files. Check the paths." << std::endl;
    }

    return 0;
}
