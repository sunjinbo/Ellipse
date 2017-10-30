/*
 ============================================================================
 Name		: EllipseAppView.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include <fbs.h>
#include <bitdev.h>
#include <bitstd.h>
#include <w32std.h>
#include <eikenv.h>
#include <akndef.h>
#include <barsread.h>
#include <ellipse_0xe8381f31.rsg>
#include <Ellipse_background.mbg>
#include "EllipseAppView.h"
#include "EllipseAppUi.h"
#include "Coordinate.h"
#include "DrawingMethodFactory.h"
#include "BmpUtils.h"

// CONSTANTS
const TInt KDoDelayTimeout = 0;
const TInt KDoFrameUpdateTimeout = 50000;
const TInt KEllipseRectWidth = 260;
const TInt KEllipseRectHeight = 100;

#if defined( __WINS__ )
_LIT( KBackgroundFileName, "Z:\\resource\\apps\\Ellipse_background.mif" );
#else
_LIT( KBackgroundFileName, "\\resource\\apps\\Ellipse_background.mif" );
#endif // __WINS__


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CEllipseAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CEllipseAppView* CEllipseAppView::NewL(CEllipseAppUi& aAppUi,const TRect& aRect)
    {
    CEllipseAppView* self = CEllipseAppView::NewLC(aAppUi,aRect);
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CEllipseAppView* CEllipseAppView::NewLC(CEllipseAppUi& aAppUi,const TRect& aRect)
    {
	CEllipseAppView* self = new (ELeave) CEllipseAppView(aAppUi);

    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CEllipseAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    CreateBmpBufferL();

    iBmpUtils = CBmpUtils::NewL( 
            KBackgroundFileName,
            EMbmEllipse_backgroundQgn_background_portrait,
            EMbmEllipse_backgroundLastElement
            );

    ScaleBitmap();
    
    iCoordinate = CCoordinate::NewL( *this, Rect() );
    
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
                    KDoDelayTimeout,
                    KDoFrameUpdateTimeout,
                    TCallBack( TimerCallback, this ) );

    iIdle = CIdle::NewL( CActive::EPriorityLow );
    iIdle->Cancel();
    iIdle->Start( TCallBack( IdleCallback, this ) );

    SetDrawingMethodL( EEmptyMethod );
    
    // Enable Drag Events.
    EnableDragEvents();

    // OR can also be done with
    Window().PointerFilter( EPointerFilterDrag, 0 );
    
    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::CEllipseAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CEllipseAppView::CEllipseAppView(CEllipseAppUi& aAppUi)
: iAppUi( aAppUi ), iDrawingMethodId( EEmptyMethod )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::~CEllipseAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CEllipseAppView::~CEllipseAppView()
    {
    Stop();
    ReleaseBmpBuffer();
    delete iCoordinate;
    delete iDrawingMethod;
    delete iIdle;
    delete iPopupMenu;
    delete iBmpUtils;
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::SetDrawingMethodL()
// -----------------------------------------------------------------------------
//
void CEllipseAppView::SetDrawingMethodL( TEllipseDrawingMethods aMethod )
	{
    if ( aMethod != iDrawingMethodId )
        {
        iDrawingMethodId = aMethod;

        delete iDrawingMethod;
        iDrawingMethod = NULL;

        iDrawingMethod = TDrawingMethodFactory::CreateDrawingMethodL(
                aMethod, *this, *this, EllipseRect() );
        
        iAppUi.UpdateMenuBarL();
        }
	}

// -----------------------------------------------------------------------------
// CEllipseAppView::DrawingMethod()
// -----------------------------------------------------------------------------
//
TEllipseDrawingMethods CEllipseAppView::DrawingMethod() const
    {
    return iDrawingMethodId;
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::Gc()
// -----------------------------------------------------------------------------
//
CFbsBitGc*& CEllipseAppView::Gc()
    {
    return iBitmapGc;
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::EikonEnv()
// -----------------------------------------------------------------------------
//
CEikonEnv* CEllipseAppView::EikonEnv()
    {
    return iEikonEnv;
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::Rect()
// -----------------------------------------------------------------------------
//
TRect CEllipseAppView::ViewRect()
    {
    return Rect();
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CEllipseAppView::SizeChanged()
    {
    TRAP_IGNORE( CreateBmpBufferL() );
    ScaleBitmap();
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::HandlePointerEventL()
// Called by framework to handle pointer touch events.
// Note: although this method is compatible with earlier SDKs, 
// it will not be called in SDKs without Touch support.
// -----------------------------------------------------------------------------
//
void CEllipseAppView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    // Call base class HandlePointerEventL()
    CCoeControl::HandlePointerEventL( aPointerEvent );
    if( aPointerEvent.iType ==TPointerEvent::EButton1Up )
        {
        CreatePopupMenuL( aPointerEvent.iPosition );
        }
    }

// ----------------------------------------------------------------------------
// CEllipseAppView::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CEllipseAppView::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        if ( iCoordinate )
            {
            iCoordinate->SetRect( Rect() );
            }
        
        if ( iDrawingMethod )
            {
            iDrawingMethod->SetEllipseRect( EllipseRect() );
            }
        }
    }

// ----------------------------------------------------------------------------
// CEllipseAppView::StateChanged
// ----------------------------------------------------------------------------
//
void CEllipseAppView::StateChanged( TInt /*aNewState*/ )
    {
    DoDrawBackground();
    
	iCoordinate->Draw();

	if ( iDrawingMethod )
		{
	    iDrawingMethod->Draw();
		}
    }

// ----------------------------------------------------------------------------
// CEllipseAppView::ProcessCommandL
// ----------------------------------------------------------------------------
//
void CEllipseAppView::ProcessCommandL( TInt aCommandId )
	{
    switch( aCommandId )
        {
        case EPinsStringMethodCmd:
            SetDrawingMethodL( EPinsStringMethod );
            break;
        case EHypotrochoidMethodCmd:
            SetDrawingMethodL( EHypotrochoidMethod );
            break;
        case EArchimedesMethodCmd:
            SetDrawingMethodL( EArchimedesMethod );
            break;
    	default:
    		break;
        }
	}

// ----------------------------------------------------------------------------
// CEllipseAppView::CreateBmpBufferL
// ----------------------------------------------------------------------------
//
void CEllipseAppView::CreateBmpBufferL()
    {
    ReleaseBmpBuffer();

    // Create double buffer bitmap
    iBitmap = new (ELeave) CFbsBitmap;
    User::LeaveIfError( iBitmap->Create( Size(), EColor16MU ) );

    // Create double buffer graphics context
    iBitmapDevice = CFbsBitmapDevice::NewL( iBitmap );
    User::LeaveIfError( iBitmapDevice->CreateContext( iBitmapGc ) );
    
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetBrushColor( KRgbBlack );
    iBitmapGc->DrawRect( Rect() );
    }

// ----------------------------------------------------------------------------
// CEllipseAppView::ReleaseBmpBuffer
// ----------------------------------------------------------------------------
//
void CEllipseAppView::ReleaseBmpBuffer()
    {
    if ( iBitmapGc )
        {
        delete iBitmapGc;
        iBitmapGc = NULL;
        }
    if ( iBitmapDevice )
        {
        delete iBitmapDevice;
        iBitmapDevice = NULL;
        }
    if ( iBitmap )
        {
        delete iBitmap;
        iBitmap = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CEllipseAppView::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CEllipseAppView::TimerCallback( TAny* aPtr )
    {
    CEllipseAppView* self = static_cast<CEllipseAppView*> ( aPtr );
    self->DoFrame();
    return 0;
    }

// ----------------------------------------------------------------------------
// CEllipseAppView::Stop
// ----------------------------------------------------------------------------
//
void CEllipseAppView::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CEllipseAppView::DoFrame
// ----------------------------------------------------------------------------
//
void CEllipseAppView::DoFrame()
    {
    Window().Invalidate( Rect() );
    ActivateGc();
    Window().BeginRedraw( Rect() );
    CWindowGc& gc = SystemGc();
    gc.BitBlt( TPoint( 0, 0 ), iBitmap );
    Window().EndRedraw();
    DeactivateGc();
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::IdleCallback()
// -----------------------------------------------------------------------------
//
TInt CEllipseAppView::IdleCallback( TAny* aPtr )
    {
	CEllipseAppView* self = static_cast<CEllipseAppView*> ( aPtr );
    self->DoStart();
    return 0;
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::DoStart()
// -----------------------------------------------------------------------------
//
void CEllipseAppView::DoStart()
	{
	iAppUi.ShowDrawingMethodSelectionList();
	}

// -----------------------------------------------------------------------------
// CEllipseAppView::CreatePopupMenuL()
// -----------------------------------------------------------------------------
//
void CEllipseAppView::CreatePopupMenuL( const TPoint& aPos )
	{
    delete iPopupMenu;
    iPopupMenu = NULL;
    
    iPopupMenu = CAknStylusPopUpMenu::NewL( this, aPos );
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, R_ELLIPSE_POPUPMENU );
    iPopupMenu->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    iPopupMenu->ShowMenu();
	}

// -----------------------------------------------------------------------------
// CEllipseAppView::EllipseRect()
// -----------------------------------------------------------------------------
//
TRect CEllipseAppView::EllipseRect() const
    {
    TRect theRect;
    theRect.iTl.iX = Rect().Center().iX - KEllipseRectWidth / 2;
    theRect.iTl.iY = Rect().Center().iY - KEllipseRectHeight / 2;
    theRect.SetSize( TSize( KEllipseRectWidth, KEllipseRectHeight ) );
    return theRect;
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::DoDrawBackground()
// -----------------------------------------------------------------------------
//
void CEllipseAppView::DoDrawBackground()
    {
    TRect theRect( Rect() );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    if ( theRect.Width() > theRect.Height() ) // landscape
        {
        iBitmapGc->BitBltMasked( 
                    theRect.iTl,
                    iBmpUtils->Bitmap( EMbmEllipse_backgroundQgn_background_landscape ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iBmpUtils->Bitmap( EMbmEllipse_backgroundQgn_background_landscape_mask ),
                    EFalse
                    );
        }
    else // portrait
        {
        iBitmapGc->BitBltMasked( 
                    theRect.iTl,
                    iBmpUtils->Bitmap( EMbmEllipse_backgroundQgn_background_portrait ),
                    TRect( TPoint( 0, 0 ), theRect.Size() ),
                    iBmpUtils->Bitmap( EMbmEllipse_backgroundQgn_background_portrait_mask ),
                    EFalse
                    );
        }
    }

// -----------------------------------------------------------------------------
// CEllipseAppView::ScaleBitmap()
// -----------------------------------------------------------------------------
//
void CEllipseAppView::ScaleBitmap()
    {
    TInt i = EMbmEllipse_backgroundQgn_background_portrait;
    while( iBmpUtils && i < EMbmEllipse_backgroundLastElement )
        {
        iBmpUtils->SetSize( i, Rect().Size() );
        ++i;
        }
    }

// End of File
