/**
 * \file CarryObject.h
 *
 * \author Joseph Kasza
 *
 * Type class that store bitmap images for objects in our Game
 */
#pragma once

#include <vector>
#include <memory>
#include <string>

/**
 * Stores type information for Xml loading
 */
class CType
{
public:
	/** Adds an image to vector mImage
	  * \param filename is std::wstring filename
	  */
	void AddImage(std::wstring filename);

	/** Gets the first image in the vector mImages
	  * \return a std::shared_ptr<Gdiplus::Bitmap>
	  */
	std::shared_ptr<Gdiplus::Bitmap> GetFirstImage() {
		return mImages[0];
	}

	/** Gets the second image in the vector mImages
	  * \return a std::shared_ptr<Gdiplus::Bitmap>
	  */
	std::shared_ptr<Gdiplus::Bitmap> GetSecondImage() {
		return mImages[1];
	}

	/** Sets mName to name
	  * \param name is std::wstring
	  */
	void SetName(std::wstring name) { mName = name; }

	/**Gets mName
	  * \return mName a std::wstring 
	  */
	std::wstring GetName() { return mName; }

private:
	/// mImages contains the various image bitmaps for an object
	std::vector<std::shared_ptr<Gdiplus::Bitmap>> mImages;

	/// mName is the name of the object
	std::wstring mName;
};

