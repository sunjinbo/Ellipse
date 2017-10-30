/*
 ============================================================================
 Name		: EllipseApplication.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "Ellipse.hrh"
#include "EllipseDocument.h"
#include "EllipseApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CEllipseApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CEllipseApplication::CreateDocumentL()
    {
    // Create an Ellipse document, and return a pointer to it
    return CEllipseDocument::NewL(*this);
    }

// -----------------------------------------------------------------------------
// CEllipseApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CEllipseApplication::AppDllUid() const
    {
    // Return the UID for the Ellipse application
    return KUidEllipseApp;
    }

// End of File
