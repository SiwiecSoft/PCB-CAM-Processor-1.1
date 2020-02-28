///-----------------------------------------------------------------
///
/// @file      MyGL.cpp
/// @author    rado4ever
/// Created:   2016-04-17 11:27:12
/// @section   DESCRIPTION
///            MyGL class implementation ----------- to jeszce nie jest klasa ale kto wie moze kiedys :)
///
///------------------------------------------------------------------

#include "MyGL.h"

using namespace std;

void EnableOpenGL( HWND hWnd, HDC *hDC, HGLRC *hRC )
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
}


void DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC )
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

void RenderOpenGL()
{
    
}

void ResizeOpenGL()
{
    
}




// Draw functions

void DrawLine( Cpoint *P1, Cpoint *P2 )
{
    glBegin(GL_LINES);
        //glColor3f(Col.GLRed(), Col.GLGreen(), Col.GLBlue());
        glVertex2f(P1->real(), P1->imag());
        glVertex2f(P2->real(), P2->imag());
    glEnd();
}

void DrawLine( Cpoint P1, Cpoint P2, rxColour Col )
{
    glBegin(GL_LINES);
        glColor3f(Col.GLRed(), Col.GLGreen(), Col.GLBlue());
        glVertex2f(P1.real(), P1.imag());
        glVertex2f(P2.real(), P2.imag());
    glEnd();
}

void DrawQuad( Cpoint P1, Cpoint P2, Cpoint P3, Cpoint P4, rxColour Col, bool Fill )
{
    if ( Fill ) glBegin(GL_QUADS);
    else        glBegin(GL_LINE_LOOP);
        glColor3f(Col.GLRed(), Col.GLGreen(), Col.GLBlue());
        glVertex2f(P1.real(), P1.imag());
        glVertex2f(P2.real(), P2.imag());
        glVertex2f(P3.real(), P3.imag());
        glVertex2f(P4.real(), P4.imag());
    glEnd();
}

void DrawRect( Cpoint P1, Cpoint P2, rxColour Col, bool Fill )
{
    if ( Fill ) glBegin(GL_QUADS);
    else        glBegin(GL_LINE_LOOP);
        glColor3f(Col.GLRed(), Col.GLGreen(), Col.GLBlue());
        glVertex2f(P1.real(), P1.imag());
        glVertex2f(P1.real(), P2.imag());
        glVertex2f(P2.real(), P2.imag());
        glVertex2f(P2.real(), P1.imag());
    glEnd();
}

void DrawPolygon( Cpoint P1, bool OutSide, int n, double R, double StartAngle, rxColour Col, bool Fill )
{
    if ( OutSide ) R = R/cos(M_PI/n);
    if ( Fill ) glBegin(GL_POLYGON);
    else        glBegin(GL_LINE_LOOP);
        glColor3f(Col.GLRed(), Col.GLGreen(), Col.GLBlue());
        for ( double i = StartAngle; i < 2*M_PI + StartAngle; i += 2*M_PI/n ) glVertex2f(P1.real() + sin(i)*R, P1.imag() + cos(i)*R );
    glEnd();
}

void DrawCircle( Cpoint P1, double R, rxColour Col, bool Fill )
{
    DrawPolygon( P1, false, 20, R, 0.0, Col, Fill );
}

void DrawArc( Cpoint P1, double R, double StartAngle, double EndAngle, rxColour Col )
{
    Cpoint CP;
    if ( EndAngle < StartAngle ) EndAngle += 2*M_PI;
    glBegin(GL_LINE_STRIP);
        glColor3f(Col.GLRed(), Col.GLGreen(), Col.GLBlue());
        for ( double i = StartAngle; i <= EndAngle; i += ( EndAngle - StartAngle )/20 )
        {
            CP = P1 + polar( R, i ); 
            glVertex2f( CP.real(), CP.imag() );
        }
        // i jeszcze ostatni punkt 
        CP = P1 + polar( R, EndAngle ); 
        glVertex2f( CP.real(), CP.imag() );
    glEnd();
}
