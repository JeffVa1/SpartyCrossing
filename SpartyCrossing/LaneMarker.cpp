/**
 * \file LaneMarker.cpp
 *
 * \author Jeff Valentic
 */

#include "pch.h"
#include "LaneMarker.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using namespace Gdiplus;


CLaneMarker::CLaneMarker()
{
}

void CLaneMarker::Draw(Gdiplus::Graphics* graphics)
{
    SolidBrush fillBrush(Color(mColorR, mColorG, mColorB));

    float curX = mX - 50;
    float curY = mY;

    for (int x = 1; x <= mRepeatX; x++) {
        Point start(curX, curY);
        Point end(curX + mWidth, curY + mHeight);
        for (int y = 1; y <= mRepeatY; y++) {
            graphics->FillRectangle(&fillBrush, curX, curY, mWidth, mHeight);
            curY += 64;
        }
        curX += 64;
        curY = mY;
    }

}

/// \param node the XML item to be loaded.
void CLaneMarker::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{

    mX = float(node->GetAttributeDoubleValue(L"x", 0));
    mX = mX * 64;
    mY = float(node->GetAttributeDoubleValue(L"y", 0));
    mY = mY * 64;

    mHeight = float(node->GetAttributeDoubleValue(L"height", 0));
    mHeight = mHeight * 64;
    mWidth = float(node->GetAttributeDoubleValue(L"width", 0));
    mWidth = mWidth * 64;

    mRepeatX = node->GetAttributeIntValue(L"repeat-x", 1);
    mRepeatY = node->GetAttributeIntValue(L"repeat-y", 1);

    wstring colorW = node->GetAttributeValue(L"color", L"0");
    string color(colorW.begin(), colorW.end());
    string delim = ",";

    string colorVec[3];
    size_t pos = 0;

    int ind = 0;
    while ((pos = color.find(delim)) != string::npos) {
        colorVec[ind] = color.substr(0, pos);

        if (color == ",0" || color == "0" || color == "") {
            colorVec[ind] = "0";
        }
        else {
            color.erase(0, pos + 1);
        }
        ind += 1;
    }
    
    colorVec[2] = color;

    mColorR = stoi(colorVec[0]);
    mColorG = stoi(colorVec[1]);
    mColorB = stoi(colorVec[2]);
}