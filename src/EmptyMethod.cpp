/*
 ============================================================================
 Name        : EmptyMethod.cpp
 Author      : Sun Jinbo
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : CEmptyMethod implementation
 ============================================================================
 */

#include <coecntrl.h>
#include <bitstd.h>
#include <ellipse_0xe8381f31.rsg>
#include "EmptyMethod.h"


CEmptyMethod::CEmptyMethod(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
: CDrawingMethod( aObserver, aEllipseEnv, aEllipseRect )
    {
    // No implementation required
    }

CEmptyMethod::~CEmptyMethod()
    {
    }

CEmptyMethod* CEmptyMethod::NewLC(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
    {
    CEmptyMethod* self 
        = new (ELeave) CEmptyMethod(aObserver, aEllipseEnv, aEllipseRect);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CEmptyMethod::SetEllipseRect( const TRect& aEllipseRect )
    {
    CDrawingMethod::SetEllipseRect( aEllipseRect );
    }

void CEmptyMethod::Draw()
    {
    DoDrawMethodName();
    }

void CEmptyMethod::Move()
    {
    // no implementation required
    }

CEmptyMethod* CEmptyMethod::NewL(            
        MDrawingMethodObserver& aObserver, 
        MEllipseEnv& aEllipseEnv,
        const TRect& aEllipseRect )
    {
    CEmptyMethod* self 
        = CEmptyMethod::NewLC(aObserver, aEllipseEnv, aEllipseRect);
    CleanupStack::Pop(); // self;
    return self;
    }

void CEmptyMethod::ConstructL()
    {
    CDrawingMethod::ConstructL();
    LoadMethodNameL( R_EMPTY_METHOD_TEXT );
    }

