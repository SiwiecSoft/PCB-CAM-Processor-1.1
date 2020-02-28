///-----------------------------------------------------------------
///
/// @file      PCBCore.h
/// @author    rado4ever
/// Created:   2016-09-28 15:05:23
/// @section   DESCRIPTION
///            PCBCore class declaration
///
///------------------------------------------------------------------



#ifndef PCBCORE
#define PCBCORE

#include <wx/wx.h>
//#include "PCBNode.h"
#include "MyGL.h"
#include "Primitive.h"
#include "NodeMeneger.h"

class PCBCore
{
    public:
        virtual ~PCBCore() {};
        
        // Obsuga selektow
        bool Select( bool Sel = true ) { Selected = Sel; return Sel; };
        bool IsSelected(){ return Selected; };
        // Ustanowienie NodeMenegera
        static void SetNodeMeneger( NodeMeneger *Meneger ) { NodeMngr = Meneger; };
        
        // Wirtualne metody
        virtual bool SelectWithNodes ( bool Sel = true ) = 0;                   // Zaznacza wraz z nodami
        virtual void Draw( Cpoint Shift = Cpoint( 0.0, 0.0 ), wxString Col = "" ) = 0;
        virtual bool IsPointInside( Cpoint Point, double CutterRadius = 0.0 ) = 0;
        virtual bool IsNodeInside ( PCBNode *NodeToTest ) = 0;
        virtual wxString GetSaveString() = 0;
        virtual PCBCore *Duplicate() = 0;
        
        static NodeMeneger  *NodeMngr; 
        
    protected:
        bool Selected;
};

WX_DEFINE_ARRAY_PTR( PCBCore *,  PCBCoreArray );

#endif
