///-----------------------------------------------------------------
///
/// @file      PCBrPad.cpp
/// @author    rado4ever
/// Created:   2016-05-13 11:09:15
/// @section   DESCRIPTION
///            PCBrPad class implementation
///
///------------------------------------------------------------------

#include "PCBrPad.h"

PCBrPad::~PCBrPad()
{
    NodeMngr->UnRegisterNode( Node );
}

PCBrPad::PCBrPad( double Dimension, PCBNode *Node )
{
    this->Dimension = Dimension;
    this->Node = Node;
    
    NodeMngr->RegisterNode( Node );

    Select(false);
}

PCBrPad* PCBrPad::New( wxString Params )
{
    double   ReturnedDimension;
    PCBNode *ReturnedNode;
    
    if ( CheckConstructingString( Params, rpad, &ReturnedDimension, &ReturnedNode ) ) return new PCBrPad( ReturnedDimension, ReturnedNode );
    else                                                                              return NULL;
}

void PCBrPad::ReCalculate( double CutterRadius )
{
}

void PCBrPad::Draw( Cpoint Shift, wxString Col )
{
    DrawCircle( Node->Position + Shift, Dimension/2, IsSelected() ? rxColour( 150, 255, 150 ) : rxColour( 0, 255, 0 ) );
}

void PCBrPad::GetPrimitives( PrimitiveArray *ReplyArray, double CutterRadius )
{
    Cpoint Center =  Node->Position;
    ReplyArray->Add( new Primitive( Cpoint( Center + polar( Dimension/2 + CutterRadius, ZERO ) ), Cpoint( Center + polar( Dimension/2 + CutterRadius, -ZERO ) ), Center, this ) );
}

void PCBrPad::GetCommonPoints( Primitive *Prim )
{
}

bool PCBrPad::IsPointInside( Cpoint Point, double CutterRadius )
{   
   return abs( Point - Node->Position ) < Dimension/2 + CutterRadius + ZERO;
}

wxString PCBrPad::GetSaveString()
{
    return wxString::Format( "%i|%f|%i", rpad, Dimension, Node->ID );
}

PCBCore *PCBrPad::Duplicate()
{
    PCBNode *NewNode = NodeMngr->GetNodeByOriginID( Node->ID );
    
    if ( NewNode ) return new PCBrPad( Dimension, NewNode );
    else           return NULL;
}

void PCBrPad::Draw( double Dimension, Cpoint Point, wxString Col )
{
    DrawCircle( Point, Dimension/2, rxColour( 0, 255, 0 ) );
}
