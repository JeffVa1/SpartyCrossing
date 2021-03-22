/**
 * \file LaneMarker.h
 *
 * \author Jeff Valentic
 *
 * Declaration of the CLaneMarker class.
 * The class which contains the lane marker objects
 */

#pragma once
#include "Item.h"
#include "Level.h"

/**
 * Stores information about the yellow lines between lanes
 * and draws them in
 */
class CLaneMarker :
    public CItem
{
public:
    CLaneMarker();

    /// Draws the Lane Marker
    /// \param graphics - the graphics object to use in draw.
    void Draw(Gdiplus::Graphics* graphics) override;

    /// \param node the XML item to be loaded.
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Determines if an object was hit
    /// \param x The X coordinate of the object
    /// \param y The Y coordinate of the object
    /// \returns True if the obect was hit, else false
    virtual bool HitTest(int x, int y) override { return false; }

private:
    /// How much red is in the object
    int mColorR;
    /// How much green is in the object
    int mColorG;
    /// How much blue is in the object
    int mColorB;

    /// How X location of the Lane Marker
    float mX;
    /// How Y location of the Lane Marker
    float mY;
    /// How height of the Lane Marker
    float mHeight;
    /// How width of the Lane Marker
    float mWidth;
    
    /// How many times the Lane Marker drawing should repeat in X direction
    int mRepeatX = 1;
    /// How many times the Lane Marker drawing should repeat in Y direction
    int mRepeatY = 1;
};

