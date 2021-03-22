/**
 * \file Timer.h
 *
 * \author Rohan Singh
 *
 * Declaration of the CTimer class.
 * The class which contains a game timer
 */

#pragma once
#include <string>
#include <ctime>

 /**
 *  Implements a Timer
 */
class CTimer
{
public:
	void Update(double elapsed);
	void Reset();
	void Start();
	/// \param win If Hero is in win condition
	void Stop(bool win);
	std::wstring ConvertTime();
	/**
	* Returns current time
	* \returns mTime The time
	*/
	double GetTime() { return mTime; }

	/**
	* Returns if game was won
	* \returns mWin
	*/
	bool GetWin() const { return mWin; }


private:
	/// Current time
	double mTime = 0;
	/// Is timer running
	bool mRunning = true;
	/// Was the level won
	bool mWin = false;
};

