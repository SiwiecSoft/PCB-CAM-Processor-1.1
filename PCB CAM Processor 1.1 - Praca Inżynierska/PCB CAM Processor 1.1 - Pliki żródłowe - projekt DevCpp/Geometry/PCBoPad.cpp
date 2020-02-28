///-----------------------------------------------------------------
///
/// @file      PCBoPad.cpp
/// @author    rado4ever
/// Created:   2016-04-18 16:10:58
/// @section   DESCRIPTION
///            PCBoPad class implementation
///
///------------------------------------------------------------------

/* Octagonal pad contour descripcion

   (2)----(1)     
  /          \    y ^
(3)          (0)    |
 |            |     |
 |            |     |
(4)          (7)    |
  \          /      |
   (5)----(6)       |__________> x
   
*/

#include "PCBoPad.h"

PCBoPad::~PCBoPad()
{
    NodeMngr->UnRegisterNode( Node );
}

PCBoPad::PCBoPad( double Dimension, PCBNode *Node )
{
    this->Dimension = Dimension;
    this->Node = Node;
    
    NodeMngr->RegisterNode( Node );

    Select(false);
}

PCBoPad* PCBoPad::New( wxString Params )
{
    double   ReturnedDimension;
    PCBNode *ReturnedNode;
    
    if ( CheckConstructingString( Params, opad, &ReturnedDimension, &ReturnedNode ) ) return new PCBoPad( ReturnedDimension, ReturnedNode );
    else                                                                              return NULL;
}

void PCBoPad::ReCalculate( double CutterRadius )
{
    double R = Dimension / 2;
    double x = Node->Position.real();
    double y = Node->Position.imag();
    int i = 0;
    
    R = R/cos(M_PI/8);
    
    for ( double a = M_PI/8; a < 2*M_PI; a += M_PI/4 ) 
    {
        ContourPoints[i].real() = x + cos(a)*R;
        ContourPoints[i].imag() = y + sin(a)*R;
        i++;
    }
    
    //for( int i = 0; i < 8; i++ ) Lines[i]->Calc();
}

void PCBoPad::Draw( Cpoint Shift, wxString Col )
{
    ReCalculate();
    DrawPolygon( Node->Position + Shift, true, 8, Dimension/2, M_PI/8, IsSelected() ? rxColour( 150, 255, 150 ) : rxColour( 0, 255, 0 ) );
}

void PCBoPad::GetPrimitives( PrimitiveArray *ReplyArray, double CutterRadius )
{
    ReCalculate( CutterRadius );
    
    for ( int i = 0; i < 7; i++ )  ReplyArray->Add( new Primitive( ContourPoints[i], ContourPoints[i+1], this ) );

    ReplyArray->Add( new Primitive( ContourPoints[7], ContourPoints[0], this ) );
}

void PCBoPad::GetCommonPoints( Primitive *Prim )
{
}

bool PCBoPad::IsPointInside( Cpoint Point, double CutterRadius )
{    
    return ( 
             Point.real() > ContourPoints[4].real() &&
             Point.imag() > ContourPoints[5].imag() &&
             Point.real() < ContourPoints[0].real() &&
             Point.imag() < ContourPoints[1].imag() &&
             // nierownosci ograniczajace
             Point.imag() > -Point.real() + ContourPoints[4].real() + ContourPoints[4].imag() && 
             Point.imag() < -Point.real() + ContourPoints[0].real() + ContourPoints[0].imag() &&
             
             Point.imag() > Point.real() - ContourPoints[6].real() + ContourPoints[6].imag() && 
             Point.imag() < Point.real() - ContourPoints[2].real() + ContourPoints[2].imag()
             );
}

wxString PCBoPad::GetSaveString()
{
    return wxString::Format( "%i|%f|%i", opad, Dimension, Node->ID );
}

PCBCore *PCBoPad::Duplicate()
{
    PCBNode *NewNode = NodeMngr->GetNodeByOriginID( Node->ID );
    
    if ( NewNode ) return new PCBoPad( Dimension, NewNode );
    else           return NULL;
}

void PCBoPad::Draw( double Dimension, Cpoint Point, wxString Col )
{
    DrawPolygon( Point, true, 8, Dimension/2, M_PI/8, rxColour( 0, 255, 0 ) );
}
