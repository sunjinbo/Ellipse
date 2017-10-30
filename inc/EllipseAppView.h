/*
 ============================================================================
 Name		: EllipseAppView.h
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __ELLIPSEAPPVIEW_h__
#define __ELLIPSEAPPVIEW_h__

// INCLUDES
#include <coecntrl.h>
#include <eikmobs.h>
#include <aknstyluspopupmenu.h>
#include "EllipseEnv.h"
#include "DrawingMethod.h"
#include "Ellipse.hrh"

// FORWARD DECLARATIONS
class CCoordinate;
class CEllipseAppUi;
class CBmpUtils;

// CLASS DECLARATION
class CEllipseAppView : public CCoeControl
	, public MDrawingMethodObserver
	, public MEikMenuObserver
	, public MEllipseEnv
    {
public:
    // New methods

    /**
     * NewL.
     * Two-phased constructor.
     * Create a CEllipseAppView object, which will draw itself to aRect.
     * @param aRect The rectangle this view will be drawn to.
     * @return a pointer to the created instance of CEllipseAppView.
     */
    static CEllipseAppView* NewL(CEllipseAppUi& aAppUi, const TRect& aRect);

    /**
     * NewLC.
     * Two-phased constructor.
     * Create a CEllipseAppView object, which will draw itself
     * to aRect.
     * @param aRect Rectangle this view will be drawn to.
     * @return A pointer to the created instance of CEllipseAppView.
     */
    static CEllipseAppView* NewLC(CEllipseAppUi& aAppUi, const TRect& aRect);

    /**
     * ~CEllipseAppView
     * Virtual Destructor.
     */
    virtual ~CEllipseAppView();

public:
    // New functions
    void SetDrawingMethodL( TEllipseDrawingMethods aMethod );
    TEllipseDrawingMethods DrawingMethod() const;

public:
    // from MEllipseEnv
    CFbsBitGc*& Gc();
    CEikonEnv* EikonEnv();
    TRect ViewRect();

public:
    // Functions from base classes

    /**
     * From CoeControl, SizeChanged.
     * Called by framework when the view size is changed.
     */
    void SizeChanged();

    /**
     * From CoeControl, HandlePointerEventL.
     * Called by framework when a pointer touch event occurs.
     * Note: although this method is compatible with earlier SDKs, 
     * it will not be called in SDKs without Touch support.
     * @param aPointerEvent the information about this event
     */
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    void HandleResourceChange( TInt aType );

private:
    // MDrawingMethodObserver
    void StateChanged( TInt aNewState );
    
private:
    // MEikMenuObserver
    void ProcessCommandL( TInt aCommandId );
    void SetEmphasis( CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/ ) {}
    
private:
    // Constructors

    /**
     * ConstructL
     * 2nd phase constructor.
     * Perform the second phase construction of a
     * CEllipseAppView object.
     * @param aRect The rectangle this view will be drawn to.
     */
    void ConstructL(const TRect& aRect);

    /**
     * CEllipseAppView.
     * C++ default constructor.
     */
    CEllipseAppView(CEllipseAppUi& aAppUi);

private:
    // New functions
    void CreateBmpBufferL();
    void ReleaseBmpBuffer();
    static TInt TimerCallback( TAny* aPtr );
    void Stop();
    void DoFrame();
    static TInt IdleCallback( TAny* aPtr );
    void DoStart();
    void CreatePopupMenuL( const TPoint& aPos );
    TRect EllipseRect() const;
    void DoDrawBackground();
    void ScaleBitmap();
    
private:
    // Member data
    CEllipseAppUi& iAppUi;
    CFbsBitmap* iBitmap; // owned
    CFbsBitmapDevice* iBitmapDevice; // owned
    CFbsBitGc* iBitmapGc; // owned
    CPeriodic* iPeriodic; // owned
    CCoordinate* iCoordinate; // owned
    CDrawingMethod* iDrawingMethod; // owned
    CIdle* iIdle; // owned.
    CAknStylusPopUpMenu* iPopupMenu; // owned
    CBmpUtils* iBmpUtils; // owned
    TEllipseDrawingMethods iDrawingMethodId;
    };

#endif // __ELLIPSEAPPVIEW_h__

// End of File
