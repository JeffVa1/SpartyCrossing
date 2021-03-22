/**
 * \file Hero.h
 *
 * \author Noah Homyak
 *
 * Declaration of the CHero class.
 * The class which contains the Hero object
 */
#pragma once

#include "Item.h"
#include "CarryObject.h"
#include "Type.h"


/**
 * Implements the main character object
 */
class CHero : public CItem
{
public:
    /// Default constructor (disabled)
    CHero() = delete;

    /// Copy constructor (disabled)
    CHero(const CHero&) = delete;

    /**
    * Draws in a Hero object
    * \param graphics Graphics device to draw on
    */
    virtual void Draw(Gdiplus::Graphics* graphics) override;

    /// Handle updates for animation
    /// \param elapsed The time since the last update
    void Update(double elapsed);

    /// Loads our hero into a level
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Allows Hero to pickup an item
    /// \param object our hero wants to carry
    void PickUpObject(std::shared_ptr<CCarryObject> object);

    /// Allows Hero to carry an Item
    /// \param object our hero is carrying
    void CarryObject(std::shared_ptr<CCarryObject> object);

    /// Allows Hero to drop the Item
    void DropItem();

    /// Control Hero's movement. 
    void MoveUp();      ///< Moves Hero in the positive Y direction
    void MoveDown();    ///< Moves Hero in the negative Y direction
    void MoveRight();   ///< Moves Hero in the positive X direction
    void MoveLeft();    ///< Moves Hero in the negative X direction

    /**
    * Constructor
    * \param x the X Starting location of the hero
    * \param y the Y Starting location of the hero
    * \param type The type that this hero is
    */
    CHero(int x, int y, std::shared_ptr<CType> type);

    /**
    * Getter for CarryingObject boolean
    * \returns true if hero is carrying object, else false
    */
    bool GetCarryingObject() { return mCarryingObject; }

    /** Accept a visitor
     * \param visitor The visitor we accept
     */
    void Accept(CTypeVisitor* visitor) override { visitor->VisitHero(this); }

    /**
    * Tests whether the hero is in contact with another object
    * \param x The X location of the object
    * \param y The Y location of the object
    * \returns true if hit, else false
    */
    bool HitTest(int x, int y);

    /** The X location of the hero
     * \returns X location in pixels */
    float GetX() const { return mSpartyX; }

    /** The Y location of the hero
    * \returns Y location in pixels */
    float GetY() const { return mSpartyY; }

    /**
    * Sets the mX and mY location of the hero
    * \param x The X location of the hero
    * \param y The Y location of the hero
    */
    void SetPosition(float x, float y);

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
    * Change Hero's speed to match that of the boat
    * \param onBoat True if Hero is on boat, else false
    * \param speed The speed of the boat the hero is on
    */
    void BoatRide(bool onBoat, float speed)
    {
        mOnBoat = onBoat;
        mBoatSpeed = speed;
    }

    /**
    * Sets the image of the hero to the dead version
    */
    void HeroDeath() { mItemImage = mItemImage2; }

    /**
    * Sets the image of the hero to the regluar version
    */
    void ResetImage() { mItemImage = mItemImage1; }

private:
    /// Pointer to a bitmap of the Hero's normal Image
    std::shared_ptr<Gdiplus::Bitmap> mItemImage;
    /// Pointer to a bitmap of the Hero's carrying Image
    std::shared_ptr<Gdiplus::Bitmap> mItemImage1;
    /// Pointer to a bitmap of the Hero's death Image
    std::shared_ptr<Gdiplus::Bitmap> mItemImage2;

    /// Member variables to read from XmlFile (XmlLoad)
    std::wstring mFile;         ///< Name of Default Image File
    std::wstring mHitFile;      ///< Name of Hit Image File
    std::wstring mName;          ///< Name of The Hero

    /// Item Location in the level
    float mSpartyX = 0;      ///< X location for the center of Sparty
    float mSpartyY = 0;      ///< Y location for the center of Sparty

    /// Boolean indicating whether Sparty is carrying an object
    bool mCarryingObject = false;

    /// Boolean that indicates if Hero is on a boat
    bool mOnBoat = false;

    /// The Speed of the boat the Hero is on
    float mBoatSpeed = 0;
};
