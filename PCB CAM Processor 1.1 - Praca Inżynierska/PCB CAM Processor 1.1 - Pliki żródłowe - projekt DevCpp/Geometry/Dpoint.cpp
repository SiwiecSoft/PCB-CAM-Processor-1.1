///-----------------------------------------------------------------
///
/// @file      Dpoint.cpp
/// @author    rado4ever
/// Created:   2016-04-17 11:24:45
/// @section   DESCRIPTION
///            Dpoint class implementation
///
///------------------------------------------------------------------

#include "Dpoint.h"

using namespace std;

Dpoint::Dpoint( double x, double y )
{
    this->x = x;
    this->y = y;
}

Dpoint::Dpoint( Dpoint *OldDpoint )
{
    this->x = OldDpoint->x;
    this->y = OldDpoint->y;
}

bool Dpoint::IsBetween( Dpoint *Dpoint1, Dpoint *Dpoint2 ) // dziala poprawnie dla punktow ktore sa w lini prostej
{
    double x1 = Dpoint1->x;
    double y1 = Dpoint1->y;
    double x2 = Dpoint2->x;
    double y2 = Dpoint2->y;
    
    return ( min(x1,x2) <= x && max(x1,x2) >= x   &&   min(y1,y2) <= y && max(y1,y2) >= y );
}




bool IsLine( Cpoint *End1, Cpoint *Tested, Cpoint *End2 ) // dziala poprawnie dla punktow ktore sa w lini prostej
{
    double x0 = Tested->real();
    double y0 = Tested->imag();
    double x1 = End1->real();
    double y1 = End1->imag();
    double x2 = End2->real();
    double y2 = End2->imag();
    
    return ( min(x1,x2) <= x0 && max(x1,x2) >= x0   &&   min(y1,y2) <= y0 && max(y1,y2) >= y0 );
}

Cpoint Cscalar( Cpoint V1, Cpoint V2 )
{
    return Cpoint( V1.real()*V2.real() + V1.imag()*V2.imag(), 0 );
}

Cpoint GetPointOnLine( Cpoint V1, Cpoint V2, Cpoint V3 ) // oblicza V4 czyli rzut punktu V3 na prost¹ V1, V2
{
    // http://www.algorytm.org/geometria-obliczeniowa/rzutowanie-punktu-prostopadle-na-linie.html
    
    Cpoint U = Cscalar( V3-V1, V2-V1 ) / Cscalar( V1-V2, V1-V2 ); // U = u + 0i
    return V1 + (V2-V1)*U;
}

