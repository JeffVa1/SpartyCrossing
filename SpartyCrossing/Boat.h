/**
 * \file Boat.h
 *
 * \author Jeff Valentic
 *
 * Declaration of the CBoat class.
 * The class which contains the boat objects
 */
#pragma once
#include "Item.h"
#include "Type.h"
#include "Lane.h"

/**
 * Stores information about the boats from the XML File
 * and draws them in
 */
class CBoat :
    public CItem
{
public:

	/// Default constructor (disabled)
	CBoat() = delete;

	/// Copy constructor (disabled)
	CBoat(const CBoat&) = delete;

	/**
	* Draws in a Boat object
	* \param graphics Graphics device to draw on
	*/
	void Draw(Gdiplus::Graphics* graphics);

	/**  Get the file name for this Obstacle image
	 * \returns Filename or blank if none
	 */
	std::wstring GetFile() { return mFile; }

	/**
	* handles updates for animations
	* \param elapsed The time elapsed between the last frame
	*/
	void Update(double elapsed);

	/**  Set the item location
	* \param x X location
	* \param y Y location
	*/
	void SetLocation(float x, float y)
	{
		mX = x;
		mY = y + 32;
	}
	/** The X location of the item
	 * \returns X location in pixels */
	float GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels */
	float GetY() const { return mY; }

	/**
	* Tests whether the boat is in contact with another object
	* \param x The X location of the object
	* \param y The Y location of the object
	* \returns true if hit, else false
	*/
	bool HitTest(int x, int y);

	/**
	* Constructor
	* \param type The type of boat the object will be
	* \param lane The lane this object will go in
	*/
	CBoat(std::shared_ptr<CType> type, std::shared_ptr<CLane> lane);

	/**
	* Sets the image loaded from the Xml File to mItemImage
	* \param image Shared pointer to the image from the XML File
	*/
	virtual void SetImageBitmap(std::shared_ptr<Gdiplus::Bitmap> image) override { mItemImage = image; }

	/**
	* Getter for the mSpeedX variable
	* \returns whatever is inside mSpeedX
	*/
	float GetSpeed() const { return mSpeedX; }

private:
	/// The file for this item
	std::wstring mFile;

	/// ID of the specific item
	std::wstring mID;

	/// The image of this Obstacle
	std::shared_ptr<Gdiplus::Bitmap> mItemImage;

	/// Obstacle speed in the X direction
	double mSpeedX;

	/// The X Location of a boat object
	float mX = 0;

	/// The Y Location of a boat object
	float mY = 0;

	/// Shared pointer to a Lane
	std::shared_ptr<CLane> mLane;
};

