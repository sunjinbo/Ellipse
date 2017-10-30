/*
 ============================================================================
 Name		: EllipseDocument.h
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __ELLIPSEDOCUMENT_h__
#define __ELLIPSEDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CEllipseAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CEllipseDocument application class.
 * An instance of class CEllipseDocument is the Document part of the
 * AVKON application framework for the Ellipse example application.
 */
class CEllipseDocument : public CAknDocument
    {
public:
    // Constructors and destructor

    /**
     * NewL.
     * Two-phased constructor.
     * Construct a CEllipseDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CEllipseDocument.
     */
    static CEllipseDocument* NewL(CEikApplication& aApp);

    /**
     * NewLC.
     * Two-phased constructor.
     * Construct a CEllipseDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CEllipseDocument.
     */
    static CEllipseDocument* NewLC(CEikApplication& aApp);

    /**
     * ~CEllipseDocument
     * Virtual Destructor.
     */
    virtual ~CEllipseDocument();

public:
    // Functions from base classes

    /**
     * CreateAppUiL
     * From CEikDocument, CreateAppUiL.
     * Create a CEllipseAppUi object and return a pointer to it.
     * The object returned is owned by the Uikon framework.
     * @return Pointer to created instance of AppUi.
     */
    CEikAppUi* CreateAppUiL();

private:
    // Constructors

    /**
     * ConstructL
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CEllipseDocument.
     * C++ default constructor.
     * @param aApp Application creating this document.
     */
    CEllipseDocument(CEikApplication& aApp);

    };

#endif // __ELLIPSEDOCUMENT_h__
// End of File
