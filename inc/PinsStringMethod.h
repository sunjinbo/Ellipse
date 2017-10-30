/*
 ============================================================================
 Name		: PinsStringMethod.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CArchimedesMethod declaration
 ============================================================================
 */

#ifndef PINSSTRINGMETHOD_H
#define PINSSTRINGMETHOD_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "DrawingMethod.h"

// CLASS DECLARATION

/**
 *  CArchimedesMethod
 * 
 */
class CPinsStringMethod : public CDrawingMethod
    {
public:
    // Constructors and destructor

    /**
     * Destructor.
     */
    virtual ~CPinsStringMethod();

    /**
     * Two-phased constructor.
     */
    static CPinsStringMethod* NewL(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

    /**
     * Two-phased constructor.
     */
    static CPinsStringMethod* NewLC(            
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
    CPinsStringMethod(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

    /**
     * EPOC default constructor for performing 2nd stage construction
     */
    void ConstructL();

private:
    // New methods
    void InitPinsPoints();

private: 
    // Member data
    TPoint iPinsPointOne;
    TPoint iPinsPointTwo;
    TInt iEllipsePointIndex;
    };

#endif // PINSSTRINGMETHOD_H
