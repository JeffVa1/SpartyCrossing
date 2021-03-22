/**
 * \file Interface.h
 *
 * \author Rohan Singh
 *
 * Declaration of the CInterface class.
 * The class which handels game interface display
 */

#pragma once
#include "Timer.h"
#include "DoubleBufferDC.h"
#include <string>
#include <vector>

class CGame;
 /**
 *  Implements an Interface
 */
class CInterface
{
public:
	void Draw(Gdiplus::Graphics* graphics, int levelNum, std::vector<std::wstring> cargoNames, CGame* game);
	void Update(double elapsed);
	void Reset();
	void LevelEnd(std::wstring message, bool win);

	/**
	* Returns if game was won
	* \returns mWin from mTimer
	*/
	bool GetWin() const { return mTimer.GetWin(); }
private:
	/// Game timer
	CTimer mTimer;
	/// Total time that has passed
	double mElapsed = 0;
	/// End time of level
	double mEndTime = 0;
	/// Message
	std::wstring mMessage;
	/// Has level ended;
	bool mEnd = false;
};

