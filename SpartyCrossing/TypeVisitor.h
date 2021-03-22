/**
 * \file TypeVisitor.h
 *
 * \author Joseph Kasza
 *
 * Declaration of the CTypeVisitor class.
 * The class which contains the TypeVisitor objects
 */

#pragma once

// Forward references to all carry object types
class CCarryObject;
class CTile;
class CItem;
class CHero;

/**
 * Visitor Class for Type
 */
class CTypeVisitor
{
public:
	virtual ~CTypeVisitor() {}

	/** Visit a CCarryObject object
	 * \param carryObject CarryObject we are visiting */
	virtual void VisitCarryObject(CCarryObject* carryObject) {}

	/** Visit a CTile object
	 * \param tile Tile we are visiting */
	virtual void VisitTile(CTile* tile) {}

	/** Visit a CItem object
	 * \param item Item we are visiting */
	virtual void VisitItem(CItem* item) {}

	/** Visit a CHero object
	 * \param hero Hero we are visiting */
	virtual void VisitHero(CHero* hero) {}
};

