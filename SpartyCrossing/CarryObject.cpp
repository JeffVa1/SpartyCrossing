/**
 * \file CarryObject.cpp
 *
 * \author Joseph Kasza
 */

#include "pch.h"
#include "CarryObject.h"
#include "Game.h"
#include "Type.h"

using namespace std;
using namespace Gdiplus;

CCarryObject::CCarryObject()
{
    
}

 void CCarryObject::Draw(Gdiplus::Graphics* graphics)
 {
     auto image = GetImageBitmap();
     if (image != nullptr)
     {
         int currentX = mX;
         int currentY = mY;
         int wid = image->GetWidth();
         int hit = image->GetHeight();

         graphics->DrawImage(image.get(),
                     currentX, currentY,
                     wid, hit);         
     }

 }

bool CCarryObject::HitTest(int x, int y)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image.
    // Subtracting the center makes x, y relative to the center of 
    // the image. Adding half the size makes x, y relative to the top 
    // corner of the image.
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

void CCarryObject::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node, std::shared_ptr<CType> cargoPNGType, std::shared_ptr<CType> carriedType)
{
    if (node->GetAttributeValue(L"image", L"") != L"") {
        
        CCarryObject::SetCargoImageBitmap(cargoPNGType->GetFirstImage());
        CCarryObject::SetCarriedImageBitmap(carriedType->GetFirstImage());

        mItemImage = mNonCarriedImage;

        mID = node->GetAttributeValue(L"id", L"");
        mName = node->GetAttributeValue(L"name", L"");
        mX = float(node->GetAttributeIntValue(L"x", 0));
        mX = mX * 64;
        mInitialX = mX;
        mY = 960;
        mPrey = node->GetAttributeValue(L"eats", L"");
    }
}
