//-----------------------------------------------------------------------------
// CSimulator.h
// Runs the show. Owns the renderer and the clock, draws every map it is given
// and steps every robot. Robots sense their own maps; this only draws them.
//
// Written by Dangaroo :D
//-----------------------------------------------------------------------------

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "CRobot.h"
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

        //---Setup---
        // Maps and robots stay owned by the caller and must outlive this.
        bool AddMap( const CLoopReader& aMap );   // must already be read in
        bool AddRobot( CRobot* apRobot );
        bool RemoveRobot();                        // not written yet
        bool CheckConfig();                        // at least one map and one robot

        //---Running---
        void RunSimulator();

    private:
        void Update();
        void Draw();

        std::vector<const CLoopReader*> mMaps;
        std::vector<CRobot*>            mRobots;
        CRender mRender;

        float mTimeStep;
        float mCurrentTime;
        int   mUpdateCount;
};

#endif
