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

// Custom color for MTRX3760 Lab2 use
#define OLIVE      CLITERAL(Color){ 128, 128, 0, 255 }      // Olive
#define TEAL       CLITERAL(Color){ 0, 128, 128, 255 }      // Teal
#define NAVY       CLITERAL(Color){ 0, 0, 128, 255 }        // Navy
#define SILVER     CLITERAL(Color){ 192, 192, 192, 255 }    // Silver

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

    
    // Make 20 colors for the robots to use, currently keeping Trail as same as body color
    std::vector<Color> TrailColors = { ORANGE, RED, BROWN, YELLOW, GREEN, BLUE, PURPLE, PINK, SKYBLUE, 
        LIME, GOLD, VIOLET, MAROON, OLIVE, TEAL, NAVY, SILVER, GRAY, BLACK, WHITE };
    
    std::vector<Color> BodyColors = { ORANGE, RED, BROWN, YELLOW, GREEN, BLUE, PURPLE, PINK, SKYBLUE, 
        LIME, GOLD, VIOLET, MAROON, OLIVE, TEAL, NAVY, SILVER, GRAY, BLACK, WHITE };

    if ( WallsOk && LineOk )
    {
        TronsSim.AddMap( Walls );
        TronsSim.AddMap( Line );

        for (size_t i = 0; i < BodyColors.size(); ++i) {
            CWFRobot* WallFollower = new CWFRobot("Wall follower " + std::to_string(i+1), Walls, kRobotRadius, TrailColors[i], BodyColors[i]);
            TronsSim.AddRobot(WallFollower);
        }

        TronsSim.RunSimulator();
    }
    else
    {
        std::cout << "Could not read one of the map files. Check the paths." << std::endl;
    }

    return 0;
}
