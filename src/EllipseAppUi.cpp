/*
 ============================================================================
 Name		: EllipseAppUi.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : CEllipseAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <AknPopup.h>
#include <AknLists.h>
#include <AknNoteDialog.h>
#include <BarsRead.h>
#include <eikdef.h>
#include <GulIcon.h>
#include <EikClbd.h>
#include <eikenv.h>
#include <eikapp.h>
#include <eikmenup.h>
#include <AknIconArray.h>
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <avkon.mbg>
#include <ellipse_0xe8381f31.rsg>

#include "Ellipse.hrh"
#include "Ellipse.pan"
#include "EllipseApplication.h"
#include "EllipseAppUi.h"
#include "EllipseAppView.h"

// Constans
const TInt KMaxTitleLength = 32;

// path and name of mbm file

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CEllipseAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CEllipseAppUi::ConstructL()
    {
    // Initialise app UI with standard value.
    BaseConstructL(CAknAppUi::EAknEnableSkin);

    // Create view object
    iAppView = CEllipseAppView::NewL(*this,ClientRect());

    iAppView->SetDrawingMethodL( EEmptyMethod );

    AddToStackL( iAppView );
    }

// -----------------------------------------------------------------------------
// CEllipseAppUi::CEllipseAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CEllipseAppUi::CEllipseAppUi()
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CEllipseAppUi::~CEllipseAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CEllipseAppUi::~CEllipseAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack( iAppView );
        delete iAppView;
        iAppView = NULL;
        }

    iFsSession.Close();
    }

// -----------------------------------------------------------------------------
// CEllipseAppUi::ShowDrawingMethodSelectionList()
// -----------------------------------------------------------------------------
//
void CEllipseAppUi::ShowDrawingMethodSelectionList()
    {
    TRAP_IGNORE( DoShowDrawingMethodSelectionListL() );
    }

// -----------------------------------------------------------------------------
// CEllipseAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CEllipseAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case EAboutCmd:
            {
            CAknMessageQueryDialog* dlg =
                    new (ELeave) CAknMessageQueryDialog();
            dlg->PrepareLC( R_ABOUT_QUERY_DIALOG );
            HBufC* title = iEikonEnv->AllocReadResourceLC(
                    R_ABOUT_DIALOG_TITLE );
            dlg->QueryHeading()->SetTextL(*title);
            CleanupStack::PopAndDestroy(); //title
            HBufC* msg = iEikonEnv->AllocReadResourceLC( R_ABOUT_DIALOG_TEXT );
            dlg->SetMessageTextL(*msg);
            CleanupStack::PopAndDestroy(); //msg
            dlg->RunLD();
            }
            break;

        case EPinsStringMethodCmd:
            iAppView->SetDrawingMethodL( EPinsStringMethod );
            break;

        case EHypotrochoidMethodCmd:
            iAppView->SetDrawingMethodL( EHypotrochoidMethod );
            break;

        case EArchimedesMethodCmd:
            iAppView->SetDrawingMethodL( EArchimedesMethod );
            break;

        default:
            Panic( EEllipseBadCommand );
            break;
        }
    }

// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CEllipseAppUi::HandleResourceChangeL( TInt aType )
    {
    CAknAppUi::HandleResourceChangeL( aType );
    iAppView->SetRect( ClientRect() );
    }

// -----------------------------------------------------------------------------
// CEllipseAppUi::DoShowDrawingMethodSelectionListL()
// -----------------------------------------------------------------------------
//
void CEllipseAppUi::DoShowDrawingMethodSelectionListL()
    {
    // Create CEikTextListBox instance, list
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;

    // Push list'pointer to CleanupStack.
    CleanupStack::PushL( list );

    // Create CAknPopupList instance, popupList
    CAknPopupList* popupList = CAknPopupList::NewL( list, 
								R_AVKON_SOFTKEYS_SELECT_CANCEL,
								AknPopupLayouts::EMenuWindow );
    // Push popupList'pointer to CleanupStack.
    CleanupStack::PushL( popupList );

    // Initialize listbox.
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff,
                                                     CEikScrollBarFrame::EAuto );

    // Create CDesCArrayFlat instance, items
    CDesCArrayFlat* items = iCoeEnv->ReadDesCArrayResourceL(
								R_AKNPOPLIST_MENU_DRAWING_METHOD_ARRAY );
        // Push items'pointer to CleanupStack.  
    CleanupStack::PushL( items );

    // Set listitems.
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    CleanupStack::Pop(); // items
    
    // Allocate TBuf with constant length.
    TBuf<KMaxTitleLength> title;

    // Reads a resource into a descriptor.
    iCoeEnv->ReadResourceL( title, R_AKNPOPLIST_MENU_DRAWING_METHOD_TITLE );

    popupList->SetTitleL( title );

    // Show popup list and then show return value.
    TInt popupOk = popupList->ExecuteLD();

    // Pop the popupList's pointer from CleanupStack
    CleanupStack::Pop();

    if ( popupOk )
        {
        TInt index = list->CurrentItemIndex();
        
        iAppView->SetDrawingMethodL( (TEllipseDrawingMethods)index );
        }
    
    // Pop and Destroy the list's pointer from CleanupStack
    CleanupStack::PopAndDestroy();
    }

// -----------------------------------------------------------------------------
// CEllipseAppUi::UpdateMenuBarL()
// -----------------------------------------------------------------------------
//
void CEllipseAppUi::UpdateMenuBarL()
    {
    CEikMenuBar*  menuBar = iEikonEnv->AppUiFactory()->MenuBar();
    switch ( iAppView->DrawingMethod() )
        {
        case EEmptyMethod:
            menuBar->SetMenuTitleResourceId( R_EMPTY_MENUBAR );
            break;
        case EPinsStringMethod:
            menuBar->SetMenuTitleResourceId( R_PINS_STRING_CHECKED_MENUBAR );
            break;
        case EHypotrochoidMethod:
            menuBar->SetMenuTitleResourceId( R_HYPOTROCHOID_CHECKED_MENUBAR );
            break;
        case EArchimedesMethod:
            menuBar->SetMenuTitleResourceId( R_ARCHIMEDES_CHECKED_MENUBAR );
            break;
        default:
            break;
        }
    }

// End of File
