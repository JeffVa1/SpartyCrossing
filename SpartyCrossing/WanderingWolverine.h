/**
 * \file WanderingWolverine.h
 *
 * \author Jeff Valentic
 *
 * Declaration of the CWanderingWolverine class.
 * The class which contains the WanderingWolverine objects
 */

#pragma once
#include "Item.h"
#include "Type.h"
/**
  * Implements the Wandering Wolverine obstacle in the game.
  */
class CWanderingWolverine :
    public CItem
{
public:
    /// Default constructor (disabled)
    CWanderingWolverine() = delete;

    /// Copy constructor (disabled)
    CWanderingWolverine(const CWanderingWolverine&) = delete;

    /**
      * Draw function to implement visuals for wolverine
      * \param graphics - the graphics engine to use in drawing.
      */
    void Draw(Gdiplus::Graphics* graphics);

    /// Handle updates for animation
    /// \param elapsed The time since the last update
    void Update(double elapsed);

    /// Loads our hero into a level
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Control Wolverine's movement. 
    void MoveUp();      ///< Moves Wolverine in the positive Y direction
    void MoveDown();    ///< Moves Wolverine in the negative Y direction
    void MoveRight();   ///< Moves Wolverine in the positive X direction
    void MoveLeft();    ///< Moves Wolverine in the negative X direction

    /**Constructor
      * \param type is a std::shared_ptr<CType>
      */
    CWanderingWolverine(std::shared_ptr<CType> type);

    /**
      * HitTest function to check if item overlaps with argument positions
      * \param x - the x position to check
      * \param y - the y position to check
      * \return bool value if coordinates are in image
      */
    bool HitTest(int x, int y);

    /** The X location of the item
      * \returns X location in pixels */
    float GetX() const { return mWolverineX; }

    /** The Y location of the item
      * \returns Y location in pixels */
    float GetY() const { return mWolverineY; }

    /** Sets mItemImage
      * \param image is std::shared_ptr<Gdiplus::Bitmap>
      */
    virtual void SetImageBitmap(std::shared_ptr<Gdiplus::Bitmap> image) override { mItemImage = image; }

    /** Test if there was a collision
      * \returns a bool value if there was a collision 
      */
    virtual bool Collision() override { return true; }

    /**Resets wolverine's position
      */
    void ResetPosition();

    /** Gets the Id for the object
      * \return mID a std::wstring
      */
    virtual std::wstring GetId() const override { return mId; }

private:
    /// Pointer to a bitmap of the Sparty Image
    std::shared_ptr<Gdiplus::Bitmap> mItemImage;

    /// Member variables to read from XmlFile (XmlLoad)
    std::wstring mFile;         ///< Name of Default Image File
    std::wstring mName;          ///< Name of The Hero

    /** Id for this object
      */
    std::wstring mId;

    /// Item Location in the level
    float mWolverineX = 0;      ///< X location for the center of Sparty
    float mWolverineY = 0;      ///< Y location for the center of Sparty

    /** mTopBound of object set to 0
      */
    float mTopBound = 0;

    /** mBottomBound of object set to 0
      */
    float mBottomBound = 0;

    /** mLeftBound of object set to 0
      */
    float mLeftBound = 0;

    /** mRightBound of object set to 0
      */
    float mRightBound = 0;

    /** mStartX of object set to 0
      */
    float mStartX = 0;

    /** mStartY of object set to 0
      */
    float mStartY = 0;
};

