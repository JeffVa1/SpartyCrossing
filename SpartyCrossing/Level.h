/**
 * \file Level.h
 *
 * \author Rohan Singh
 *
 * Declaration of the CLevel class.
 * The class can open and load a level file
 */

#pragma once
#include"XmlNode.h"
#include"Hero.h"
#include"Type.h"
#include "WanderingWolverine.h"
#include"Interface.h"
#include<string>
#include<memory>
#include<vector>
#include<map>

class CBoat;
class CCar;
class CLane;
class CGame;

/**
 *  Implements a Level
 */
class CLevel
{
public:
	/**
      * Loads the level file
      * \param filename The file to be opened and read
      * \param game is the CGame object
	  */
	void Load(const std::wstring& filename, CGame* game);

	/**
      * Loads the type tag
      * \param node The node to be itterated over
      */
	void XmlType(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/**
      * Loads the background tag
      * \param node The node to be itterated over
      */
	void XmlBackground(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/**
      * Loads the river tag
      * \param node The node to be itterated over
      */
	void XmlRiver(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/**
      * Loads the road tag
      * \param node The node to be itterated over
      */
	void XmlRoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/**
      * Loads level items to active game
      * \param game Game being played
      */
	void GetItems(CGame* game);

	/// Get the items
	/// \returns mItems Items
	std::vector<std::shared_ptr<CItem>> GetItems() {
		return mItems;
	}
	/// Get the types
	/// \returns mTypes The types
	std::map < std::wstring, std::shared_ptr<CType>> GetTypes() {
		return mTypes;
	}

	/// Get the hero
	/// \returns hero
	std::shared_ptr<CHero> GetHero() const { return mHero; }

	/**
	* Update function to check for collisions with sparty
	* \param elapsed - double - var that represents how much time has passed.
	*/
	void Update(double elapsed);

	/**
	* RestartLevel function to reset positions of objects
	* when level is failed.
	*/
	void RestartLevel();


	/** Picks up an item if it is carriable
	  * \param x Mouse Cursor X Position
	  * \param y Mouse Cursor Y Position
	  */
	void PickUpItem(int x, int y);

	/** Drops the item the hero is currently holding
	  */
	void DropItem();

	/** Draws the interface for the level
	  * \param graphics is Gdiplus::Graphics*
	  * \param level is a int of the level object
	  */
	void DrawInterface(Gdiplus::Graphics* graphics, int level);

	/** Updates the interface
	  * \param elapsed is a double representing the how much time has passed
	  */
	void UpdateInterface(double elapsed);

	/** Resets the interface
	  */
	void ResetInterface();

	/** Ends the current level
	  */
	void LevelEnd();

	/** Goes to next level
	  */
	void NextLevel();

	/**
	* Returns if game was won
	* \returns mWin from mTimer
	*/
	bool GetWin() const { return mInterface.GetWin(); }

	/** Turns on RoadCheat
	  */
	void ToggleRoadCheat();

	/** Turns on RiverCheat
	  */
	void ToggleRiverCheat();

	/** Turns on WolverineCheat
	  */
	void ToggleWolverineCheat();

private:
	
	/// Map relating an ID to a CType containing images corresponding to that ID
	std::map<std::wstring, std::shared_ptr<CType>> mTypes;

	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;

	/// All Cargo Items
	std::vector<std::shared_ptr<CCarryObject> > mCargo;
	
	/// A vector of floats to represent the cargo positions in the level
	std::vector<float> mCargoPositions;

	/// All lanes
	std::vector<std::shared_ptr<CLane> > mLanes;

	/// Pointer to the hero
	std::shared_ptr<CHero> mHero;

	/// The CCarryObject object that the hero holds
	std::shared_ptr<CCarryObject> mCarriedObject;

	/// A vector containing the CBoat objects in the level
	std::vector<std::shared_ptr<CBoat> > mBoats;

	/// Initial mWolverine is nullptr unless indicated elsewhere
	std::shared_ptr<CWanderingWolverine> mWolverine = nullptr;
	
	/// Interface with timer and cargo
	CInterface mInterface;

	/// Message to be displayed on interface
	std::wstring mMessage = L"Default";
	
	/// Refrence to game
	CGame* mGame;
	
	/// Bool representing if game was won
	bool mWon = false;
	
	/// Bool representing if road cheat is on
	bool mRoadCheat = false;

	/// Bool representing if river cheat is on
	bool mRiverCheat = false;

	/// Bool representing if wolverine cheat is on
	bool mWolverineCheat = false;
};

