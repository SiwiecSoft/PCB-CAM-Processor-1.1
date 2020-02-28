///-----------------------------------------------------------------
///
/// @file      PCBoPad.h
/// @author    rado4ever
/// Created:   2016-04-18 16:10:58
/// @section   DESCRIPTION
///            PCBoPad class declaration
///
///------------------------------------------------------------------

#ifndef PCBOPAD
#define PCBOPAD

#include "PCBPad.h"

class PCBoPad : public PCBPad
{
    public:
        // Konstruktory
        PCBoPad( double Dimension, PCBNode *Node );
        // Destruktory
        virtual ~PCBoPad();
        
        // Wirtualne metody od PCBCore
        virtual void Draw( Cpoint Shift = Cpoint( 0.0, 0.0 ), wxString Col = "" );
        virtual bool IsPointInside( Cpoint Point, double CutterRadius = 0.0 );
        virtual wxString GetSaveString();
        virtual PCBCore *Duplicate(); 
                 
        // Wirtualne metody od PCBCore::PCBObject
        virtual void ReCalculate( double CutterRadius = 0.0 );
        virtual void GetPrimitives( PrimitiveArray *ReplyArray, double CutterRadius = 0.0 );
        virtual void GetCommonPoints( Primitive *Prim );
        
        // Statyczny pseudo-konstruktor 
        static PCBoPad* New( wxString Params );
       
        // Statyczna funkcja Draw
        static void Draw( double Dimension, Cpoint Point, wxString Col = "" );

    private:
        Cpoint ContourPoints[8];
};

WX_DEFINE_ARRAY_PTR( PCBoPad *,  PCBoPadArray );

#endif
