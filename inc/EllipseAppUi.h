/*
 ============================================================================
 Name		: EllipseAppUi.h
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __ELLIPSEAPPUI_h__
#define __ELLIPSEAPPUI_h__

// INCLUDES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CEllipseAppView;

// CLASS DECLARATION
/**
 * CEllipseAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CEllipseAppUi : public CAknAppUi
    {
public:
    // Constructors and destructor

    /**
     * ConstructL.
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CEllipseAppUi.
     * C++ default constructor. This needs to be public due to
     * the way the framework constructs the AppUi
     */
    CEllipseAppUi();

    /**
     * ~CEllipseAppUi.
     * Virtual Destructor.
     */
    virtual ~CEllipseAppUi();

public:
    // New functions
    void ShowDrawingMethodSelectionList();
    void UpdateMenuBarL();

private:
    // Functions from base classes

    /**
     * From CEikAppUi, HandleCommandL.
     * Takes care of command handling.
     * @param aCommand Command to be handled.
     */
    void HandleCommandL(TInt aCommand);

    /**
     *  HandleResourceChangeL.
     *  Called by the framework when the application status pane
     *  size is changed.
     */
    void HandleResourceChangeL( TInt aType );

private:
    // New function
    void DoShowDrawingMethodSelectionListL();

private:
    // Data
    RFs iFsSession;

    /**
     * The application view
     * Owned by CEllipseAppUi
     */
    CEllipseAppView* iAppView;
    };

#endif // __ELLIPSEAPPUI_h__

// End of File
