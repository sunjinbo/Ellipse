/* ====================================================================
 * File: BmpUtils.h
 * Created: 03/31/11
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BMPUTILS_H
#define C_BMPUTILS_H

// INCLUDE FILES
#include <e32base.h>
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CBmpUtils class
*
* @since S60 5.0
*/
class CBmpUtils : public CBase
    {
public: // Constructor and destructor

    static CBmpUtils* NewL( const TDesC& aFileName, TInt aFrom, TInt aTo );
    virtual ~CBmpUtils();

public: // New functions

    void SetSize( TInt aIndex, TSize aSize );
    void SetSizeAndRotation( TInt aIndex, TSize aSize, TInt aAngle );
    CFbsBitmap* Bitmap( TInt aIndex ) const;

protected: // Default destructor

    CBmpUtils( TInt aFrom, TInt aTo );
    void ConstructL( const TDesC& aFileName );

private: // New function
    void LoadBitmapL ();

protected: // Data members
    TInt iFrom;
    TInt iTo;
    HBufC* iFileName; // Own
    RPointerArray<CFbsBitmap>  iBitmapArray;
    };

#endif // C_BMPUTILS_H

// End of File
