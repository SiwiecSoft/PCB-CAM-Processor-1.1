///-----------------------------------------------------------------
///
/// @file      PCBPad.h
/// @author    rado4ever
/// Created:   2016-09-28 17:30:25
/// @section   DESCRIPTION
///            PCBPad class declaration
///
///------------------------------------------------------------------

#ifndef PCBPAD
#define PCBPAD

#include "PCBObject.h"

class PCBPad : public PCBObject
{
    public:
        
        // Wirtualne metody od PCBCore
        virtual bool SelectWithNodes ( bool Sel = true ) { Node->Select( Sel ); return Select( Sel ); };   // Zaznacza wraz z nodami przestaje byc wirtualna
        virtual void Draw( Cpoint Shift = Cpoint( 0.0, 0.0 ), wxString Col = "" ) = 0;
        virtual bool IsPointInside( Cpoint Point, double CutterRadius = 0.0 ) = 0;
        virtual bool IsNodeInside ( PCBNode *NodeToTest ) { return ( NodeToTest == Node ); };
        virtual wxString GetSaveString() = 0;
        virtual PCBCore *Duplicate() = 0;
                 
        // Wirtualne metody od PCBCore::PCBObject
        virtual void ReCalculate( double CutterRadius = 0.0 ) = 0;
        virtual void GetPrimitives( PrimitiveArray *ReplyArray, double CutterRadius = 0.0 ) = 0;
        virtual void GetCommonPoints( Primitive *Prim ) = 0;
        
        // W³asne nie wirtualne
        PCBNode *GetNode()  { return Node; };
        int      GetNodeID(){ return Node->ID; };
        
        double GetDimension()               { return Dimension; };
        void   SetDimension( double Value ) { if ( Value > 0.0 ) Dimension = Value; };
        
        // Sprawdzanie poprawnosci stringa konstukcyjnego
        static bool CheckConstructingString( wxString ConstructingString, unsigned int ExpectedPrefix, double *ReturnedDimension, PCBNode **ReturnedNode )
        {
            if ( NodeMngr == NULL ) return false;
            
            unsigned int Prefix = wxAtoi( ElementOfString( 1, ConstructingString, '|' ) );
            unsigned int ID     = wxAtoi( ElementOfString( 3, ConstructingString, '|' ) );
            
            if ( Prefix != ExpectedPrefix ) return false;
            
            *ReturnedNode = NodeMngr->GetNodeByID( ID );
            if ( ReturnedNode != NULL && ElementOfString( 2, ConstructingString, '|' ).ToDouble( ReturnedDimension ) ) return true;
            else                                                                                                       return false;
        };
    
    protected:
        double Dimension;
        PCBNode *Node;
        
};

WX_DEFINE_ARRAY_PTR( PCBPad *, PCBPadArray );

#endif
