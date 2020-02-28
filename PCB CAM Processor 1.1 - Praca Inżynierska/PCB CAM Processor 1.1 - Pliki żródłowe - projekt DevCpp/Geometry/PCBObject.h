///-----------------------------------------------------------------
///
/// @file      PCBObject.h
/// @author    rado4ever
/// Created:   2016-04-18 15:47:23
/// @section   DESCRIPTION
///            PCBObject class declaration
///
///------------------------------------------------------------------

#ifndef PCBOBJECT
#define PCBOBJECT

#include "PCBCore.h"

class PCBObject : public PCBCore
{
    public:
        virtual ~PCBObject() {};
        
        // Wirtualne metody od PCBCore
        virtual bool SelectWithNodes ( bool Sel = true ) = 0;                   // Zaznacza wraz z nodami
        virtual void Draw( Cpoint Shift = Cpoint( 0.0, 0.0 ), wxString Col = "" ) = 0;
        virtual bool IsPointInside( Cpoint Point, double CutterRadius = 0.0 ) = 0;
        virtual bool IsNodeInside ( PCBNode *NodeToTest ) = 0;
        virtual wxString GetSaveString() = 0;
        virtual PCBCore *Duplicate() = 0;
                 
        // Nowe metody wirtualne
        virtual void ReCalculate( double CutterRadius = 0.0 ) = 0;
        virtual void GetPrimitives( PrimitiveArray *ReplyArray, double CutterRadius = 0.0 ) = 0;
        virtual void GetCommonPoints( Primitive *Prim ) = 0;
              
    protected:
        
};

WX_DEFINE_ARRAY_PTR( PCBObject *,  PCBObjectArray );

#endif
