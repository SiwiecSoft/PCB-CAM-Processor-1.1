///-----------------------------------------------------------------
///
/// @file      PCBHole.h
/// @author    rado4ever
/// Created:   2016-09-28 15:15:23
/// @section   DESCRIPTION
///            PCBHole class declaration
///
///------------------------------------------------------------------

#ifndef PCBHOLE
#define PCBHOLE

#include "PCBCore.h"

class PCBHole2 : public PCBCore
{
    public:
        // Konstruktory
        virtual ~PCBHole2();
        // Destruktory
        PCBHole2( double Dimension, PCBNode *Node );
        
        // Wirtualne metody od PCBCore
        virtual bool SelectWithNodes ( bool Sel = true ) { Node->Select( Sel ); return Select( Sel ); };   // Zaznacza wraz z nodami
        virtual void Draw( Cpoint Shift = Cpoint( 0.0, 0.0 ), wxString Col = "" );
        virtual bool IsPointInside( Cpoint Point, double CutterRadius = 0.0 );
        virtual bool IsNodeInside ( PCBNode *NodeToTest ) { return ( NodeToTest == Node ); };
        virtual wxString GetSaveString(); 
        virtual PCBCore *Duplicate(); 
        
        // Wlasne nie wirtualne
        double GetDimension()               { return Dimension; };
        void   SetDimension( double Value ) { if ( Value > 0.0 ) Dimension = Value; };
        Cpoint GetPosition()                { return Node->Position; };
        
        // Statyczny pseudo-konstruktor 
        static PCBHole2* New( wxString Params );
        
        // Statyczna funkcja Draw
        static void Draw( double Dimension, Cpoint Point, wxString Col = "" );
        
    private:
        double   Dimension;
        PCBNode *Node;
};

WX_DEFINE_ARRAY_PTR( PCBHole2 *, PCBHole2Array );
WX_DEFINE_SORTED_ARRAY( PCBHole2 *, PCBHole2SortedArray );

static int CompareThrowDiameter( PCBHole2 *first, PCBHole2 *second )
{   
    if (  first->GetDimension() < second->GetDimension() ) return -1;
    else return 1;
}

#endif
