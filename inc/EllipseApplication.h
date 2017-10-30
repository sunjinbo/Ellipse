/*
 ============================================================================
 Name		: EllipseApplication.h
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __ELLIPSEAPPLICATION_H__
#define __ELLIPSEAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "Ellipse.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidEllipseApp =
    {
    _UID3
    };

// CLASS DECLARATION

/**
 * CEllipseApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CEllipseApplication is the application part of the
 * AVKON application framework for the Ellipse example application.
 */
class CEllipseApplication : public CAknApplication
    {
public:
    // Functions from base classes

    /**
     * From CApaApplication, AppDllUid.
     * @return Application's UID (KUidEllipseApp).
     */
    TUid AppDllUid() const;

protected:
    // Functions from base classes

    /**
     * From CApaApplication, CreateDocumentL.
     * Creates CEllipseDocument document object. The returned
     * pointer in not owned by the CEllipseApplication object.
     * @return A pointer to the created document object.
     */
    CApaDocument* CreateDocumentL();
    };

#endif // __ELLIPSEAPPLICATION_H__
// End of File
