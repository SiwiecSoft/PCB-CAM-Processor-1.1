///-----------------------------------------------------------------
///
/// @file      Dpoint.h
/// @author    rado4ever
/// Created:   2016-04-17 11:24:45
/// @section   DESCRIPTION
///            Dpoint class declaration
///
///------------------------------------------------------------------

#ifndef DPOINT
#define DPOINT

#include <complex>
using namespace std;
typedef complex<double> Cpoint;

typedef double Angle;

#include <wx/wx.h>

class Dpoint
{
    public:
        double x;
        double y;
        
        bool IsBetween( Dpoint *Dpoint1, Dpoint *Dpoint2 );
        
        Dpoint( double x = 0.0, double y = 0.0 );
        Dpoint( Dpoint *OldDpoint );
};

WX_DEFINE_SORTED_ARRAY( Cpoint *, CpointSortedArray );
WX_DEFINE_SORTED_ARRAY( Angle  *, AngleSortedArray );



/*static int CompareThrowLine(Dpoint *first, Dpoint *second);
static int CompareEuclides( Dpoint *first, Dpoint *second );
static int CompareSum( Dpoint *first, Dpoint *second );*/

bool IsLine( Cpoint *End1, Cpoint *Tested, Cpoint *End2 ); // dziala poprawnie dla punktow ktore sa w lini prostej bo tak naprawde sprawdza czy jest w prostokacie

Cpoint Cscalar( Cpoint V1, Cpoint V2 ); // liczy iloczyn skalarny wektorow podanych jako liczby zespolone i zwraca go jako liczbe zespolona

Cpoint GetPointOnLine( Cpoint V1, Cpoint V2, Cpoint V3 ); // oblicza V4 czyli rzut punktu V3 na prost¹ V1, V2

static int CompareThrowLine( Cpoint *first, Cpoint *second )
{
    if ( real(*first) -  real(*second) < 0.001 &&  real(*first) -  real(*second) > -0.001 ) // czyli zero
    {
        if (  imag(*first) <  imag(*second) ) return -1;
        else return 1;
    }
    else
    {
        if (  real(*first) <  real(*second) ) return -1;
        else return 1;
    }
}

static int CompareThrowArc( Cpoint *first, Cpoint *second )
{
    double af = arg(*first);   if ( af < 0 ) af += 2*M_PI;
    double as = arg(*second);  if ( as < 0 ) as += 2*M_PI;
    
    if (  af < as ) return -1;
    else return 1;
}

static int CompareAngle( Angle *first, Angle *second )
{
    if (  *first < *second ) return -1;
    else return 1;
}

#endif
