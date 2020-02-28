///-----------------------------------------------------------------
///
/// @file      PCBNode.cpp
/// @author    rado4ever
/// Created:   2016-04-17 12:12:12
/// @section   DESCRIPTION
///            PCBNode class implementation
///
///------------------------------------------------------------------

#include "PCBNode.h"
#include "MyGL.h"

// pcbnode

PCBNode::PCBNode( unsigned int ID, double x, double y )
{
    this->ID = ID;
    Position = Cpoint(x, y);
    Select(false);
    
    RegisterValue = 0;
    OriginID = -1;
}

PCBNode::PCBNode( unsigned int ID, Cpoint Position )
{
    this->ID = ID;
    this->Position = Position;
    Select(false);
    
    RegisterValue = 0;
    OriginID = -1;
}

PCBNode* PCBNode::New( wxString Params )
{
    Cpoint Position;
    
    unsigned int ID  = wxAtoi( ElementOfString( 2, Params, '|' ) );
    
    if (  ElementOfString( 1, Params, '|' ) != "n" )                       return NULL;
    if ( !ElementOfString( 3, Params, '|' ).ToDouble( &Position.real() ) ) return NULL;
    if ( !ElementOfString( 4, Params, '|' ).ToDouble( &Position.imag() ) ) return NULL;
    
    return new PCBNode( ID, Position );
}

wxString PCBNode::GetSaveString()
{
    return wxString::Format( "n|%i|%f|%f", ID, Position.real(), Position.imag() );
}

void PCBNode::Draw( wxString Col )
{
    if ( IsSelected() ) 
    {
        DrawCircle( Position, 0.1, rxColour(Col), true );
    }
}

bool PCBNode::Register( bool LogicVal )
{
    if ( LogicVal ) RegisterValue++;
    else            RegisterValue--;
    
    return (bool)RegisterValue;
}

PCBNode *PCBNode::Duplicate( Cpoint Shift )
{
    PCBNode *NewNode = new PCBNode( 0, Position + Shift ); // Nowy node o zadnym ID
    NewNode->OriginID = ID; // Ustalamy mu siebie jako pochodzenie czyli duplikatora
    
    return NewNode;
}

// pcbhole

PCBHole::PCBHole( double Dimension, PCBNode *Node )
{
    this->Dimension = Dimension;
    this->Node = Node;
    Select(false);
}

PCBHole::PCBHole( wxString Params, PCBNodeArray *NodeArray, bool *Success )
{
    Select(false);
    
    int ID; 
    
    if ( ElementOfString( 1, Params, '|' ) != "h" ) // jesli podano z³y typ
    {
        *Success = false;
        delete this;
        return;
    }
    
    ElementOfString( 2, Params, '|' ).ToDouble( &Dimension );
    ID = wxAtoi( ElementOfString( 3, Params, '|' ) );

    for ( int i = 0; i < NodeArray->GetCount(); i++ )
    {
        if ( NodeArray->Item(i)->ID == ID )
        {
            Node = NodeArray->Item(i);
            *Success = true;
            return;
        }
    }
    
    *Success = false;
    delete this;
}

void PCBHole::Draw( wxString Col )
{
    double Nodex = Node->Position.real();
    double Nodey = Node->Position.imag();
    double R = Dimension/2;
    DrawCircle( Node->Position, R, rxColour("WHITE"), true );
    DrawCircle( Node->Position, R, rxColour(Col), false );
    DrawLine( Cpoint( Nodex -R, Nodey -R ), Cpoint( Nodex +R, Nodey +R ), rxColour(Col) );
    DrawLine( Cpoint( Nodex -R, Nodey +R ), Cpoint( Nodex +R, Nodey -R ), rxColour(Col) );
}

wxString PCBHole::GetSaveString()
{
    return wxString::Format( "h|%f|%i", Dimension, Node->ID );
}


