/**
 * \file Interface.cpp
 *
 * \author Rohan Singh
 */

#include "pch.h"
#include "Interface.h"
#include "Game.h"
using namespace Gdiplus;

/**
* Adds Items to list
* \param graphics Graphical interface
* \param levelNum Level number to be displayed
* \param cargoNames Vector containing names of the cargo
* \param game Pointer to the game object
*/
void CInterface::Draw(Gdiplus::Graphics* graphics, int levelNum, std::vector<std::wstring> cargoNames, CGame* game)
{
	graphics->FillRectangle(&SolidBrush(Color(0, 0, 0)) , Rect(975, 0, 300, 1050));

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font timerFont(&fontFamily, 25);
	SolidBrush yellow(Color(247, 220, 111));
	if (mTimer.GetTime() < 2) 
	{
		Gdiplus::Font titleFont(&fontFamily, 50);
		auto levelStr = L"Begin Level " + std::to_wstring(levelNum);
		graphics->DrawString(levelStr.c_str(),  // String to draw
			-1,         // String length, -1 so it figures it out on its own
			&titleFont,      // The font to use
			PointF(300, 450),   // Where to draw (top left corner)
			&yellow);    // The brush to draw the text with
	}
	std::wstring wtime = mTimer.ConvertTime();
	auto time = wtime.c_str();
	graphics->DrawString(time ,  // String to draw
		-1,         // String length, -1 so it figures it out on its own
		&timerFont,      // The font to use
		PointF(1020, 0),   // Where to draw (top left corner)
		&yellow);    // The brush to draw the text with

	Gdiplus::Font levelFont(&fontFamily, 30);
	SolidBrush blue(Color(52, 152, 219));
	auto levelStr = L"Level " + std::to_wstring(levelNum);
	graphics->DrawString(levelStr.c_str(),  // String to draw
		-1,         // String length, -1 so it figures it out on its own
		&levelFont,      // The font to use
		PointF(1020, 100),   // Where to draw (top left corner)
		&blue);    // The brush to draw the text with

	Gdiplus::Font cargoFont(&fontFamily, 30);
	SolidBrush orange(Color(230, 126, 34));
	int place = 0;

	for (auto name : cargoNames) 
	{
		graphics->DrawString(name.c_str(),  // String to draw
			-1,         // String length, -1 so it figures it out on its own
			&cargoFont,      // The font to use
			PointF(1020, 200 + place * 75),   // Where to draw (top left corner)
			&orange);    // The brush to draw the text with
		place++;
	}
	SolidBrush magenta(Color(255, 0, 204));
	if (mEnd) 
	{
		Gdiplus::Font titleFont(&fontFamily, 50);
		graphics->DrawString(mMessage.c_str(),  // String to draw
			-1,         // String length, -1 so it figures it out on its own
			&titleFont,      // The font to use
			PointF(300, 450),   // Where to draw (top left corner)
			&magenta);    // The brush to draw the text with
		if (mElapsed > mEndTime + 2) 
		{
			game->NextLevel();
		}
	}
}

/**
* Updates the interface
* \param elapsed Updates the time
*/
void CInterface::Update(double elapsed)
{
	mTimer.Update(elapsed);
	mElapsed += elapsed;
}

/**
* Resets the interface
*/
void CInterface::Reset()
{
	mTimer.Reset();
	mElapsed = 0;
	double mEndTime = 0;
	mEnd = false;
}

/**
* Displays end level messages
* \param message Message to be displayed
* \param win Was the level won
*/
void CInterface::LevelEnd(std::wstring message, bool win)
{	
	if (!mEnd) 
	{
		mTimer.Stop(win);
		mEndTime = mElapsed;
		mEnd = true;
		mMessage = message;
	}

}