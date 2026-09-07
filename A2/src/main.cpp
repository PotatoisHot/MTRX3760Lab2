#include "CSimulator.h"
#include "CRobot.h"
#include <iostream>
#include <string>


int main()
{
    CSimulator TronsSim(1);

    TronsSim.SetMap("../../ExampleCode/SimpleWalls.map");
    CRobot* Robot1 = new CRobot("Robot1", 1, {110, 500}, 10);
    TronsSim.AddRobot(Robot1, 1);

    TronsSim.RunSimulator();
    //std::cout << "Debug 1" << std::endl;
    delete Robot1;

    return 0;
}