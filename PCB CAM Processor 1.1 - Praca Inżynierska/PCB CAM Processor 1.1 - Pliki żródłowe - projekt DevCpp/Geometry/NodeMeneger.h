///-----------------------------------------------------------------
///
/// @file      NodeMeneger.h
/// @author    rado4ever
/// Created:   2016-09-29 21:24:56
/// @section   DESCRIPTION
///            NodeMeneger class declaration
///
///------------------------------------------------------------------

//#include "Geometry.h"
#include "PCBNode.h"
#include "../xmlfunc.h"

#ifndef NODEMENEGER
#define NODEMENEGER

class NodeMeneger
{
    public:
        ~NodeMeneger();
        NodeMeneger();
        
        PCBNode *GetNodeByIndex    ( unsigned int Index );
        PCBNode *GetNodeByID       ( unsigned int ID );
        PCBNode *GetNodeByOriginID ( unsigned int OriginID );
        
        void GetSelected( PCBNodeArray *ReturnTable );
        
        unsigned int AddNode( PCBNode *Pointer ) { Pointer->ID = CurrentID++; NodeArray.Add( Pointer ); return Pointer->ID; };
        
        unsigned int GetCount() { return NodeArray.GetCount(); };
        
        void RegisterNode  ( PCBNode *Pointer );
        void UnRegisterNode( PCBNode *Pointer );
        
        bool SelectAll   ( bool Sel ) { for ( unsigned int i = 0; i < NodeArray.GetCount(); i++ ) NodeArray.Item(i)->Select( Sel ); return Sel; };
        bool SelectByRect( Cpoint P1, Cpoint P2 );
        
        void Clear();
        
        void     LoadNode   ( wxString Params );
        void     LoadContent( wxString XMLData );
        wxString GetSaveString();
        
        void   DuplicateSelected( Cpoint Shift );
        // czyscimy id duplikatora zeby ponowna duplikacja tego samego noda nie spowodowala tego ze dwa rozne nody maja ten sam Origin :)
        void   ClearOriginIDs() { for ( unsigned int i = 0; i < NodeArray.GetCount(); i++ )  NodeArray.Item(i)->OriginID = -1; };
        
    private:
        PCBNodeArray  NodeArray;
        unsigned int  CurrentID;
};

#endif
