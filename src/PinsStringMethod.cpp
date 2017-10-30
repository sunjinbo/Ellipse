/*
 ============================================================================
 Name		: PinsStringMethod.cpp
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPinsStringMethod implementation
 ============================================================================
 */

#include <coecntrl.h>
#include <bitstd.h>
#include <ellipse_0xe8381f31.rsg>
#include "PinsStringMethod.h"

const TRgb KLineColor = KRgbBlack;

CPinsStringMethod::CPinsStringMethod(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
: CDrawingMethod( aObserver, aEllipseEnv, aEllipseRect )
    {
    // No implementation required
    }

CPinsStringMethod::~CPinsStringMethod()
    {
    }

CPinsStringMethod* CPinsStringMethod::NewLC(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
    {
    CPinsStringMethod* self 
        = new (ELeave) CPinsStringMethod(aObserver, aEllipseEnv, aEllipseRect);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CPinsStringMethod::SetEllipseRect( const TRect& aEllipseRect )
    {
    CDrawingMethod::SetEllipseRect( aEllipseRect );
    InitPinsPoints();
    }

void CPinsStringMethod::Draw()
    {
    DoDrawMethodName();
    
    iGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iGc->SetPenSize( TSize( 1, 1 ) );
    iGc->SetPenColor( KLineColor );
    iGc->SetBrushColor( KLineColor );

    TPoint ellipsePoint = iEllipsePointList[iEllipsePointIndex];
    iGc->DrawLine( ellipsePoint, iPinsPointOne );
    iGc->DrawLine( ellipsePoint, iPinsPointTwo);

    iGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    iGc->SetPenSize( TSize( 1, 1 ) );
    iGc->SetPenColor( KLineColor );
    iGc->DrawEllipse( iEllipseRect );
    
    iGc->SetPenColor( KRgbBlue );
    iGc->SetBrushColor( KRgbBlue );
    iGc->SetBrushStyle( CGraphicsContext::ESolidBrush );

    iGc->DrawRect( TRect( TPoint( iPinsPointOne.iX - 3, iPinsPointOne.iY - 3 ), TSize( 6, 6 ) ) );
    iGc->DrawRect( TRect( TPoint( iPinsPointTwo.iX - 3, iPinsPointTwo.iY - 3 ), TSize( 6, 6 ) ) );
    
    iGc->SetPenColor( KRgbRed );
    iGc->SetBrushColor( KRgbRed );
    iGc->DrawEllipse( TRect( TPoint( ellipsePoint.iX - 3, ellipsePoint.iY - 3 ), TSize( 6, 6 ) ) );
    }

void CPinsStringMethod::Move()
	{
    TInt count( iEllipsePointList.Count() );
    iEllipsePointIndex++;
    if ( iEllipsePointIndex < 0 || iEllipsePointIndex >= count )
        {
        iEllipsePointIndex = 0;
        }
	}

CPinsStringMethod* CPinsStringMethod::NewL(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
    {
    CPinsStringMethod* self 
        = CPinsStringMethod::NewLC(aObserver, aEllipseEnv, aEllipseRect);
    CleanupStack::Pop(); // self;
    return self;
    }

void CPinsStringMethod::ConstructL()
    {
    CDrawingMethod::ConstructL();
    LoadMethodNameL( R_PINS_STRING_METHOD_TEXT );
    InitPinsPoints();
    }

void CPinsStringMethod::InitPinsPoints()
    {
    TInt a(0), b(0), c(0);
    if ( iEllipseRect.Width() > iEllipseRect.Height() )
        {
        // focal position is in X-axis 
        a = iEllipseRect.Width() / 2;
        b = iEllipseRect.Height() / 2;
        c = Sqrt( a * a - b * b );

        iPinsPointOne.iX = iEllipseRect.Center().iX - c;
        iPinsPointOne.iY = iEllipseRect.Center().iY;
        iPinsPointTwo.iX = iEllipseRect.Center().iX + c;
        iPinsPointTwo.iY = iEllipseRect.Center().iY;
        }
    else
        {
        // focal position is in Y-axis
        a = iEllipseRect.Height() / 2;
        b = iEllipseRect.Width() / 2;
        c = Sqrt( a * a - b * b );

        iPinsPointOne.iX = iEllipseRect.Center().iX;
        iPinsPointOne.iY = iEllipseRect.Center().iY - c;
        iPinsPointTwo.iX = iEllipseRect.Center().iX;
        iPinsPointTwo.iY = iEllipseRect.Center().iY + c;
        }
    }
