/**
 * \file CarryObject.h
 *
 * \author Joseph Kasza
 *
 * Base class for any CarryObject in our Game
 */

#pragma once
#include "pch.h"
#include "TypeVisitor.h"
#include <memory>
#include <string>
#include "level.h"
#include "Type.h"

class CGame;
/**
 *  Implements a CarryObject which is derived from CItem
 */
class CCarryObject : public CItem
{
private:
	///Name of this CarryObject
	std::wstring mName;

	/// X location for the center of Item
	float mX = 0;

	/// Y location for the center of Item
	float mY = 0;

	/// Store the original X coordinate so that it can
	/// be picked up / dropped accordingly
	float mInitialX = 0;

	///Bool value of carry object being held by sparty
	bool mIsHeld = false;

	/// The file for this item
	std::wstring mFile;

	/// The image of this CarryObject
	std::shared_ptr<Gdiplus::Bitmap> mItemImage;

	/// The image of this CarryObject not being carried 
	std::shared_ptr<Gdiplus::Bitmap> mNonCarriedImage;

	/// The image of this CarryObject being carried 
	std::shared_ptr<Gdiplus::Bitmap> mCarriedImage;

	///Name of the object this CarryObject eats
	std::wstring mPrey;

	/// The ID for a Tile template
	std::wstring mID;

	///Carried Image for CarryObject
	std::wstring mFile2;

public:
	///Constructor
	CCarryObject(/*CLevel* level*/);

	/// Draws Item
	/// \param graphics Graphics device to draw on
	void Draw(Gdiplus::Graphics* graphics);

	/**  Gets the name of the CarryObject
	  * \returns std::wstring mName
	  */
	std::wstring GetName() {
		return mName;
	}

	/**  Gets the name of the prey for a CarryObject
	  * \returns std::wstring mPrey
	  */
	std::wstring GetPrey() {
		return mPrey;
	}

	/**  Gets the ID for a CarryObject
	  * \returns std::wstring mID
	  */
	std::wstring GetID() { return mID; }

	/** Accept a visitor
	 * \param visitor The visitor we accept 
	 */
	void Accept(CTypeVisitor* visitor) override { visitor->VisitCarryObject(this); }

	/** Test if param x and y are within this objects image
	 * \param x X coordinate to test
	 * \param y Y coordinate to test
	 * \return bool value if x and y are in image
	 */
	bool HitTest(int x, int y);

	/**  Get the file name for this CarryObject image
	 * \returns Filename or blank if none 
	 */
	std::wstring GetFile() { return mFile; }

	///  Handle updates for animation
	/// \param elapsed The time since the last update
	void Update(double elapsed) {}

	/**  Set the item location
	* \param x X location
	* \param y Y location 
	*/
	void SetLocation(float x, float y)
	{
		mX = x;
		mY = y;
	}

	/** The X location of the item
	 * \returns X location in pixels */
	float GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels */
	float GetY() const { return mY; }

	/** Gets the initial x value of this object
	 * \return a float mInitialX
	 */
	float GetInitialX() { return mInitialX; }

	/** Loads in xml information to member variables
	  * \param node is a const std::shared_ptr<xmlnode::CXmlNode>&
	  * \param cargoPNGType is a std::shared_ptr<CType> containing a bitmap of this object image
	  * \param carriedType is a std::shared_ptr<CType> containing a bitmap of this object image being carried
	  */
	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node, std::shared_ptr<CType> cargoPNGType, std::shared_ptr<CType> carriedType);

	/**
	  * Sets mNonCarriedImage to the param image
	  * \param image is std::shared_ptr<Gdiplus::Bitmap>
	  */
	void SetCargoImageBitmap(std::shared_ptr<Gdiplus::Bitmap> image) { mNonCarriedImage = image; }

	/**
	  * Sets mCarriedImage to the param image
	  * \param image is std::shared_ptr<Gdiplus::Bitmap>
	  */
	void SetCarriedImageBitmap(std::shared_ptr<Gdiplus::Bitmap> image) { mCarriedImage = image; }

	/**
	  * Sets mItemImage to mCarriedImage
	  */
	void SetCarryImage() { mItemImage = mCarriedImage; }

	/**
	  * Sets mItemImage to mNonCarriedImage
	  */
	void SetDefaultImage() { mItemImage = mNonCarriedImage; }

	/** Gets the mItemImage of this object
	  * \return the std::shared_ptr<Gdiplus::Bitmap> mItemImage of this object
	  */
	std::shared_ptr<Gdiplus::Bitmap> GetImageBitmap() { return mItemImage; }
};

