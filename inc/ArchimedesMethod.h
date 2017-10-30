/*
 ============================================================================
 Name		: ArchimedesMethod.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CArchimedesMethod declaration
 ============================================================================
 */

#ifndef ARCHIMEDESMETHOD_H
#define ARCHIMEDESMETHOD_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "DrawingMethod.h"

// CLASS DECLARATION

/**
 *  CArchimedesMethod
 * 
 */
class CArchimedesMethod : public CDrawingMethod
    {
public:
    // Constructors and destructor

    /**
     * Destructor.
     */
    virtual ~CArchimedesMethod();

    /**
     * Two-phased constructor.
     */
    static CArchimedesMethod* NewL(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

    /**
     * Two-phased constructor.
     */
    static CArchimedesMethod* NewLC(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

public:
    // from base class CDrawingMethod
    void Draw();
    void Move();

private:

    /**
     * Constructor for performing 1st stage construction
     */
    CArchimedesMethod(            
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

    /**
     * EPOC default constructor for performing 2nd stage construction
     */
    void ConstructL();

private:
    // Member data
    void CalcArchimedesPoints();
    static TInt ModeCallback( TAny* aPtr );
    void DoNextMode();
    
private:
    // Member data
    TPoint iArchimedesPointOne;
    TPoint iArchimedesPointTwo;
    TInt iEllipsePointIndex;
    enum TArchimedesMode
    	{
    	ENormal,
    	EExtra
    	};
    TArchimedesMode iMode;
    CPeriodic* iModePeriodic; // owned.
    };

#endif // ARCHIMEDESMETHOD_H
