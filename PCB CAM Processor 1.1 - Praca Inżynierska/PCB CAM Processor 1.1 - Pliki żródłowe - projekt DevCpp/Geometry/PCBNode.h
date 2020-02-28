///-----------------------------------------------------------------
///
/// @file      PCBNode.h
/// @author    rado4ever
/// Created:   2016-04-17 12:13:13
/// @section   DESCRIPTION
///            PCBNode class declaration
///
///------------------------------------------------------------------

/**** metoda wyznacznikowa
    
    A1x + B1y = C1
    A2x + B2y = C2
    
    W  = A1*B2 - B1*A2
    Wx = C1*B2 - B1*C2 dla -C   Wx = B1*C2 - C1*B2
    Wy = A1*C2 - C1*A2 dla -C   Wy = C1*A2 - A1*C2
    
    Gdy W != 0
    
    x = Wx / W
    y = Wy / W
    
**********************/

#ifndef PCBNODE
#define PCBNODE

#include "Dpoint.h"
#include "../MySource/inc/rx.h"

enum
{
    none = 0,
    rpad,
    spad,
    opad,
    sline,
    rline,
    duplicate
};

class PCBNode
{
    public:
        unsigned int ID;
        int          OriginID; // gdy brak pochodzenia to -1
        
        Cpoint Position;
        
        PCBNode( unsigned int ID, double x, double y );
        PCBNode( unsigned int ID, Cpoint Position );
        
        wxString GetSaveString();
        
        // Obsuga selektow
        bool Select( bool Sel = true ) { Selected = Sel; return Sel; };
        bool IsSelected(){ return Selected; };
        
        void Draw( wxString Col = "BLACK" );
        
        void SaveOldPosition() { OldPosition = Position; };
        void ShiftPosition( Cpoint Vec ) { Position = OldPosition + Vec; };
        
        bool Register( bool LogicVal = true );
        
        PCBNode *Duplicate( Cpoint Shift );
        
        // Statyczny pseudo-konstruktor 
        static PCBNode* New( wxString Params );
        
    private:
        bool         Selected;
        Cpoint       OldPosition;
        unsigned int RegisterValue;
};

WX_DEFINE_ARRAY_PTR( PCBNode *, PCBNodeArray );

class PCBHole
{
    public:
        double Dimension;
        PCBNode *Node;
        
        PCBHole( double Dimension, PCBNode *Node );
        PCBHole( wxString Params, PCBNodeArray *NodeArray, bool *Success );
        
        void Draw( wxString Col = "BLACK" );
        
        wxString GetSaveString();
        
        // Obsuga selektow
        bool Select( bool Sel = true ) { Selected = Sel; return Sel; };
        bool IsSelected(){ return Selected; };
        
    private:
        bool Selected;
};

WX_DEFINE_ARRAY_PTR( PCBHole *, PCBHoleArray );
WX_DEFINE_SORTED_ARRAY( PCBHole *, PCBHoleSortedArray );

#endif
