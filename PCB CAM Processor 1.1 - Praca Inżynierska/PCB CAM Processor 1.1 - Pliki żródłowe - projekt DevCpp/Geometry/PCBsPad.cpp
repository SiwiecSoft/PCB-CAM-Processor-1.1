///-----------------------------------------------------------------
///
/// @file      PCBsPad.cpp
/// @author    rado4ever
/// Created:   2016-04-18 20:52:15
/// @section   DESCRIPTION
///            PCBsPad class implementation
///
///------------------------------------------------------------------

/* Square pad contour descripcion

   (0)-----(1) y ^ 
    +       +    |
    +       +    |
   (3)-----(2)   |_______> x
   
*/

#include "PCBsPad.h"

PCBsPad::~PCBsPad()
{
    NodeMngr->UnRegisterNode( Node );
}

PCBsPad::PCBsPad( double Dimension, PCBNode *Node )
{
    this->Dimension = Dimension;
    this->Node = Node;
    
    NodeMngr->RegisterNode( Node );

    Select(false);
}

PCBsPad* PCBsPad::New( wxString Params )
{
    double   ReturnedDimension;
    PCBNode *ReturnedNode;
    
    if ( CheckConstructingString( Params, spad, &ReturnedDimension, &ReturnedNode ) ) return new PCBsPad( ReturnedDimension, ReturnedNode );
    else                                                                              return NULL;
}

void PCBsPad::ReCalculate( double CutterRadius )
{
    Cpoint Vx = Cpoint( Dimension / 2 + CutterRadius, 0 );
    Cpoint Vy = Cpoint( 0, Dimension / 2 + CutterRadius );
    
    ContourPoints[0] = Node->Position - Vx + Vy;
    ContourPoints[1] = Node->Position + Vx + Vy;
    ContourPoints[2] = Node->Position + Vx - Vy;
    ContourPoints[3] = Node->Position - Vx - Vy;
}

void PCBsPad::Draw( Cpoint Shift, wxString Col )
{
    ReCalculate();
    DrawPolygon( Node->Position + Shift, true, 4, Dimension/2, M_PI/4, IsSelected() ? rxColour( 150, 255, 150 ) : rxColour( 0, 255, 0 ) );
}

void PCBsPad::GetPrimitives( PrimitiveArray *ReplyArray, double CutterRadius )
{
    ReCalculate( CutterRadius );
    
    ReplyArray->Add( new Primitive( ContourPoints[0], ContourPoints[1], this ) );
    ReplyArray->Add( new Primitive( ContourPoints[1], ContourPoints[2], this ) );
    ReplyArray->Add( new Primitive( ContourPoints[2], ContourPoints[3], this ) );
    ReplyArray->Add( new Primitive( ContourPoints[3], ContourPoints[0], this ) );
}

void PCBsPad::GetCommonPoints( Primitive *Prim )
{
}

bool PCBsPad::IsPointInside( Cpoint Point, double CutterRadius )
{   
    ReCalculate( CutterRadius );
    
    return ( Point.real() > ContourPoints[3].real() &&
             Point.imag() > ContourPoints[3].imag() &&
             Point.real() < ContourPoints[1].real() &&
             Point.imag() < ContourPoints[1].imag()    );
}

wxString PCBsPad::GetSaveString()
{
    return wxString::Format( "%i|%f|%i", spad, Dimension, Node->ID );
}

PCBCore *PCBsPad::Duplicate()
{
    PCBNode *NewNode = NodeMngr->GetNodeByOriginID( Node->ID );
    
    if ( NewNode ) return new PCBsPad( Dimension, NewNode );
    else           return NULL;
}

void PCBsPad::Draw( double Dimension, Cpoint Point, wxString Col )
{
    DrawPolygon( Point, true, 4, Dimension/2, M_PI/4, rxColour( 0, 255, 0 ) );
}

