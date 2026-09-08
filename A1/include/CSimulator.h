//-----------------------------------------------------------------------------
// CSimulator.h

// The main class for the simulator. Keeps the loop running, owns the map,
// the renderer and the timer, and drives every robot that has been added.

// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "CRobot.h"
#include "CMap.h"
#include "CRender.h"
#include "CLoopReader.h"
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
class CSimulator
{
    public:
        //---Ctor/Dtor---
        CSimulator( float aTimeStep );
        ~CSimulator();

        //---Configuration---
        bool SetMap( const std::string& aFileName );
        bool AddRobot( CRobot* apRobot );        // the caller keeps ownership
        bool RemoveRobot();                      // not written yet
        bool CheckConfig();                      // not written yet

        const CPose& GetStartPose() const;       // where the map says a robot starts

        //---Running---
        void RunSimulator();

    private:
        void Update();
        void Draw();

        std::vector<CRobot*> mRobots;
        CMap        mMap;
        CRender     mRender;
        CLoopReader mLoopReader;

        float mTimeStep;
        float mCurrentTime;
        int mUpdateCount;
};

#endif
