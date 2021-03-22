/**
 * \file Boat.h
 *
 * \author Jeff Valentic
 *
 * Declaration of the CCar class.
 * The class which contains the car objects
 */
#pragma once
#include "Item.h"
#include "Type.h"
#include "Lane.h"

/**
 * Stores information about the boats from the XML File
 * and draws them in
 */
class CCar :
    public CItem
{
public:

	/// Default constructor (disabled)
	CCar() = delete;

	/// Copy constructor (disabled)
	CCar(const CCar&) = delete;

	/**
	* Draws in a car object
	* \param graphics Graphics device to draw on
	*/
	void Draw(Gdiplus::Graphics* graphics);

	/**  Get the file name for this Obstacle image
	 * \returns Filename or blank if none
	 */
	std::wstring GetFile() { return mFile; }

	/**
	* Handle updates for animation
	* \param elapsed Time elapsed from the last frame drawn
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

	/**
	* Sets member variable mSwapTime to parameter passed in
	* \param time Time that we want mSwapTime to equal
	*/
	void SetSwapTime(float time)
	{
		mSwapTime = time;
	}

	/** The X location of the item
	 * \returns X location in pixels */
	float GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels */
	float GetY() const { return mY; }

	/** Name getter for car
	* \returns mName Name of the car */
	std::wstring GetName() const override { return mName; }

	/**
	* Tests whether the car is in contact with another object
	* \param x The X location of the object
	* \param y The Y location of the object
	* \returns true if hit, else false
	*/
	bool HitTest(int x, int y);

	/**
	* Constructor
	* \param type The type of car the object will be
	* \param lane The lane this object will go in
	*/
	CCar(std::shared_ptr<CType> type, std::shared_ptr<CLane> lane);

	/**
	* Sets the image loaded from the Xml File to mItemImage1
	* \param image Shared pointer to the image from the XML File
	*/
	virtual void SetImageBitmap(std::shared_ptr<Gdiplus::Bitmap> image) override { mItemImage1 = image; }

	/**
	* Sets the image loaded from the Xml File to mItemImage2
	* \param image Shared pointer to the image from the XML File
	*/
	virtual void SetImageBitmap2(std::shared_ptr<Gdiplus::Bitmap> image) override { mItemImage2 = image; }

	/**
	* Getter for the mSpeedX variable
	* \returns whatever is inside mSpeedX
	*/
	float GetSpeed() const { return mSpeedX; }

	/**
	* Virtual Function that returns if there was a collision or not
	* \returns true if collision occurred, else false
	*/
	virtual bool Collision() override { return true; }

private:
	/// The file for this item
	std::wstring mFile;

	/// The name for this item
	std::wstring mName;

	/// ID of the specific item
	std::wstring mID;

	/// The image of this Obstacle
	std::shared_ptr<Gdiplus::Bitmap> mItemImage;
	/// The image of this Obstacle
	std::shared_ptr<Gdiplus::Bitmap> mItemImage1;
	/// The image of this Obstacle
	std::shared_ptr<Gdiplus::Bitmap> mItemImage2;

	/// The index of which image is displayed
	int mCurrentImage = 1;

	/// Obstacle speed in the X direction
	double mSpeedX;

	/// The X Location of a car object
	float mX = 0;

	/// The Y Location of a car object
	float mY = 0;

	/// Shared pointer to one of the lanes
	std::shared_ptr<CLane> mLane;

	/// The time between animation swapping for driving
	float mSwapTime = 0.5;

	/// Previous time between animation swapping
	double mPrevTime = 0;
};

