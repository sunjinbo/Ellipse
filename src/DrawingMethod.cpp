/*
 ============================================================================
 Name		: DrawingMethod.cpp
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDrawingMethod implementation
 ============================================================================
 */

#include <e32math.h>
#include <fbs.h>
#include <bitstd.h>
#include <eikenv.h>
#include <stringloader.h>
#include "DrawingMethod.h"
#include "EllipseEnv.h"

// CONSTANTS
const TReal KPI = 3.1415926;
const TInt KSetps = 180;
const TInt KAngle = 360;
const TInt KDoMoveDelayTimeout = 0;
const TInt KDoMoveTimeout = 100000;
const TInt KOriginTextOffset = 8;

const TRgb KTextColor = TRgb( 0, 111, 121 );

CDrawingMethod::CDrawingMethod( 
  MDrawingMethodObserver& aObserver, 
  MEllipseEnv& aEllipseEnv,
  const TRect& aEllipseRect )
: CActive(EPriorityUserInput), // high priority
  iObserver( aObserver ),
  iEllipseEnv( aEllipseEnv ),
  iGc( aEllipseEnv.Gc() ),
  iEnv( aEllipseEnv.EikonEnv() ),
  iEllipseRect( aEllipseRect )
    {
    CActiveScheduler::Add(this); // Add to scheduler
    }

void CDrawingMethod::ConstructL()
    {
    User::LeaveIfError(iTimer.CreateLocal()); // Initialize timer
    
    InitializeOrbit( iEllipsePointList, iEllipseRect );

    TFontSpec fontSpec = iEnv->DenseFont()->FontSpecInTwips();
    fontSpec.iHeight -= fontSpec.iHeight / 3;
    fontSpec.iFontStyle.SetBitmapType( EMonochromeGlyphBitmap );
    iEnv->ScreenDevice()->GetNearestFontInTwips( iFont, fontSpec );

    StartL( 50000 );
    
    iPeriodic = CPeriodic::NewL( CActive::EPriorityUserInput );
    iPeriodic->Cancel();
    iPeriodic->Start(
                    KDoMoveDelayTimeout,
                    KDoMoveTimeout,
                    TCallBack( TimerCallback, this ) );
    }

CDrawingMethod::~CDrawingMethod()
    {
    Cancel(); // Cancel any request, if outstanding
    iTimer.Close(); // Destroy the RTimer object
    // Delete instance variables if any
    iEllipsePointList.Close();

    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;
        }
    
    delete iDrawingMethodName;
    iEnv->ScreenDevice()->ReleaseFont( iFont );
    }

void CDrawingMethod::SetEllipseRect( const TRect& aEllipseRect )
	{
	iEllipseRect = aEllipseRect;
	InitializeOrbit( iEllipsePointList, iEllipseRect );
	// And then we update ellipse scene immediately
	iObserver.StateChanged( EEllipseSceneUpdated );
	}

void CDrawingMethod::DoCancel()
    {
    iTimer.Cancel();
    }

void CDrawingMethod::RunL()
    {
    iObserver.StateChanged( EEllipseSceneUpdated );
    iTimer.After(iStatus, 50000); // Set for 1 sec later
    SetActive(); // Tell scheduler a request is active
    }

TInt CDrawingMethod::RunError(TInt aError)
    {
    return aError;
    }

TReal CDrawingMethod::Cos( TReal aSrc ) const
    {
    TReal trg = 0.0;
    Math::Cos( trg, aSrc );
    return trg;
    }

TReal CDrawingMethod::Sin( TReal aSrc ) const
    {
    TReal trg = 0.0;;
    Math::Sin( trg, aSrc );
    return trg;
    }

TReal CDrawingMethod::Mod( TReal aSrc, const TReal &aModulus ) const
    {
    TReal trg = 0.0;;
    Math::Mod( trg, aSrc, aModulus );
    return trg;
    }

TReal CDrawingMethod::Sqrt( TReal aSrc ) const
    {
    TReal trg = 0.0;;
    Math::Sqrt( trg, aSrc );
    return trg;
    }

TReal CDrawingMethod::Square( TReal aSrc ) const
    {
    return aSrc * aSrc;
    }

void CDrawingMethod::InitializeOrbit( 
        RArray<TPoint>& aEllipsePointList, const TRect& aEllipseRect )
    {
    // Remove all orbit points from the list first.
    aEllipsePointList.Reset();

    TReal a = aEllipseRect.Width() / 2;
    TReal b = aEllipseRect.Height() / 2;

    // Angle is given by degree value
    TReal beta = -KAngle * ( KPI / 180 ); // Converts degree value into radians
    TReal sinbeta = Sin( beta );
    TReal cosbeta = Cos( beta );
    
    for ( TInt i = 0; i < 360; i += 360 / KSetps )
        {
        TReal alpha = i * ( KPI / 180 );
        TReal sinalpha = Sin( alpha );
        TReal cosalpha = Cos( alpha );
        
        TPoint orbitPoint;
        orbitPoint.iX
            = aEllipseRect.Center().iX + ( a * cosalpha * cosbeta - b * sinalpha * sinbeta );
        orbitPoint.iY
            = aEllipseRect.Center().iY + ( a * cosalpha * sinbeta + b * sinalpha * cosbeta );

        aEllipsePointList.Insert( orbitPoint, 0 );
        }
    }

void CDrawingMethod::LoadMethodNameL( TInt aResourceId )
    {
    iDrawingMethodName = StringLoader::LoadL( aResourceId );
    }

void CDrawingMethod::DoDrawMethodName()
    {
    if ( iDrawingMethodName )
        {
        iGc->UseFont( iFont );

        // Draws original point
        TRect textRect;
        TPoint tl;
        tl.iX = iEllipseEnv.ViewRect().iTl.iX + KOriginTextOffset;
        tl.iY = iEllipseEnv.ViewRect().iTl.iY + KOriginTextOffset;
        TInt w = iFont->TextWidthInPixels( *iDrawingMethodName );
        TInt h = iFont->HeightInPixels() + KOriginTextOffset;
        textRect.SetRect( tl, TSize( w, h ) );
        TInt baseline = ( textRect.Height() + iFont->HeightInPixels() ) / 2;

        iGc->SetPenStyle( CGraphicsContext::ESolidPen );
        iGc->SetBrushStyle( CGraphicsContext::ENullBrush );
        iGc->SetPenColor( KTextColor );
        iGc->DrawText( *iDrawingMethodName, textRect, baseline, CGraphicsContext::ECenter, 0 );

        // Discards font
        iGc->DiscardFont();
        }
    }

void CDrawingMethod::StartL(TTimeIntervalMicroSeconds32 aDelay)
    {
    Cancel(); // Cancel any request, just to be sure
    iState = EUninitialized;
    iTimer.After(iStatus, aDelay ); // Set for later
    SetActive(); // Tell scheduler a request is active
    }

TInt CDrawingMethod::TimerCallback( TAny* aPtr )
    {
	CDrawingMethod* self = static_cast<CDrawingMethod*> ( aPtr );
    self->Move();
    return 0;
    }
