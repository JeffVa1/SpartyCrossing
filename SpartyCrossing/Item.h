/**
 * \file Item.h
 *
 * \author Noah Homyak
 *
 * Declaration of the CItem class.
 * The parent class which contains the item objects
 */
#pragma once

#include <memory>
#include <string>
#include "TypeVisitor.h"
#include "XmlNode.h"

class CGame;

/**
 *  Implements an Item
 */
class CItem
{
public:
    /// Draws Item
    /// \param graphics Graphics device to draw on
    virtual void Draw(Gdiplus::Graphics* graphics) {}

    /// Handle updates for animation
    /// \param elapsed The time since the last update
    virtual void Update(double elapsed) {}

    /** Test this item to see if it has been clicked on
     * \param x X location on the level to test
     * \param y Y location on the level to test
     * \return true if clicked on */
    virtual bool HitTest(int x, int y);

    /** The X location of the item
     * \returns X location in pixels */
    virtual float GetX() const { return mX; }

    /** The Y location of the item
    * \returns Y location in pixels */
    virtual float GetY() const { return mY; }

    /** Getter for ID of item
    * * \returns item ID */
    virtual std::wstring GetId() const { return mID; }

    /** Getter for ID of item
    * * \returns item ID */
    virtual std::wstring GetName() const { return L"default"; }

    /** Getter for name of image
    * * \returns image name */
    virtual std::wstring GetImageName() const { return mImageName; }

    /** Getter for width of Item
    * * \returns image width */
    int GetWidth() const { return mItemImage->GetWidth(); }

    /** Getter for height of Item
    * * \returns image height */
    int GetHeight() const { return mItemImage->GetHeight(); }

    /// \param node the XML item to be loaded.
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) {};

    /**
      * Sets mItemImage to the param image
      * \param image is a std::shared_ptr<Gdiplus::Bitmap> for a PNG file
      */
    virtual void SetImageBitmap(std::shared_ptr<Gdiplus::Bitmap> image) { mItemImage = image; }

    /**
      * Sets mItemImage2 to the param image
      * \param image is a std::shared_ptr<Gdiplus::Bitmap> for a PNG file
      */
    virtual void SetImageBitmap2(std::shared_ptr<Gdiplus::Bitmap> image) { mItemImage2 = image; }

    /** Gets mItemImage of this object
      * \return mItemImage as a std::shared_ptr<Gdiplus::Bitmap>
      */
    virtual std::shared_ptr<Gdiplus::Bitmap> GetImageBitmap() { return mItemImage; }

    /**
      * Accepts a CTypeVisitor object
      * \param visitor is CTypeVisitor*
      */
    virtual void Accept(CTypeVisitor* visitor) {}

    /**
      * Checks for object collision
      * \return false unless overridden
      */
    virtual bool Collision() { return false; }

private:
    /// Item Location in the level
    float mX = 0.0;      ///< X location for the center of Item
    float mY = 0.0;      ///< Y location for the center of Item

	/// The image of this item
    std::shared_ptr<Gdiplus::Bitmap> mItemImage;
    /// The image of this item
    std::shared_ptr<Gdiplus::Bitmap> mItemImage2;

    /// The name of the items image.
    std::wstring mImageName;

    /// The ID of the item.
    std::wstring mID;
};

