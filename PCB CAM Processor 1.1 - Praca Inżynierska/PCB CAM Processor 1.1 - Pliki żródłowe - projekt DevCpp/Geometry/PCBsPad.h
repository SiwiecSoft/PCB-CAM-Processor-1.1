///-----------------------------------------------------------------
///
/// @file      PCBsPad.h
/// @author    rado4ever
/// Created:   2016-04-18 20:52:15
/// @section   DESCRIPTION
///            PCBsPad class declaration
///
///------------------------------------------------------------------

#ifndef PCBSPAD
#define PCBSPAD

#include "PCBPad.h"

class PCBsPad : public PCBPad
{
    public:
        // Konstruktory
        PCBsPad( double Dimension, PCBNode *Node );
        // Destruktory
        virtual ~PCBsPad();
        
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
        static PCBsPad* New( wxString Params );
        
        // Statyczna funkcja Draw
        static void Draw( double Dimension, Cpoint Point, wxString Col = "" );

    private:
        Cpoint ContourPoints[4];
};

WX_DEFINE_ARRAY_PTR( PCBsPad *,  PCBsPadArray );

#endif
