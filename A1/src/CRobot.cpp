#include "CRobot.h"

CRobot::CRobot(std::string aName, int aID, Vec2D aStartPosition, int aRadius)
    : mName(aName), mID(aID), mStartPosition(aStartPosition), mRadius(aRadius),
      mCurrentPosition(aStartPosition)
{
};

CRobot::~CRobot()
{
};

const int CRobot::GetID() const
{
    return mID;
};

const Vec2D CRobot::GetStartPosition() const
{
    return mStartPosition;
};

const int CRobot::GetRadius() const
{
    return mRadius;
};

const std::string CRobot::GetName() const
{
    return mName;
};

const Vec2D CRobot::GetCurrentPosition() const
{
    return mCurrentPosition;
}


void CRobot::Update()
{   // Just for testing now
    if (mCurrentPosition.x < 800)
    {
        mCurrentPosition.x +=1;
    }
    else
    {
        mCurrentPosition.x = mStartPosition.x;
    }
}