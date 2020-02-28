///-----------------------------------------------------------------
///
/// @file      NodeMeneger.cpp
/// @author    rado4ever
/// Created:   2016-09-29 21:24:56
/// @section   DESCRIPTION
///            NodeMeneger class implementation
///
///------------------------------------------------------------------

#include "NodeMeneger.h"

NodeMeneger::~NodeMeneger()
{
    Clear();
}

NodeMeneger::NodeMeneger()
{
    CurrentID = 0;
}

PCBNode *NodeMeneger::GetNodeByIndex( unsigned int Index )
{
    if ( Index < NodeArray.GetCount() ) return NodeArray.Item( Index );
    else                                return NULL;
}

PCBNode *NodeMeneger::GetNodeByID( unsigned int ID )
{
    for ( int i = 0; i < NodeArray.GetCount(); i++ ) 
        if ( NodeArray.Item(i)->ID == ID ) return NodeArray.Item(i);
        
    return NULL;
}

PCBNode *NodeMeneger::GetNodeByOriginID( unsigned int OriginID )
{
    for ( int i = 0; i < NodeArray.GetCount(); i++ ) 
        if ( NodeArray.Item(i)->OriginID == OriginID ) return NodeArray.Item(i);
        
    return NULL;
}

void NodeMeneger::GetSelected( PCBNodeArray *ReturnTable )
{
    ReturnTable->Clear();
    
    for ( int i = 0; i < NodeArray.GetCount(); i++ ) 
        if ( NodeArray.Item(i)->IsSelected() )
             ReturnTable->Add( NodeArray.Item(i) );
}

void NodeMeneger::RegisterNode( PCBNode *Pointer )
{
    Pointer->Register();
}

void NodeMeneger::UnRegisterNode( PCBNode *Pointer )
{
    if ( !Pointer->Register(false) ) // usuwamu noda bo nie potrzebny
    {
        delete Pointer;               // usuniecie obiektu
        NodeArray.Remove( Pointer );  // usuniecie pustedo wskaznika z tablicy;
    }
}

bool NodeMeneger::SelectByRect( Cpoint P1, Cpoint P2 )
{
    // zaznaczenie nodow ktore sa w tym obszarze rect    
    for ( int i = 0; i < NodeArray.GetCount(); i++ )
    {
        if ( IsLine ( &P1, &NodeArray.Item(i)->Position, &P2 ) )  NodeArray.Item(i)->Select();
    }
}

void NodeMeneger::Clear()
{
    WX_CLEAR_ARRAY( NodeArray );
    CurrentID = 0;
}

void NodeMeneger::LoadNode( wxString Params )
{
    PCBNode *NewNode;
    
    NewNode = PCBNode::New( Params );
    if ( NewNode )
    {
        NodeArray.Add( NewNode );
        if ( NewNode->ID > CurrentID ) CurrentID = NewNode->ID + 1;
    }
}

void NodeMeneger::LoadContent( wxString XMLData )
{ 
    wxArrayString asNodes;
    GetXLMBlocks( XMLData, "node", &asNodes, 1 );
    
    Clear();
    
    for ( int i = 0; i < asNodes.GetCount(); i++ )
    {
        LoadNode( asNodes.Item(i) );
    }
}

wxString NodeMeneger::GetSaveString()
{
    wxString Spacing = "\t", Ret = "<nodes>\n";
        for ( int i = 0; i < NodeArray.GetCount(); i++ ) Ret += Spacing + "<node>" + NodeArray.Item(i)->GetSaveString() + "</node>\n";
    Ret += "</nodes>\n";
    
    return Ret;
}

void NodeMeneger::DuplicateSelected( Cpoint Shift )
{
    unsigned int ChildAmount = NodeArray.Count();
    
    for ( unsigned int i = 0; i < ChildAmount; i++ ) // po wszyskich dzieciach
    {
        if ( NodeArray.Item(i)->IsSelected() ) // jesli zaznaczone
        {
            AddNode( NodeArray.Item(i)->Duplicate( Shift ) );
        }
    }  
}
