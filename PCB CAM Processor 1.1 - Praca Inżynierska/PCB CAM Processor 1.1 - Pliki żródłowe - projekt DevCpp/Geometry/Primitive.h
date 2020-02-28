///-----------------------------------------------------------------
///
/// @file      Primitive.h
/// @author    rado4ever
/// Created:   2016-04-26 21:07:14
/// @section   DESCRIPTION
///            Primitive class declaration
///
///------------------------------------------------------------------

#ifndef PRIMITIVE
#define PRIMITIVE

#define ZERO  0.000000001
#define NANO  0.000001
#define MICRO 0.001

#define EQ_DOUBLE(a,b,z) ( abs(a-b) <  z )
#define LT_DOUBLE(a,b,z) (    (a-b) < -z )
#define LE_DOUBLE(a,b,z) (    (a-b) <  z )
#define GT_DOUBLE(a,b,z) (    (a-b) >  z )
#define GE_DOUBLE(a,b,z) (    (a-b) > -z )

#define GTLT_DOUBLE(a,b,c,z) ( GT_DOUBLE(a,b,z) && LT_DOUBLE(a,c,z) )
#define GELE_DOUBLE(a,b,c,z) ( GE_DOUBLE(a,b,z) && LE_DOUBLE(a,c,z) )

#include <wx/wx.h>
#include "Dpoint.h"

enum
{
    line = 1,
    arc,
};

class PCBObject;
class PrimitiveArray;

class Primitive
{
    public:
        Primitive( Cpoint Begin, Cpoint End,                PCBObject *Owner = NULL );
        Primitive( Cpoint Begin, Cpoint End, Cpoint Center, PCBObject *Owner = NULL );
        //Primitive( const LinePrim &PrimitiveSrc ) : Begin( PrimitiveSrc.Begin ),  End( PrimitiveSrc.End ) {};
        //Primitive( const LinePrim *PrimitiveSrc ) : Begin( PrimitiveSrc->Begin ), End( PrimitiveSrc->End ) {};
        ~Primitive();
        
        void Calc();
        void Draw( wxString Col = "BLACK" );
        void Init();
        void Cut( Primitive *Prim );
        void GetFragments( PrimitiveArray *OutArray );
        
        void Reverse( bool reverse = true ) { rev = reverse; };
        bool IsReverse() { return rev; };
        
        Cpoint GetMiddlePoint();
        Cpoint GetBeginPoint()  { return rev ? end   : begin; };
        Cpoint GetEndPoint()    { return rev ? begin : end;   };
        Cpoint GetCenterPoint() { return center; };
        double GetR()           { return R; };
        
        double Len();
        double AngleLen();
        double GetMinNorm( Cpoint Base );
        
        bool IsIn( Cpoint Point );
        bool IsInLine( Primitive *Prim );
        bool Join( Primitive *Prim );
        
        Primitive *GetPercentFragment( double Val ); // Val E {0,1}
        
        int GetType()   { return type; };
        PCBObject* GetOwner() { return owner; };
      
    private:
        int type;
        CpointSortedArray *ComPointsArray;
        AngleSortedArray  *ArcAngleArray;
        Cpoint begin, end, center;  
        PCBObject *owner;
        Angle BeginAngle, EndAngle;
        double R;
        bool rev;
        void addpoint( Cpoint Point ); // dodaje punkt do wczesniej zainicjowanej tablicy sortujacej
};

WX_DEFINE_ARRAY_PTR( Primitive *,  PrimitiveArray );

#endif
