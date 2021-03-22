/**
 * \file Boat.h
 *
 * \author Noah Homyak
 *
 * Declaration of the CLane class.
 * The class which contains the Lane tile objects
 */

#pragma once

#include <vector>
#include <memory>
#include "Item.h"

class CBoat;
class CCar;

/**
 * Stores information about the yellow lines between lanes
 * and draws them in
 */
class CLane
{
public:
	/**
	 * Constructor (creating a lane in the game)
	 * Takes in an obstacle that will belong to that lane
	 * \param y The Y coordinate of the middle of the Lane
	 * \param speed The speed that vehicles go in the Lane
	 * \param width The width of the Lane
	 */
	CLane(float y, float speed, float width);

	/**
	 * Getter for the member variable mSpeed
	 * \returns The mSpeed variable
	 */
	float GetSpeed() { return mSpeed; }

	/**
	 * Setter for the member variable mLaneType
	 * \param type The type that we assign to mLaneType
	 */
	void SetLaneType(std::string type) { mLaneType = type; }

	/**
	 * Pushes back a vehicle to our vector of vehicles
	 * \param boat A boat that goes in our vector of vehicles
	 */
	void AddVehicle(std::shared_ptr<CItem> boat) { mVehicles.push_back(boat); }

	/**
	 * Getter for the member variable mWidth
	 * \returns The mWidth variable
	 */
	float GetWidth() { return mWidth; }

private:
	/// Vector that keeps tracks of the lanes
	std::vector<std::shared_ptr<CItem> > mVehicles;

	/// String for the type of Lane
	std::string mLaneType;

	/// The Y location of the middle of the Lane
	float mY = 0;

	/// The width of the Lane
	float mWidth = 0;

	/// The Speed of the Vehicle in the Lane
	float mSpeed = 0;
};

