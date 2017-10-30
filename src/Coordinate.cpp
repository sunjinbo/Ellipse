/*
 ============================================================================
 Name		: Coordinate.cpp
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCoordinate implementation
 ============================================================================
 */

#include <eikenv.h>
#include <fbs.h>
#include <bitstd.h>
#include <coecntrl.h>
#include "Coordinate.h"
#include "EllipseEnv.h"

// CONSTANTS
_LIT( KOriginText, "0" );
const TInt KOriginTextOffset = 4;
_LIT( KXAxisText, "X" );
const TInt KXAxisTextOffset = 4;
_LIT( KYAxisText, "Y" );
const TInt KYAxisTextOffset = 4;
const TInt KScaleGap = 10;
const TInt KScaleLen = 5;
const TRgb KLineColor = KRgbBlack;

CCoordinate::CCoordinate( MEllipseEnv& aEnv, const TRect& aRect )
: iGc( aEnv.Gc() ), iEnv( aEnv.EikonEnv() ), iCoordinateRect( aRect )
    {
    // No implementation required
    }

CCoordinate::~CCoordinate()
    {
    iEnv->ScreenDevice()->ReleaseFont( iFont );
    }

CCoordinate* CCoordinate::NewLC( MEllipseEnv& aEnv, const TRect& aRect )
    {
    CCoordinate* self = new (ELeave) CCoordinate( aEnv, aRect );
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CCoordinate* CCoordinate::NewL( MEllipseEnv& aEnv, const TRect& aRect )
    {
    CCoordinate* self = CCoordinate::NewLC( aEnv, aRect );
    CleanupStack::Pop(); // self;
    return self;
    }

void CCoordinate::ConstructL()
    {
    TFontSpec fontSpec = iEnv->AnnotationFont()->FontSpecInTwips();
    fontSpec.iHeight -= fontSpec.iHeight / 3;
    fontSpec.iFontStyle.SetBitmapType( EMonochromeGlyphBitmap );
    iEnv->ScreenDevice()->GetNearestFontInTwips( iFont, fontSpec );
    }

void CCoordinate::Draw()
    {
    // Draws background
    
    iGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iGc->SetBrushStyle( CGraphicsContext::ENullBrush );

    // Draws X-Axis
    TPoint start, end;
    start.iX = iCoordinateRect.iTl.iX;
    start.iY = iCoordinateRect.iBr.iY - iCoordinateRect.Height() / 2;
    end.iX = iCoordinateRect.iBr.iX;
    end.iY = iCoordinateRect.iBr.iY - iCoordinateRect.Height() / 2;
    iGc->SetPenColor( KLineColor );
    iGc->DrawLine( start, end );
    
    TInt x = 0;
    TInt y = iCoordinateRect.Center().iY;
    for ( x = iCoordinateRect.Center().iX + KScaleGap; x < iCoordinateRect.iBr.iX; x += KScaleGap )
    	{
        iGc->DrawLine( TPoint( x, y ), TPoint( x, y - KScaleLen ) );
    	}
    
    for ( x = iCoordinateRect.Center().iX - KScaleGap; x > iCoordinateRect.iTl.iX; x -= KScaleGap )
    	{
		iGc->DrawLine( TPoint( x, y ), TPoint( x, y - KScaleLen ) );
    	}
    
    // Draws Y-Axis
    start.iX = iCoordinateRect.iBr.iX - iCoordinateRect.Width() / 2;
    start.iY = iCoordinateRect.iTl.iY;
    end.iX = iCoordinateRect.iBr.iX - iCoordinateRect.Width() / 2;
    end.iY = iCoordinateRect.iBr.iY;
    iGc->SetPenColor( KLineColor );
    iGc->DrawLine( start, end );

    x = iCoordinateRect.Center().iX;
    for ( y = iCoordinateRect.Center().iY + KScaleGap; y < iCoordinateRect.iBr.iY; y += KScaleGap )
    	{
        iGc->DrawLine( TPoint( x, y ), TPoint( x - KScaleLen, y ) );
    	}
    
    for ( y = iCoordinateRect.Center().iY + KScaleGap; y > iCoordinateRect.iTl.iY; y -= KScaleGap )
    	{
        iGc->DrawLine( TPoint( x, y ), TPoint( x - KScaleLen, y ) );
    	}
    
    // Draws original point
    TRect textRect;
    TPoint tl;
    tl.iX = iCoordinateRect.Center().iX + KOriginTextOffset;
    tl.iY = iCoordinateRect.Center().iY + KOriginTextOffset;
    TInt w = iFont->TextWidthInPixels( KOriginText );
    TInt h = iFont->HeightInPixels();
    textRect.SetRect( tl, TSize( w, h ) );
    TInt baseline = ( textRect.Height() + iFont->HeightInPixels() ) / 2;
    
    iGc->SetPenColor( KRgbBlack );
    iGc->UseFont( iFont );
    iGc->DrawText( KOriginText, textRect, baseline, CGraphicsContext::ECenter, 0 );

    // Draws X-Axis text
    w = iFont->TextWidthInPixels( KXAxisText );
    h = iFont->HeightInPixels();
    tl.iX = iCoordinateRect.iBr.iX - w - KXAxisTextOffset;
    tl.iY = iCoordinateRect.iBr.iY - iCoordinateRect.Height() / 2 + KXAxisTextOffset;

    textRect.SetRect( tl, TSize( w, h ) );
    iGc->SetPenColor( KRgbBlack );
    iGc->DrawText( KXAxisText, textRect, baseline, CGraphicsContext::ECenter, 0 );

    // Draws Y-Axis text
    w = iFont->TextWidthInPixels( KYAxisText );
    h = iFont->HeightInPixels();
    tl.iX = iCoordinateRect.iBr.iX - iCoordinateRect.Width() / 2 + KYAxisTextOffset;
    tl.iY = iCoordinateRect.iTl.iY;

    textRect.SetRect( tl, TSize( w, h ) );
    iGc->SetPenColor( KRgbBlack );
    iGc->DrawText( KYAxisText, textRect, baseline, CGraphicsContext::ECenter, 0 );

    // Discards font
    iGc->DiscardFont();

    }

void CCoordinate::SetRect( const TRect& aRect )
    {
    iCoordinateRect = aRect;
    }
