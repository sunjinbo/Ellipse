/*
 ============================================================================
 Name		: Ellipse.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "EllipseApplication.h"

LOCAL_C CApaApplication* NewApplication()
    {
    return new CEllipseApplication;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

