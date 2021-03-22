/**
 * \file Hero.cpp
 *
 * \author Noah Homyak
 */

#include "pch.h"
#include <string>
#include "Hero.h"

using namespace std;
using namespace Gdiplus;

/// Pixels per Tile
const int PixelsPerTile = 64;

/// Window Edge for Top side of Window
const int TopEdge = 0;

/// Window Edge for Bottom side of Window
const int BottomEdge = 992;     ///< Window Height - 32

/// Window Edge for Left side of Window
const int LeftEdge = -32;

/// Window Edge for Right side of Window
const int RightEdge = 928;     ///< Window Length - 32

/**
 * Draws the Hero object into the window
 */
void CHero::Draw(Gdiplus::Graphics* graphics)
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
void CHero::Update(double elapsed)
{
    if (mOnBoat)
    {
        mSpartyX += mBoatSpeed * elapsed;
    }
}

/**
* Gets the file name, file hit image, and name of the hero from Xml File
* and sets them to their respective member variables
* \param node that is a constant pointer to the XmlFile we're reading from
*/
void CHero::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    mFile = node->GetAttributeValue(L"image", L"");
    mHitFile = node->GetAttributeValue(L"hit-image", L"");
    mName = node->GetAttributeValue(L"name", L"");

}

/**
* Sets Pickedup item position to the Hero's position
* Sets CarryingObject to true
*/
void CHero::PickUpObject(std::shared_ptr<CCarryObject> object)
{
    object->SetLocation(mSpartyX - 32, mSpartyY - 32);

    mCarryingObject = true;
}

/**
* Allows the Hero to carry an Item
*/
void CHero::CarryObject(std::shared_ptr<CCarryObject> object)
{
    if (mCarryingObject == true)
    {
        object->SetLocation(mSpartyX - 32, mSpartyY - 32);
    }
}

void CHero::DropItem()
{
    mCarryingObject = false;
}

/**
* Moves the Hero upwards in the window
*/
void CHero::MoveUp()
{
    if (mSpartyY - PixelsPerTile >= TopEdge)
    {
        mSpartyY -= PixelsPerTile;
    }
    else
    {
        mSpartyY -= (mSpartyY - TopEdge);
    }
}

/**
* Moves the Hero downwards in the window
*/
void CHero::MoveDown()
{
    if (mSpartyY + PixelsPerTile <= BottomEdge)
    {
        mSpartyY += PixelsPerTile;
    }
    else
    {
        mSpartyY += (BottomEdge - mSpartyY);
    }
}

/**
* Moves the Hero rightwards in the window
*/
void CHero::MoveRight()
{
    if (mSpartyX + PixelsPerTile <= RightEdge)
    {
        mSpartyX += PixelsPerTile;
    }
    else
    {
        mSpartyX += (RightEdge - mSpartyX);
    }
}

/**
* Moves the Hero leftwards in the window
*/
void CHero::MoveLeft()
{
    if (mSpartyX - PixelsPerTile >= LeftEdge)
    {
        mSpartyX -= PixelsPerTile;
    }
    else
    {
        mSpartyX -= (mSpartyX - LeftEdge);
    }
}

/// Constructor
CHero::CHero(int x, int y, std::shared_ptr<CType> type)
{
    mSpartyX = x;
    mSpartyY = y;
    CHero::SetImageBitmap(type->GetFirstImage());
    CHero::SetImageBitmap2(type->GetSecondImage());

    mItemImage = mItemImage1;
}

bool CHero::HitTest(int x, int y)
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

void CHero::SetPosition(float x, float y) {
    mSpartyX = x;
    mSpartyY = y;
}