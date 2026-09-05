#ifndef CROBOT_H
#define CROBOT_H

#include "Geometry.h" // For Vec2D
#include <string>



class CRobot
{
    public:
        CRobot(std::string aName, int aID, Vec2D aStartPosition, int aRadius);
        ~CRobot();

        const std::string GetName() const;
        const int GetID() const;
        const Vec2D GetStartPosition() const;
        const int GetRadius() const;
        const Vec2D GetCurrentPosition() const;

        void Update();

    private:
        std::string mName;
        int mID;
        Vec2D mStartPosition;
        int mRadius;

        Vec2D mCurrentPosition;
};


#endif