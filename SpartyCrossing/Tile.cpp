/**
 * \file Tile.cpp
 *
 * \author Jeffrey Valentic
 */

#include "pch.h"
#include "Game.h"
#include "Tile.h"
#include "Type.h"

using namespace std;
using namespace Gdiplus;



/// The directory containing the file images
const std::wstring CTile::ImagesDirectory = L"images/";


/**
 *  Distance from center for inside of tiles.
 *
 * Our tiles are a diamond that is 64 pixels tall and 128 pixels
 * wide. So, if we take the distance from the center vertically and 
 * double it, it would be as if we had a 64 by 64 diamond. The 
 * "Manhattan distance" from the center would be no more than 64
 * in that case.
 */
const int InsideTolerance = 64;

CTile::CTile(CLevel* level, std::shared_ptr<CType> type)
{
    mLevel = level;
    CItem::SetImageBitmap(type->GetFirstImage());
}


/**
*  Destructor
*/
CTile::~CTile()
{
}

void CTile::Draw(Gdiplus::Graphics *graphics)
{
    auto image = GetImageBitmap();
    if (image != nullptr)
    {
        int currentX = mX-50;
        for (int i = 0; i < repeatX; i++) {
            int currentY = mY + 64;
            for (int q = 0; q < repeatY; q++) {
                int wid = image->GetWidth();
                int hit = image->GetHeight();

                graphics->DrawImage(image.get(),
                    currentX, currentY - hit,
                    wid + 1, hit + 1);

                currentY += 64;
            }
            currentX += 64;
        }
    }

}

bool CTile::HitTest(int x, int y)
{
    int minX = mX;
    int minY = mY;

    int maxX = mX + (64 * repeatX);
    int maxY = mY + (64* repeatY);
    
    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}

void CTile::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    if (node->GetAttributeValue(L"decor image", L"") != L"") {
        mFile = node->GetAttributeValue(L"decor image", L"");
        mID = node->GetAttributeValue(L"id", L"");
    }
    else {
        
        mID = node->GetAttributeValue(L"id", L"");
        if (mID == L"r001") {
            mHazardTile = true;
        }
        mX = float(node->GetAttributeIntValue(L"x", 0));
        mX = mX * 64;
        mY = float(node->GetAttributeIntValue(L"y", 0));
        mY = mY * 64;
        repeatX = node->GetAttributeIntValue(L"repeat-x", 0);
        repeatY = node->GetAttributeIntValue(L"repeat-y", 0);
    }
}

bool CTile::Collision() 
{
    if (mHazardTile) {
        return true;
    }
    return false;
}