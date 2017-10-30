/*
 ============================================================================
 Name		: HypotrochoidMethod.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CHypotrochoidMethod declaration
 ============================================================================
 */

#ifndef HYPOTROCHOIDMETHOD_H
#define HYPOTROCHOIDMETHOD_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "DrawingMethod.h"

// CLASS DECLARATION

/**
 *  CHypotrochoidMethod
 * 
 */
class CHypotrochoidMethod : public CDrawingMethod
    {
public:
    // Constructors and destructor

    /**
     * Destructor.
     */
    virtual ~CHypotrochoidMethod();

    /**
     * Two-phased constructor.
     */
    static CHypotrochoidMethod* NewL(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

    /**
     * Two-phased constructor.
     */
    static CHypotrochoidMethod* NewLC(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

public:
    // from base class CDrawingMethod
    void SetEllipseRect( const TRect& aEllipseRect );
    void Draw();
    void Move();

private:

    /**
     * Constructor for performing 1st stage construction
     */
    CHypotrochoidMethod(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

    /**
     * EPOC default constructor for performing 2nd stage construction
     */
    void ConstructL();

private:
    // New methods
    void Initialize();

private:
    // Member data
    TInt iFocalLength;
    TInt iEllipsePointIndex;
    TRect iBigCircleRect;
    TRect iSmallCircleRect;
    RArray<TPoint> iSmallCirclePointList;
    };

#endif // HYPOTROCHOIDMETHOD_H
