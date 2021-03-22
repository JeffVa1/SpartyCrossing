/**
 * \file Game.cpp
 *
 * \author Rohan Singh
 */

#include "pch.h"
#include "Game.h"

using namespace std;
using namespace Gdiplus;

/// Game area in virtual pixels
const static int Width = 1224;

/// Game area height in virtual pixels
const static int Height = 1024;


CGame::CGame()
{
    wstring l0 = L"levels/level0.xml";
    wstring l1 = L"levels/level1.xml";
    wstring l2 = L"levels/level2.xml";
    wstring l3 = L"levels/level3.xml";

    mLevels[0].Load(l0, this);
    mLevels[1].Load(l1, this);
    mLevels[2].Load(l2, this);
    mLevels[3].Load(l3, this);

    this->NewGame(1);
}

/**
 * Draw the game area
 * \param graphics The GDI+ graphics context to draw on
 * \param width Width of the client window
 * \param height Height of the client window
 */
void CGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
    // Fill the background with black
    SolidBrush brush(Color::Black);
    graphics->FillRectangle(&brush, 0, 0, width, height);

    //
    // Automatic Scaling
    //
    float scaleX = float(width) / float(Width);
    float scaleY = float(height) / float(Height);
    mScale = min(scaleX, scaleY);

    // Ensure it is centered horizontally
    mXOffset = (float)((width - Width * mScale) / 2);

    // Ensure it is centered vertically
    mYOffset = (float)((height - Height * mScale) / 2);

    graphics->TranslateTransform(mXOffset, mYOffset);
    graphics->ScaleTransform(mScale, mScale);

    // From here on you are drawing virtual pixels

    Region myRegion(Rect(-32, 0, Width, Height));
    graphics->SetClip(&myRegion, CombineModeReplace);
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
    graphics->ResetClip();
    mLevels[mLevel].DrawInterface(graphics, mLevel);

    if (mRunning != true) 
    {
        mLevels[mLevel].LevelEnd();
    }

    
}

void CGame::NewGame(int level)
{
    mRunning = true;
    mFinished = false;
    mItems.clear();
    mLevel = level;
    mLevels[mLevel].GetItems(this);
    mLevels[mLevel].ResetInterface();
    mLevels[mLevel].RestartLevel();

}

vector<double> CGame::OnLButtonDown(int x, int y)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;

    vector<double> mousePos;
    mousePos.push_back(oX);
    mousePos.push_back(oY);

    return mousePos;
}

void CGame::Update(double elapsed)
{
    for (auto item : mLevels[mLevel].GetItems())
    {
        item->Update(elapsed);
    }
    mLevels[mLevel].UpdateInterface(elapsed);
    mHero->Update(elapsed);
    mLevels[mLevel].Update(elapsed);
}

void CGame::AddItems(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

/**
* Ends current level and begins new level
*/
void CGame::StopLevel()
{
    mRunning = false;
}

void CGame::NextLevel()
{
    if (mLevels[mLevel].GetWin())
    {
        if (mLevel < 3)
        {
            mLevel++;
        }

    }
    NewGame(mLevel);
}



/** 
* Calls function for MoveUp() in hero class so it can access mHeroX
* and mHeroY variables and change them accordingly
*/
void CGame::MoveHeroUp()
{
    if (mRunning == true)
    {
        mHero->MoveUp();
    }

}

/**
* Calls function for MoveDown() in hero class so it can access mHeroX
* and mHeroY variables and change them accordingly
*/
void CGame::MoveHeroDown()
{
    if (mRunning == true) 
    {
        mHero->MoveDown();
    }

}

/**
* Calls function for MoveLeft() in hero class so it can access mHeroX
* and mHeroY variables and change them accordingly
*/
void CGame::MoveHeroLeft()
{
    if (mRunning == true) 
    {
        mHero->MoveLeft();
    }

}

/**
* Calls function for MoveRight() in hero class so it can access mHeroX
* and mHeroY variables and change them accordingly
*/
void CGame::MoveHeroRight()
{
    if (mRunning == true) 
    {
        mHero->MoveRight();
    }

}


/**
* Determines if item can be picked up or dropped and calls function in
* CLevel to interact with carriable objects accordingly
* \param x The X coordinate of the mouse click
* \param y The Y coordinate of the mouse click
*/
void CGame::InteractWithItem(int x, int y)
{
    if (mHero->GetCarryingObject() == false)
    {
        int dx = mHero->GetX() - x;
        int dy = mHero->GetY() - y;
        if (sqrt(dx * dx + dy * dy) < 500) {
            mLevels[mLevel].PickUpItem(x, y);
        }
        
    }
    else
    {
        mLevels[mLevel].DropItem();
    }
}

void CGame::RoadCheat() {
    mLevels[mLevel].ToggleRoadCheat();
}

void CGame::RiverCheat() {
    mLevels[mLevel].ToggleRiverCheat();
}

void CGame::WolverineCheat() {
    mLevels[mLevel].ToggleWolverineCheat();
}