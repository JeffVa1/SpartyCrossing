/**
 * \file Game.h
 *
 * \author Rohan Singh
 *
 * Declaration of the CGame class.
 * The class which contains the game and levels
 */

#pragma once
#include <vector>
#include <memory>
#include "Level.h"
#include "Item.h"

 /**
 *  Implements a Game
 */
class CGame
{
public:
	CGame();

	/**
      * Adds Items to list
      * \param item Adds item to item vector
      */
	void AddItems(std::shared_ptr<CItem> item);

	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);

	/**
      * Handle a click on the game area
      * \param x X location clicked on
      * \param y Y location clicked on
	  * \return a vector of doubles
      */
	std::vector<double> OnLButtonDown(int x, int y);

	/** Handle updates for animation
      * \param elapsed The time since the last update
      */
	void Update(double elapsed);

	/**
      * Starts new level
      * \param level Level to be played
      */
	void NewGame(int level);

	/** Ends the current game running
	  */
	void EndGame() { mRunning = false; }
	
	/** Stops current level
	  */
	void StopLevel();

	/** Goes to next level
	  */
	void NextLevel();

	/** Get mRunning
	  * \return a bool value in mRunning
	  */
	bool GetRunning() { return mRunning; }

	/// Functions to call on event that a key has been pressed down
	void MoveHeroUp();		///< Called in CChildView when E key pressed
	void MoveHeroDown();	///< Called in CChildView when D key pressed
	void MoveHeroLeft();	///< Called in CChildView when S key pressed
	void MoveHeroRight();	///< Called in CChildView when F key pressed
	
	/** Setter for the pointer to mHero
	  * \param hero is std::shared_ptr<CHero> hero
	  */
	void SetHero(std::shared_ptr<CHero> hero) { mHero = hero; }

	/// Called on the event that the mouse button has been clicked and hits a carriable object
	void InteractWithItem(int x, int y);

	/** Cheat for road tiles
	  */
	void RoadCheat();

	/** Cheat for river tiles
	  */
	void RiverCheat();

	/** Cheat for wolverine object
	  */
	void WolverineCheat();

private:
	/// Scale of window
	float mScale;
	/// X aspect of offest
	float mXOffset;
	/// Y aspect of offset
	float mYOffset;
	/// Vector of items neing used
	std::vector<std::shared_ptr<CItem> > mItems;
	/// Level counter
	int mLevel = 0;
	/// Number of levels
	const static int mNumLevels = 4;
	/// List of levels
	CLevel mLevels[mNumLevels];
	/// Pointer to our Hero object
	std::shared_ptr<CHero> mHero;
	/// Is game running
	bool mRunning = true;
	/// Have the end messages finished
	bool mFinished = false;
};

