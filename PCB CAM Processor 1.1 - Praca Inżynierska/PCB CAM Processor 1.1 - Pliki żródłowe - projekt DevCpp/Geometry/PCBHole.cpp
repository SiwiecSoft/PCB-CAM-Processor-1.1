///-----------------------------------------------------------------
///
/// @file      PCBHole.cpp
/// @author    rado4ever
/// Created:   2016-04-17 12:12:12
/// @section   DESCRIPTION
///            PCBHole class implementation
///
///------------------------------------------------------------------

#include "PCBHole.h"

NodeMeneger *PCBCore::NodeMngr  = NULL;

PCBHole2::~PCBHole2()
{
    NodeMngr->UnRegisterNode( Node );
}

PCBHole2::PCBHole2( double Dimension, PCBNode *Node )
{
    this->Dimension = Dimension;
    this->Node = Node;
    
    NodeMngr->RegisterNode( Node );
    
    Select(false);
}

PCBHole2* PCBHole2::New( wxString Params )
{
    if ( NodeMngr == NULL ) return NULL;
    
    double Dimension;
    PCBNode *Node;
    
    unsigned int ID  = wxAtoi( ElementOfString( 3, Params, '|' ) );
    
    if ( ElementOfString( 1, Params, '|' ) != "h" ) return NULL;
    
    Node = NodeMngr->GetNodeByID( ID );
    if ( Node && ElementOfString( 2, Params, '|' ).ToDouble( &Dimension ) ) return new PCBHole2( Dimension, Node );
    else                                                                    return NULL; 
}

void PCBHole2::Draw( Cpoint Shift, wxString Col )
{
    Node->Position += Shift;
    
    if ( Col.IsEmpty() ) Col = IsSelected() ? "LIGHT GREY" : "BLACK";
    
    double Nodex = Node->Position.real();
    double Nodey = Node->Position.imag();
    double R = Dimension/2;
    DrawCircle( Node->Position, R, rxColour("WHITE"), true );
    DrawCircle( Node->Position, R, rxColour(Col), false );
    DrawLine( Cpoint( Nodex -R, Nodey -R ), Cpoint( Nodex +R, Nodey +R ), rxColour(Col) );
    DrawLine( Cpoint( Nodex -R, Nodey +R ), Cpoint( Nodex +R, Nodey -R ), rxColour(Col) );
    
    Node->Position -= Shift;
}

bool PCBHole2::IsPointInside( Cpoint Point, double CutterRadius )
{   
   return abs( Point - Node->Position ) < Dimension/2 + CutterRadius + ZERO;
}

wxString PCBHole2::GetSaveString()
{
    return wxString::Format( "h|%f|%i", Dimension, Node->ID );
}

PCBCore *PCBHole2::Duplicate()
{
    PCBNode *NewNode = NodeMngr->GetNodeByOriginID( Node->ID );
    
    if ( NewNode ) return new PCBHole2( Dimension, NewNode );
    else           return NULL;
}

void PCBHole2::Draw( double Dimension, Cpoint Point, wxString Col )
{
    double Nodex = Point.real();
    double Nodey = Point.imag();
    double R = Dimension/2;
    DrawCircle( Point, R, rxColour("WHITE"), true );
    DrawCircle( Point, R, rxColour(Col), false );
    DrawLine( Cpoint( Nodex -R, Nodey -R ), Cpoint( Nodex +R, Nodey +R ), rxColour(Col) );
    DrawLine( Cpoint( Nodex -R, Nodey +R ), Cpoint( Nodex +R, Nodey -R ), rxColour(Col) );
}

