/**
 * \file WanderingWolverine.cpp
 *
 * \author Jeff Valentic
 */

#include "pch.h"
#include "WanderingWolverine.h"
#include <string>
#include <stdlib.h>

using namespace std;
using namespace Gdiplus;

/// Pixels per Tile
const int PixelsPerTile = 64;

/// Window Edge for Top side of Window
const int TopEdge = 32;

/// Window Edge for Bottom side of Window
const int BottomEdge = 992;     ///< Window Height - 32

/// Window Edge for Left side of Window
const int LeftEdge = 32;

/// Window Edge for Right side of Window
const int RightEdge = 1024;     ///< Window Length - 32

const int InsideTolerance = 64;

void CWanderingWolverine::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();
    graphics->DrawImage(mItemImage.get(),
        float(GetX() - wid / 2), float(GetY() - hit / 2),
        (float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
}

/**
 * Handle updates for animation
 * \param elapsed The time since the last update
 */
void CWanderingWolverine::Update(double elapsed)
{
    int moveCheck = rand() % 100 + 1;     // moveCheck in the range 1 to 100

    if (moveCheck >= 90) {
        int moveDirection = rand() % 100 + 1;   // moveDirection in the range 1 to 100

        if (moveDirection <= 15) {
            MoveUp();
        }
        if (moveDirection > 15 && moveDirection <= 30) {
            MoveDown();
        }
        if (moveDirection > 30 && moveDirection <= 65) {
            MoveRight();
        }
        if (moveDirection > 65 && moveDirection <= 100) {
            MoveLeft();
        }
    }
}

/**
* Gets the file name, file hit image, and name of the hero from Xml File
* and sets them to their respective member variables
* \param node that is a constant pointer to the XmlFile we're reading from
*/
void CWanderingWolverine::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    mFile = node->GetAttributeValue(L"image", L"");
    mName = node->GetAttributeValue(L"name", L"");

    mWolverineX = float(node->GetAttributeDoubleValue(L"x", 0)) * 64;
    mWolverineY = float(node->GetAttributeDoubleValue(L"y", 0)) * 64;

    mStartX = mWolverineX;
    mStartY = mWolverineY;

    mTopBound = float(node->GetAttributeDoubleValue(L"y-min", 0)) * 64;
    mBottomBound = float(node->GetAttributeDoubleValue(L"y-max", 0)) * 64;
    mLeftBound = float(node->GetAttributeDoubleValue(L"x-min", 0)) * 64;
    mRightBound = float(node->GetAttributeDoubleValue(L"x-max", 0)) * 64;

    mId = node->GetAttributeValue(L"id", L"");
}

/**
* Moves the Hero upwards in the window
*/
void CWanderingWolverine::MoveUp()
{
    if (mWolverineY - PixelsPerTile >= mTopBound)
    {
        mWolverineY -= PixelsPerTile;
    }
    else
    {
        mWolverineY -= (mWolverineY - mTopBound);
    }
}

/**
* Moves the Hero downwards in the window
*/
void CWanderingWolverine::MoveDown()
{
    if (mWolverineY + PixelsPerTile <= mBottomBound)
    {
        mWolverineY += PixelsPerTile;
    }
    else
    {
        mWolverineY += (mBottomBound - mWolverineY);
    }
}

/**
* Moves the Hero rightwards in the window
*/
void CWanderingWolverine::MoveRight()
{
    if (mWolverineX + PixelsPerTile <= RightEdge)
    {
        mWolverineX += PixelsPerTile;
    }
    else
    {
        mWolverineX += (RightEdge - mWolverineX);
    }
}

/**
* Moves the Hero leftwards in the window
*/
void CWanderingWolverine::MoveLeft()
{
    if (mWolverineX - PixelsPerTile >= LeftEdge)
    {
        mWolverineX -= PixelsPerTile;
    }
    else
    {
        mWolverineX -= (mWolverineX - LeftEdge);
    }
}

/// Constructor
CWanderingWolverine::CWanderingWolverine(std::shared_ptr<CType> type)
{
    CWanderingWolverine::SetImageBitmap(type->GetFirstImage());
}

bool CWanderingWolverine::HitTest(int x, int y)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = mItemImage->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mItemImage->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;
    }
}

void CWanderingWolverine::ResetPosition()
{
    mWolverineX = mStartX;
    mWolverineY = mStartY;
}