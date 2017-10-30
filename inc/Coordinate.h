/*
 ============================================================================
 Name		: Coordinate.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCoordinate declaration
 ============================================================================
 */

#ifndef COORDINATE_H
#define COORDINATE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

class CEikonEnv;
class MEllipseEnv;

// CLASS DECLARATION

/**
 *  CCoordinate
 * 
 */
class CCoordinate : public CBase
    {
public:
    // Constructors and destructor

    /**
     * Destructor.
     */
    virtual ~CCoordinate();

    /**
     * Two-phased constructor.
     */
    static CCoordinate* NewL( 
            MEllipseEnv& aEnv, 
            const TRect& aRect
            );

    /**
     * Two-phased constructor.
     */
    static CCoordinate* NewLC( 
            MEllipseEnv& aEnv, 
            const TRect& aRect 
            );

public:
    // New functions
    void Draw();
    void SetRect( const TRect& aRect );

private:

    /**
     * Constructor for performing 1st stage construction
     */
    CCoordinate( 
            MEllipseEnv& aEnv, 
            const TRect& aRect 
            );

    /**
     * EPOC default constructor for performing 2nd stage construction
     */
    void ConstructL();

private:
    // Member data
    CFbsBitGc*& iGc; // not owned
    CEikonEnv* iEnv; // not owned
    CFont* iFont;
    TRect iCoordinateRect;
    };

#endif // COORDINATE_H
