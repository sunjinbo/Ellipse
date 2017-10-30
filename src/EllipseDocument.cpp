/*
 ============================================================================
 Name		: EllipseDocument.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : CEllipseDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "EllipseAppUi.h"
#include "EllipseDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CEllipseDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CEllipseDocument* CEllipseDocument::NewL(CEikApplication& aApp)
    {
    CEllipseDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CEllipseDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CEllipseDocument* CEllipseDocument::NewLC(CEikApplication& aApp)
    {
    CEllipseDocument* self = new (ELeave) CEllipseDocument(aApp);

    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CEllipseDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CEllipseDocument::ConstructL()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CEllipseDocument::CEllipseDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CEllipseDocument::CEllipseDocument(CEikApplication& aApp) :
    CAknDocument(aApp)
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CEllipseDocument::~CEllipseDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CEllipseDocument::~CEllipseDocument()
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CEllipseDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CEllipseDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it;
    // the framework takes ownership of this object
    return new (ELeave) CEllipseAppUi;
    }

// End of File
