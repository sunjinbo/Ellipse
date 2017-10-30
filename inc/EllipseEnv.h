/*
 ============================================================================
 Name		: EllipseEnv.h
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : This file contains declarations for constants of Ellipse.
 The file can be included in C++ or resource file.
 ============================================================================
 */
#ifndef __ELLIPSEENV_H__
#define __ELLIPSEENV_H__

class CFbsBitGc;
class CEikonEnv;

// CLASS DECLARATION

/**
 *  MEllipseEnv
 * 
 */
class MEllipseEnv
    {
public: // interface function
    virtual CFbsBitGc*& Gc() = 0;
    virtual CEikonEnv* EikonEnv() = 0;
    virtual TRect ViewRect() = 0;
    };

#endif // __ELLIPSEENV_H__
