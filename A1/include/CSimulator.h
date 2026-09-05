/*
Simulator.h

This is the main class for the simulator. It is responsible for keeping the loop running, managing map, robots and watch over the timer.

Written by Dangaroo :D
*/

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "CRobot.h"
#include "CMap.h"
#include "CRender.h"
#include "CLoopReader.h"
#include <iostream>
#include <string>
#include <vector>

class CSimulator
{
    public:
        CSimulator(int aTimeStep);
        ~CSimulator();

        // Configuration/ Setup
        bool SetMap(std::string aFileName);
        bool AddRobot(CRobot* apRobot, int aID);
        bool RemoveRobot(int aID);
        bool CheckConfig(); // Check if the simulator has been set up correctly to start running 

        // Features
        void RunSimulator();
        bool PauseSimulator();
        bool ResumeSimulator();
        bool StopSimulator();

        void CloseSimulator();
    private:
        void Update();

        std::vector<CRobot*> mRobots; // Vector to store robots
        std::vector<int>  mRobotIDs; // Each Robot being added has its own ID, and this vector store these ID for better management
        CMap mMap;
        CRender mRender;
        CLoopReader mLoopReader;

        int mTimeStep;
        int mCurrentTime;
};



#endif