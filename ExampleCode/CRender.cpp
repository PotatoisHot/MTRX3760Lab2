//-----------------------------------------------------------------------------
// CRender.cpp
//
// Implementation of the raylib wrapper. The :: prefix on the raylib calls says
// "the global one", distinguishing raylib's DrawCircle from our member function
// of the same name.
//-----------------------------------------------------------------------------

#include "CRender.h"

//-----------------------------------------------------------------------------
CRender::CRender()
    :
        mScreenWidth( kMaxScreenWidth ),
        mScreenHeight( kMaxScreenHeight )
{
    InitWindow( mScreenWidth, mScreenHeight, "Watashi wa Dangaroo desu" );
    SetTargetFPS( 60 );
}

int CRender::GetScreenWidth() const
{
    return mScreenWidth;
}

int CRender::GetScreenHeight() const
{
    return mScreenHeight;
}

bool CRender::WindowShouldClose()
{
    bool Result = ::WindowShouldClose();
    return Result;
}

void CRender::CloseWindow()
{
    ::CloseWindow();
}

void CRender::BeginDrawing()
{
    ::BeginDrawing();
    ::ClearBackground( BLACK );
}

void CRender::EndDrawing()
{
    ::EndDrawing();
}

void CRender::DrawCircle( Vec2D aPosition, int aRadius, Color aColor )
{
    ::DrawCircle( aPosition.x, aPosition.y, aRadius, aColor );
}

void CRender::DrawLine( Vec2D aStart, Vec2D aEnd, float aThickness, Color aColor )
{
    Vector2 Start = { aStart.x, aStart.y };
    Vector2 End = { aEnd.x, aEnd.y };

    ::DrawLineEx( Start, End, aThickness, aColor );
};

void CRender::DrawLoop( const std::vector<Vec2D>& aVertices, float aThickness, Color aColor )
{
    if( !aVertices.empty() )
    {
        // Start from the last vertex so the first edge drawn closes the loop.
        Vec2D Previous = aVertices.back();
        for( const Vec2D& Vertex : aVertices )
        {
            DrawLine( Previous, Vertex, aThickness, aColor );
            Previous = Vertex;
        }
    }
};

void CRender::DrawTrail( const std::vector<Vec2D>& aTrail, float aThickness, Color aColor )
{
    if( !aTrail.empty() )
    {
        // Start from the first vertex so the trail is drawn in order.
        Vec2D Previous = aTrail.front();
        for( const Vec2D& Vertex : aTrail )
        {
            DrawLine( Previous, Vertex, aThickness, aColor );
            Previous = Vertex;
        }
    }
};