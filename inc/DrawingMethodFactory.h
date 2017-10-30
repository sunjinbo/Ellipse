/*
 ============================================================================
 Name		: DrawingMethodFactory.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDrawingMethodFactory declaration
 ============================================================================
 */

#ifndef DRAWINGMETHODFACTORY_H
#define DRAWINGMETHODFACTORY_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "Ellipse.hrh"

class CDrawingMethod;
class MDrawingMethodObserver;
class MEllipseEnv;

// CLASS DECLARATION

/**
 *  CDrawingMethodFactory
 * 
 */
class TDrawingMethodFactory
	{
public:
	// New function
	static CDrawingMethod* CreateDrawingMethodL( 
			TEllipseDrawingMethods aMethod,
			MDrawingMethodObserver& aObserver, 
			MEllipseEnv& aEllipseEnv,
			const TRect& aEllipseRect
			);
	};

#endif // DRAWINGMETHODFACTORY_H
