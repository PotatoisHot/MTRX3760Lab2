// It finally runs T_T, It costs me a whole night - Sad and Sleepy Dangaroo T_T zzzz
//-----------------------------------------------------------------------------
// main.cpp
// A5: twenty of each robot at once, with noise on the start pose and wheels.
// Each robot gets the map it senses and starts near where that map says.
//-----------------------------------------------------------------------------

#include "CSimulator.h"
#include "raylib.h"
#include "CWFRobot.h"
#include "CLFRobot.h"
#include "CLoopReader.h"
#include <cstdlib>    // srand
#include <ctime>      // time, to seed it
#include <iostream>
#include <string>
#include <vector>

//---Every robot is a disc of this radius, from the spec.----------------------
static const int kRobotRadius = 15;

//---Twenty of each kind, from the spec.----------------------------------------
static const int kRobotsPerType = 20;

//---Which robots to run. Both on is the A5 submission; switch one off to------
//---watch a single type on its own.-------------------------------------------
static const bool kRunWallFollowers = true;
static const bool kRunLineFollowers = true;

// Custom color for MTRX3760 Lab2 use
#define OLIVE      CLITERAL(Color){ 128, 128, 0, 255 }      // Olive
#define TEAL       CLITERAL(Color){ 0, 128, 128, 255 }      // Teal
#define NAVY       CLITERAL(Color){ 0, 0, 128, 255 }        // Navy
#define SILVER     CLITERAL(Color){ 192, 192, 192, 255 }    // Silver

//-----------------------------------------------------------------------------
int main()
{
    // Seed the random numbers once, so every run is a different run
    srand( unsigned( time( nullptr ) ) );

    // Maps first, simulator second. Objects die in reverse order, so the
    // simulator, which only borrows the maps, is always gone before they are.
    CLoopReader Walls;
    CLoopReader Line;

    bool WallsOk = Walls.ReadFile( "../../ExampleCode/SimpleWalls.map" );
    bool LineOk  = Line.ReadFile(  "../../ExampleCode/SimpleLine.map" );

    CSimulator TronsSim( 0.3f );

    // One colour per robot of each type, trail and body the same for now cause I am too lazy of thinking of other colours :(((
    std::vector<Color> RobotColors = { ORANGE, RED, BROWN, YELLOW, GREEN, BLUE, PURPLE, PINK, SKYBLUE,
        LIME, GOLD, VIOLET, MAROON, OLIVE, TEAL, NAVY, SILVER, GRAY, LIGHTGRAY, WHITE };

    if ( WallsOk && LineOk )
    {
        TronsSim.AddMap( Walls );
        TronsSim.AddMap( Line );

        // The robots live in these vectors, which own them and destroy them
        // when main ends. The simulator is only lent pointers to them, so the
        // vectors must never move their contents: reserve() up front makes
        // sure they never reallocate.
        std::vector<CWFRobot> WallFollowers;
        std::vector<CLFRobot> LineFollowers;
        WallFollowers.reserve( kRobotsPerType );
        LineFollowers.reserve( kRobotsPerType );

        // emplace_back builds each robot in place, so there is no temporary
        // to copy and destroy and each robot is destroyed exactly once
        for ( int i = 0; i < kRobotsPerType; ++i )
        {
            std::string Number = std::to_string( i + 1 );

            if ( kRunWallFollowers )
            {
                WallFollowers.emplace_back( "Wall follower " + Number, Walls, kRobotRadius, RobotColors[i], RobotColors[i] );
                TronsSim.AddRobot( &WallFollowers.back() );
            }

            if ( kRunLineFollowers )
            {
                LineFollowers.emplace_back( "Line follower " + Number, Line, Walls, kRobotRadius, RobotColors[i], RobotColors[i] );
                TronsSim.AddRobot( &LineFollowers.back() );
            }
        }

        TronsSim.RunSimulator();
    }
    else
    {
        std::cout << "Could not read one of the map files. Check the paths." << std::endl;
    }

    return 0;
}
