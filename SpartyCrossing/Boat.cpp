/**
 * \file Boat.cpp
 *
 * \author Jeff Valentic
 */

#include "pch.h"
#include "Boat.h"

using namespace std;
using namespace Gdiplus;

CBoat::CBoat(std::shared_ptr<CType> type, std::shared_ptr<CLane> lane) {
	CBoat::SetImageBitmap(type->GetFirstImage());
	mLane = lane;
	mSpeedX = mLane->GetSpeed();
}

void CBoat::Update(double elapsed)
{
	if (mX <= mLane->GetWidth() && mX >= -256) {
		mX += mSpeedX * elapsed;
	}
	else
	{
		if (mSpeedX > 0) {
			mX = -250;
		}
		if (mSpeedX < 0) {
			mX = mLane->GetWidth();
		}
	}
}

void CBoat::Draw(Gdiplus::Graphics* graphics)
{
	double wid = mItemImage->GetWidth();
	double hit = mItemImage->GetHeight();
	graphics->DrawImage(mItemImage.get(),
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		(float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
}

bool CBoat::HitTest(int x, int y)
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