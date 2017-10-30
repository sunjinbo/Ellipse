/*
 ============================================================================
 Name		: DrawingMethod.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDrawingMethod declaration
 ============================================================================
 */

#ifndef DRAWINGMETHOD_H
#define DRAWINGMETHOD_H

#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib

// FORWARD DECLARATIONS
class MEllipseEnv;
class CFbsBitGc;
class CEikonEnv;
class CFont;

// ENUMS
enum TEllipseSceneState
    {
    EEllipseSceneUpdated
    };

// CLASS DECLARATION

/**
 * MDrawingMethod class
 *
 * @since S60 5.0
 */
class MDrawingMethodObserver
    {
public:
    virtual void StateChanged( TInt aNewState ) = 0;
    };

/**
 * CDrawingMethod class
 *
 * @since S60 5.0
 */
class CDrawingMethod : public CActive
    {
public:
    // Destructor
    virtual ~CDrawingMethod();

protected:
    // C++ constructor
    CDrawingMethod( 
            MDrawingMethodObserver& aObserver, 
            MEllipseEnv& aEllipseEnv,
            const TRect& aEllipseRect );

    // Second-phase constructor
    void ConstructL();

public:
    // New methods
    virtual void SetEllipseRect( const TRect& aEllipseRect );
    virtual void Draw() = 0;
    virtual void Move() = 0;

private:
    // From CActive
    // Handle completion
    void RunL();

    // How to cancel me
    void DoCancel();

    // Override to handle leaves from RunL(). Default implementation causes
    // the active scheduler to panic.
    TInt RunError(TInt aError);

protected:
    // Subclass may use these math functions
    TReal Cos( TReal aSrc ) const;
    TReal Sin( TReal aSrc ) const;
    TReal Mod( TReal aSrc, const TReal &aModulus ) const;
    TReal Sqrt( TReal aSrc ) const;
    TReal Square( TReal aSrc ) const;
    void InitializeOrbit( RArray<TPoint>& aEllipsePointList, const TRect& aEllipseRect );
    void LoadMethodNameL( TInt aResourceId );
    void DoDrawMethodName();

private:
    // Function for making the initial request
    void StartL( TTimeIntervalMicroSeconds32 aDelay );
    static TInt TimerCallback( TAny* aPtr );

private:
    enum TDrawingMethodState
        {
        EUninitialized, // Uninitialized
        EInitialized, // Initalized
        EError
        // Error condition
        };
protected:
    // Member data
    TInt iState; // State of the active object
    RTimer iTimer; // Provides async timing service
    MEllipseEnv& iEllipseEnv;
    CFbsBitGc*& iGc; // not owned
    CEikonEnv* iEnv; // not owned
    MDrawingMethodObserver& iObserver;
    TRect iEllipseRect;
    RArray<TPoint> iEllipsePointList;
    CPeriodic* iPeriodic; // owned.
    HBufC* iDrawingMethodName; // owned.
    CFont* iFont; // owned
    };

#endif // DRAWINGMETHOD_H
