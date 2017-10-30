/*
 ============================================================================
 Name		: HypotrochoidMethod.cpp
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CHypotrochoidMethod implementation
 ============================================================================
 */

#include <coecntrl.h>
#include <bitstd.h>
#include <eikenv.h>
#include <ellipse_0xe8381f31.rsg>
#include "HypotrochoidMethod.h"

CHypotrochoidMethod::CHypotrochoidMethod(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
: CDrawingMethod( aObserver, aEllipseEnv, aEllipseRect )
    {
    // No implementation required
    }

CHypotrochoidMethod::~CHypotrochoidMethod()
    {
    iSmallCirclePointList.Close();
    }

CHypotrochoidMethod* CHypotrochoidMethod::NewLC(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
    {
    CHypotrochoidMethod* self 
        = new (ELeave) CHypotrochoidMethod(aObserver, aEllipseEnv, aEllipseRect);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CHypotrochoidMethod::SetEllipseRect( const TRect& aEllipseRect )
    {
    CDrawingMethod::SetEllipseRect( aEllipseRect );
    Initialize();
    }

void CHypotrochoidMethod::Draw()
    {
    DoDrawMethodName();
    
    iGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    iGc->SetPenSize( TSize( 1, 1 ) );

    // Draws Ellipse
    iGc->SetPenColor( KRgbBlack );
    iGc->SetBrushColor( KRgbBlack );
    iGc->DrawEllipse( iEllipseRect );
    
    // Draws big circle
    iGc->SetPenColor( KRgbDarkGray );
    iGc->SetBrushColor( KRgbDarkGray );
    iGc->SetPenStyle( CGraphicsContext::EDottedPen );
    iGc->DrawEllipse( iBigCircleRect );
    
    // Draws small circle
    TPoint tl;
    tl.iX = iSmallCirclePointList[iEllipsePointIndex].iX - iFocalLength / 2;
    tl.iY = iSmallCirclePointList[iEllipsePointIndex].iY - iFocalLength / 2;
    iGc->SetPenStyle( CGraphicsContext::EDottedPen );
    iGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    iGc->SetPenColor( KRgbDarkGray );
    iGc->SetBrushColor( KRgbDarkGray );
    iGc->DrawEllipse( TRect( tl, TSize( iFocalLength, iFocalLength ) ) );

    iGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iGc->SetPenColor( KRgbDarkGray );
    iGc->SetBrushColor( KRgbDarkGray );
    iGc->DrawLine( iSmallCirclePointList[iEllipsePointIndex], iEllipsePointList[iEllipsePointIndex] );
    
    iGc->SetPenColor( KRgbBlue );
    iGc->SetBrushColor( KRgbBlue );
    TPoint center = iSmallCirclePointList[iEllipsePointIndex];
    iGc->DrawRect( TRect( TPoint( center.iX - 3, center.iY - 3 ), TSize( 6, 6 ) ) );
    
    center = iEllipsePointList[iEllipsePointIndex];
    iGc->SetPenColor( KRgbRed );
    iGc->SetBrushColor( KRgbRed );
    iGc->DrawRect( TRect( TPoint( center.iX - 3, center.iY - 3 ), TSize( 6, 6 ) ) );
    }

void CHypotrochoidMethod::Move()
	{
    TInt count( iEllipsePointList.Count() );
    iEllipsePointIndex++;
    if ( iEllipsePointIndex < 0 || iEllipsePointIndex >= count )
        {
        iEllipsePointIndex = 0;
        }
	}

CHypotrochoidMethod* CHypotrochoidMethod::NewL(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
    {
    CHypotrochoidMethod* self 
        = CHypotrochoidMethod::NewLC(aObserver, aEllipseEnv, aEllipseRect);
    CleanupStack::Pop(); // self;
    return self;
    }

void CHypotrochoidMethod::ConstructL()
    {
    CDrawingMethod::ConstructL();
    LoadMethodNameL( R_HYPOTROCHOID_METHOD_TEXT );
    Initialize();
    }

void CHypotrochoidMethod::Initialize()
    {
    iFocalLength = ( iEllipseRect.Width() + iEllipseRect.Height() ) / 2;
    iBigCircleRect.iTl.iX = iEllipseRect.Center().iX - iFocalLength;
    iBigCircleRect.iTl.iY = iEllipseRect.Center().iY - iFocalLength;
    iBigCircleRect.iBr.iX = iEllipseRect.Center().iX + iFocalLength;
    iBigCircleRect.iBr.iY = iEllipseRect.Center().iY + iFocalLength;
    
    iSmallCircleRect.iTl.iX = iEllipseRect.Center().iX - iFocalLength / 2;
    iSmallCircleRect.iTl.iY = iEllipseRect.Center().iY - iFocalLength / 2;
    iSmallCircleRect.iBr.iX = iEllipseRect.Center().iX + iFocalLength / 2;
    iSmallCircleRect.iBr.iY = iEllipseRect.Center().iY + iFocalLength / 2;
    
    InitializeOrbit( iSmallCirclePointList, iSmallCircleRect );
    }
