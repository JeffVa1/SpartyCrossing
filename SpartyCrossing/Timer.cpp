/**
 * \file Timer.cpp
 *
 * \author Rohan Singh
 */

#include "pch.h"
#include "Timer.h"

 /**
 * Adds time to timer
 *\param elapsed Time that has passed
 */
void CTimer::Update(double elapsed)
{
	if(mRunning)
	{
		mTime += elapsed;
	}
	
}

/**
* Resets the timer
*/
void CTimer::Reset()
{
	mTime = 0;
	mRunning = true;
	mWin = false;
}

/**
* Allows time to be added to the timer
*/
void CTimer::Start()
{
	mRunning = true;
}

/**
* Stops time from being added to the timer
*/
void CTimer::Stop(bool win)
{
	mWin = win;
	mRunning = false;
}

/**
* Converts the time double to a wstring
* \returns stringTime Time represented as a string
*/
std::wstring CTimer::ConvertTime()
{

	int seconds = mTime-2;
	int minutes = seconds / 60;
	seconds = seconds % 60;
	std::wstring stringTime = std::to_wstring(minutes) + L":" + std::to_wstring(seconds);
	if (mRunning)
	{
		if (seconds < 10)
		{
			stringTime = std::to_wstring(minutes) + L":0" + std::to_wstring(seconds);
		}
		if (mTime < 2)
		{
			stringTime = L"Get Ready!";
		}
	}
	else
	{
		if (mWin)
		{
			stringTime = L"Winner!";
		}
		else
		{
			stringTime = L"Level Complete";
		}
	}
	return stringTime;
}