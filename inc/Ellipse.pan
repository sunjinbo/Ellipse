/*
 ============================================================================
 Name		: Ellipse.pan
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __ELLIPSE_PAN__
#define __ELLIPSE_PAN__

/** Ellipse application panic codes */
enum TEllipsePanics
    {
    EEllipseBadCommand = 1,
    EEllipseBadIndex
    // add further panics here
    };

inline void Panic( TEllipsePanics aReason )
    {
    _LIT( KApplicationName, "Ellipse");
    User::Panic( KApplicationName, aReason );
    }

#endif // __ELLIPSE_PAN__
