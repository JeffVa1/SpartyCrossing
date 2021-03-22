/**
 * \file Tile.h
 *
 * \author Jeffrey Valentic
 *
 * Base class for any tile in our city
 */

#pragma once
#include "pch.h"
#include <string>
#include <memory>
#include "TypeVisitor.h"
#include "Level.h"

class CGame;

/**
 * Base class for any tile in our city
 */
class CTile : public CItem
{
public:
    /** constructor
      * \param level - the level that this tile belongs to.
      * \param type is a std::shared_ptr<CType> containing bitmap images
      */
    CTile(CLevel* level, std::shared_ptr<CType> type);

    /// How much we offset drawing the tile to the left of the center
    const static int OffsetLeft = 64;

    /// How much we offset drawing the tile above the center
    const static int OffsetDown = 32;

    /** The directory were the images are stored */
    static const std::wstring ImagesDirectory;

    /** The grid spacing in the city */
    static const int GridSpacing = 64;

    ///  Default constructor (disabled)
    CTile() = delete;

    ///  Copy constructor (disabled)
    CTile(const CTile &) = delete;

    /// destructor
    virtual ~CTile();

    /**  Get the file name for this tile image
     * \returns Filename or blank if none */
    std::wstring GetFile() { return mFile; }

    /**  The X location of the center of the tile
    * \returns X location in pixels */
    float GetX() const { return mX; }

    /**  The Y location of the center of the tile
    * \returns Y location in pixels */
    float GetY() const { return mY; }

    /**  Set the item location
    * \param x X location
    * \param y Y location */
    void SetLocation(float x, float y)
    {
        mX = x;
        mY = y;
    }

    /// Draws the Tile
    /// \param graphics - the graphics object to use in draw.
    void Draw(Gdiplus::Graphics *graphics) override;

    ///  Handle updates for animation
    /// \param elapsed The time since the last update
    void Update(double elapsed) {}

    /// \param node the XML item to be loaded.
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /**  Test this item to see if it has been clicked on
    * \param x X location on the aquarium to test
    * \param y Y location on the aquarium to test
    * \return true if clicked on */
    virtual bool HitTest(int x, int y);

    /** Accept a visitor
     * \param visitor The visitor we accept
     */
    void Accept(CTypeVisitor* visitor) override { visitor->VisitTile(this); }

    /** Overrides the base classes collision 
      * \return a bool value if there is a collision
      */
    virtual bool Collision() override;

    /** Gets the Id of this object
      * \return mID a std::wstring
      */
    virtual std::wstring GetId() const override { return mID; }

private:
    // Item location in the aquarium
    float mX = 0; ///< X location for the center of the item
    float mY = 0; ///< Y location for the center of the item

    /// the amount of tiles to repeat in X direction
    int repeatX = 1;

    /// the amount of tiles to repeat in Y direction
    int repeatY = 1;

    /// The image of this tile
    std::unique_ptr<Gdiplus::Bitmap> mItemImage;

    /// The file for this item
    std::wstring mFile;

    /// The game object for this item.
    CLevel* mLevel = nullptr;

    /// Var that determines if player collision w/ tile ends game
    bool mHazardTile = false;

    /// The speed that obstacles will move on this tile.
    float mSpeed = 0;

    /// The ID for a Tile template
    std::wstring mID;
};
