/*
 ============================================================================
 Name		: EmptyMethod.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CArchimedesMethod declaration
 ============================================================================
 */

#ifndef EMPTYMETHOD_H
#define EMPTYMETHOD_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "DrawingMethod.h"

// CLASS DECLARATION

/**
 *  CArchimedesMethod
 * 
 */
class CEmptyMethod : public CDrawingMethod
    {
public:
    // Constructors and destructor

    /**
     * Destructor.
     */
    virtual ~CEmptyMethod();

    /**
     * Two-phased constructor.
     */
    static CEmptyMethod* NewL(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

    /**
     * Two-phased constructor.
     */
    static CEmptyMethod* NewLC(            
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
    CEmptyMethod(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

    /**
     * EPOC default constructor for performing 2nd stage construction
     */
    void ConstructL();

    };

#endif // EMPTYMETHOD_H
