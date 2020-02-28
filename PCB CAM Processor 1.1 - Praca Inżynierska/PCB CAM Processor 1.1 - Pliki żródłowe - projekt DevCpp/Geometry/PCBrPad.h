///-----------------------------------------------------------------
///
/// @file      PCBrPad.h
/// @author    rado4ever
/// Created:   2016-05-13 11:09:15
/// @section   DESCRIPTION
///            PCBsPad class declaration
///
///------------------------------------------------------------------

#ifndef PCBRPAD
#define PCBRPAD

#include "PCBPad.h"

class PCBrPad : public PCBPad
{
    public:
        // Konstruktory
        PCBrPad( double Dimension, PCBNode *Node );
        // Destruktory
        virtual ~PCBrPad();
        
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
        static PCBrPad* New( wxString Params );
        
        // Statyczna funkcja Draw
        static void Draw( double Dimension, Cpoint Point, wxString Col = "" );

    private:
        
};

WX_DEFINE_ARRAY_PTR( PCBrPad *,  PCBrPadArray );

#endif
