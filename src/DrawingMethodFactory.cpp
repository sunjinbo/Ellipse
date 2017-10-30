/*
 ============================================================================
 Name		: DrawingMethodFactory.cpp
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDrawingMethodFactory implementation
 ============================================================================
 */

#include "DrawingMethodFactory.h"
#include "PinsStringMethod.h"
#include "HypotrochoidMethod.h"
#include "ArchimedesMethod.h"
#include "EmptyMethod.h"

CDrawingMethod* TDrawingMethodFactory::CreateDrawingMethodL( 
				TEllipseDrawingMethods aMethod,
				MDrawingMethodObserver& aObserver, 
				MEllipseEnv& aEllipseEnv,
				const TRect& aEllipseRect )
	{
	CDrawingMethod* method = NULL;
	switch( aMethod )
		{
	    case EEmptyMethod:
            method = CEmptyMethod::NewL( aObserver, aEllipseEnv, aEllipseRect );
            break;
		case EPinsStringMethod:
			method = CPinsStringMethod::NewL( aObserver, aEllipseEnv, aEllipseRect );
			break;
		case EHypotrochoidMethod:
			method = CHypotrochoidMethod::NewL( aObserver, aEllipseEnv, aEllipseRect );
			break;
		case EArchimedesMethod:
			method = CArchimedesMethod::NewL( aObserver, aEllipseEnv, aEllipseRect );
			break;
		default:
			break;
		}
	return method;
	}
