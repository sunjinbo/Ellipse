/*
 ============================================================================
 Name		: ArchimedesMethod.cpp
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CArchimedesMethod implementation
 ============================================================================
 */

#include <bitstd.h>
#include <coecntrl.h>
#include <eikenv.h>
#include <ellipse_0xe8381f31.rsg>
#include "ArchimedesMethod.h"

const TRgb KLineColor = KRgbBlack;
const TInt KDoModeDelayTimeout = 50000000;
const TInt KDoModeTimeout = 50000000;
const TInt KExtraBlockWidth = 100;
const TInt KExtraBlockHeight = 60;

CArchimedesMethod::CArchimedesMethod(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
: CDrawingMethod( aObserver, aEllipseEnv, aEllipseRect ), iMode( EExtra )
    {
    // No implementation required
    }

CArchimedesMethod::~CArchimedesMethod()
    {
	if ( iModePeriodic )
		{
	    iModePeriodic->Cancel();
	    delete iModePeriodic;
		}
    }

CArchimedesMethod* CArchimedesMethod::NewLC(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
    {
    CArchimedesMethod* self 
        = new (ELeave) CArchimedesMethod(aObserver, aEllipseEnv, aEllipseRect);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CArchimedesMethod* CArchimedesMethod::NewL(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
    {
    CArchimedesMethod* self 
        = CArchimedesMethod::NewLC(aObserver, aEllipseEnv, aEllipseRect);
    CleanupStack::Pop(); // self;
    return self;
    }

void CArchimedesMethod::Draw()
    {
    DoDrawMethodName();
    
    iGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iGc->SetPenSize( TSize( 1, 1 ) );
    iGc->SetPenColor( KLineColor );
    iGc->SetBrushColor( KLineColor );

    TPoint ellipsePoint = iEllipsePointList[iEllipsePointIndex];

    iGc->DrawLine( ellipsePoint, iArchimedesPointTwo );
    iGc->DrawLine( iArchimedesPointOne, iArchimedesPointTwo);

    iGc->SetPenColor( KRgbBlack );
    iGc->SetBrushColor( KRgbBlack );
    iGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    iGc->DrawEllipse( iEllipseRect );

    if ( iMode == ENormal )
    	{
		iGc->SetPenColor( KRgbDarkGreen );
		iGc->SetBrushColor( KRgbDarkGreen );
		iGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
		iGc->DrawRect( TRect( TPoint( iArchimedesPointOne.iX - 3, iArchimedesPointOne.iY - 6 ), TSize( 6, 12 ) ) );
		iGc->DrawRect( TRect( TPoint( iArchimedesPointTwo.iX - 6, iArchimedesPointTwo.iY - 3 ), TSize( 12, 6 ) ) );
		
		iGc->SetPenColor( KRgbRed );
		iGc->SetBrushColor( KRgbRed );
		iGc->DrawEllipse( TRect( TPoint( ellipsePoint.iX - 3, ellipsePoint.iY - 3 ), TSize( 6, 6 ) ) );
    	}
    else
    	{
        TRgb color( KRgbDarkGreen );
        color.SetAlpha( 220 );
		iGc->SetPenColor( KRgbBlack );
		iGc->SetBrushColor( color );
		iGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
		iGc->DrawRect( TRect( TPoint( iArchimedesPointOne.iX - 12, iArchimedesPointOne.iY - 24 ), TSize( 24, 48 ) ) );
		iGc->DrawRect( TRect( TPoint( iArchimedesPointTwo.iX - 24, iArchimedesPointTwo.iY - 12 ), TSize( 48, 24 ) ) );

        TRgb blockColor( KRgbDarkYellow );
        blockColor.SetAlpha( 220 );
		iGc->SetPenColor( KRgbDarkGray );
		iGc->SetBrushColor( blockColor );
		TPoint center = iEllipseRect.Center();
		center.iX += 12;
		center.iY -= 12;
		center.iY -= KExtraBlockHeight;
		iGc->DrawRect( TRect( center, TSize( KExtraBlockWidth, KExtraBlockHeight ) ) );
		
		center = iEllipseRect.Center();
		center.iX -= 12;
		center.iY -= 12;
		center.iX -= KExtraBlockWidth;
		center.iY -= KExtraBlockHeight;
		iGc->DrawRect( TRect( center, TSize( KExtraBlockWidth, KExtraBlockHeight ) ) );
		
		center = iEllipseRect.Center();
		center.iX -= 12;
		center.iY += 12;
		center.iX -= KExtraBlockWidth;
		iGc->DrawRect( TRect( center, TSize( KExtraBlockWidth, KExtraBlockHeight ) ) );
		
		center = iEllipseRect.Center();
		center.iX += 12;
		center.iY += 12;
		iGc->DrawRect( TRect( center, TSize( KExtraBlockWidth, KExtraBlockHeight ) ) );
		
		iGc->SetPenColor( KRgbRed );
		iGc->SetBrushColor( KRgbRed );
		iGc->DrawEllipse( TRect( TPoint( ellipsePoint.iX - 3, ellipsePoint.iY - 3 ), TSize( 6, 6 ) ) );
		
		iGc->SetPenColor( KRgbBlack );
		iGc->SetBrushColor( KRgbBlack );
		iGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
		iGc->DrawRect( TRect( TPoint( iArchimedesPointOne.iX - 3, iArchimedesPointOne.iY - 3 ), TSize( 6, 6 ) ) );
		iGc->DrawRect( TRect( TPoint( iArchimedesPointTwo.iX - 3, iArchimedesPointTwo.iY - 3 ), TSize( 6, 6 ) ) );
    	}
    }

void CArchimedesMethod::Move()
	{
    TInt count( iEllipsePointList.Count() );
    iEllipsePointIndex++;
    if ( iEllipsePointIndex < 0 || iEllipsePointIndex >= count )
        {
        iEllipsePointIndex = 0;
        }
    CalcArchimedesPoints();
	}

void CArchimedesMethod::ConstructL()
    {
    CDrawingMethod::ConstructL();
    
    LoadMethodNameL( R_ARCHIMEDES_METHOD_TEXT );
    
    iModePeriodic = CPeriodic::NewL( CActive::EPriorityUserInput );
    iModePeriodic->Cancel();
    iModePeriodic->Start(
    		        KDoModeDelayTimeout,
    		        KDoModeTimeout,
                    TCallBack( ModeCallback, this ) );
    }

void CArchimedesMethod::CalcArchimedesPoints()
    {
    TPoint ellipsePoint = iEllipsePointList[iEllipsePointIndex];
    TInt a(0), b(0);
    if ( iEllipseRect.Width() > iEllipseRect.Height() )
        {
        // focal position is in X-axis 
        a = iEllipseRect.Width() / 2;
        b = iEllipseRect.Height() / 2;

        iArchimedesPointTwo.iY = iEllipseRect.Center().iY;
        if ( ellipsePoint.iX >= iEllipseRect.Center().iX )
            iArchimedesPointTwo.iX = iEllipseRect.Center().iX + ( ellipsePoint.iX - iEllipseRect.Center().iX ) * ( a - b ) / a;
        else
            iArchimedesPointTwo.iX = iEllipseRect.Center().iX - ( iEllipseRect.Center().iX - ellipsePoint.iX ) * ( a - b ) / a;
        
        iArchimedesPointOne.iX = iEllipseRect.Center().iX;
        if ( ellipsePoint.iY >= iEllipseRect.Center().iY )
            iArchimedesPointOne.iY = iEllipseRect.Center().iY - Sqrt( Square( a - b ) - Square( iArchimedesPointTwo.iX - iEllipseRect.Center().iX ) );
        else
            iArchimedesPointOne.iY = iEllipseRect.Center().iY + Sqrt( Square( a - b ) - Square( iArchimedesPointTwo.iX - iEllipseRect.Center().iX ) );
        }
    else
        {
        // ToDo:
        // focal position is in Y-axis
        a = iEllipseRect.Height() / 2;
        b = iEllipseRect.Width() / 2;
        }
    }

TInt CArchimedesMethod::ModeCallback( TAny* aPtr )
    {
	CArchimedesMethod* self = static_cast<CArchimedesMethod*> ( aPtr );
    self->DoNextMode();
    return 0;
    }

void CArchimedesMethod::DoNextMode()
	{
	iMode = ( iMode == ENormal ? EExtra : ENormal );
	}
