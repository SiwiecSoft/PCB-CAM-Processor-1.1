///-----------------------------------------------------------------
///
/// @file      MyGL.h
/// @author    rado4ever
/// Created:   2016-04-17 11:27:43
/// @section   DESCRIPTION
///            MyGL class declaration ----------- to jeszce nie jest klasa ale kto wie moze kiedys :)
///
///------------------------------------------------------------------

#ifndef MYGL
#define MYGL

#include <wx/wx.h>

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#include "Dpoint.h"

void EnableOpenGL  ( HWND hWnd, HDC *hDC, HGLRC *hRC );
void DisableOpenGL ( HWND hWnd, HDC hDC,  HGLRC hRC  );

void RenderOpenGL();
void ResizeOpenGL();

class rxColour : public wxColour
{
    public:
        rxColour( unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha=wxALPHA_OPAQUE ) : wxColour( red, green, blue, alpha ) {};
        rxColour( const wxString &colourName ) : wxColour( colourName ) {};
          
        double GLRed()   { return (double)Red()/255; };
        double GLGreen() { return (double)Green()/255; };
        double GLBlue()  { return (double)Blue()/255; };
        double GLAlpha() { return (double)Alpha()/255; }; 
};

void DrawLine( Dpoint *P1, Dpoint *P2 );

void DrawLine( Cpoint P1, Cpoint P2, rxColour Col );
void DrawQuad( Cpoint P1, Cpoint P2, Cpoint P3, Cpoint P4, rxColour Col, bool Fill = true );
void DrawRect( Cpoint P1, Cpoint P2, rxColour Col, bool Fill = true );
void DrawPolygon( Cpoint P1, bool OutSide, int n, double R, double StartAngle, rxColour Col, bool Fill = true );
void DrawCircle( Cpoint P1, double R, rxColour Col, bool Fill = true );
void DrawArc( Cpoint P1, double R, double StartAngle, double EndAngle, rxColour Col );

#endif
