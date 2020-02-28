///-----------------------------------------------------------------
///
/// @file      PCBsPath.cpp
/// @author    rado4ever
/// Created:   2016-04-18 20:56:47
/// @section   DESCRIPTION
///            PCBsPath class implementation
///
///------------------------------------------------------------------

#include "PCBsPath.h"

PCBsPath::~PCBsPath()
{
    NodeMngr->UnRegisterNode( Node[0] );
    NodeMngr->UnRegisterNode( Node[1] );
}

PCBsPath::PCBsPath( double Widht, PCBNode *Node1, PCBNode *Node2 )
{
    this->Widht = Widht;
    Node[0] = Node1;
    Node[1] = Node2;
    
    NodeMngr->RegisterNode( Node1 );
    NodeMngr->RegisterNode( Node2 );

    Select(false);
}

PCBsPath* PCBsPath::New( wxString Params )
{
    if ( NodeMngr == NULL ) return NULL;
    
    double Widht;
    PCBNode *N1, *N2;
            
    unsigned int Prefix = wxAtoi( ElementOfString( 1, Params, '|' ) );
    unsigned int ID1    = wxAtoi( ElementOfString( 3, Params, '|' ) );
    unsigned int ID2    = wxAtoi( ElementOfString( 4, Params, '|' ) );
    
    if ( Prefix != sline ) return NULL;
    
    N1 = NodeMngr->GetNodeByID( ID1 );
    N2 = NodeMngr->GetNodeByID( ID2 );
    
    if ( N1 && N2 && ElementOfString( 2, Params, '|' ).ToDouble( &Widht ) ) return new PCBsPath( Widht, N1, N2 );
    else                                                                    return NULL;
}

void PCBsPath::ReCalculate( double CutterRadius )
{
    Cpoint V1 = Node[1]->Position - Node[0]->Position;
    V1 = V1 / Cpoint( abs(V1) / ( Widht / 2 + CutterRadius ), 0 );   // wektor o kierunku sciezki i d³ rownej jej szerokosci
    Cpoint V2 = V1 * Cpoint(0,1);                                    // mnozenie razy i daje obrot o 90*
    
    ContourPoints[0] = Node[0]->Position + V2;
    ContourPoints[1] = Node[1]->Position + V2;
    
    ContourPoints[2] = Node[1]->Position - V2;
    ContourPoints[3] = Node[0]->Position - V2;
}

void PCBsPath::Draw( Cpoint Shift, wxString Col )
{
    Node[0]->Position += Shift;
    Node[1]->Position += Shift;
    
    ReCalculate();
    DrawQuad( ContourPoints[0], ContourPoints[1],ContourPoints[2], ContourPoints[3], IsSelected() ? rxColour( 100, 100, 255 ) : rxColour( 0, 0, 255 ) );
    
    DrawCircle( Node[0]->Position, Widht/2,      IsSelected() ? rxColour( 100, 100, 255 ) : rxColour( 0, 0, 255 ) );
    DrawCircle( Node[1]->Position, Widht/2,      IsSelected() ? rxColour( 100, 100, 255 ) : rxColour( 0, 0, 255 ) );
    
    Node[0]->Position -= Shift;
    Node[1]->Position -= Shift;
}

void PCBsPath::GetPrimitives( PrimitiveArray *ReplyArray, double CutterRadius )
{  
    ReCalculate( CutterRadius );
    
    ReplyArray->Add( new Primitive( ContourPoints[0], ContourPoints[1], this ) );
    ReplyArray->Add( new Primitive( ContourPoints[2], ContourPoints[3], this ) );
    ReplyArray->Add( new Primitive( ContourPoints[0], ContourPoints[3], Node[0]->Position, this ) );
    ReplyArray->Add( new Primitive( ContourPoints[2], ContourPoints[1], Node[1]->Position, this ) );
}

void PCBsPath::GetCommonPoints( Primitive *Prim )
{

}

bool PCBsPath::IsPointInside( Cpoint Point, double CutterRadius )
{
    double W = Widht/2 + CutterRadius;
    
    Cpoint V1 = Node[0]->Position;
    Cpoint V2 = Node[1]->Position;
    Cpoint V3 = ( V1 + V2 ) / Cpoint(2.0,0.0);      // punkt œrodkowy œcie¿ki
    Cpoint V4 = GetPointOnLine( V1, V2, Point );    // rzut punktu na prosta V1, V2

    bool IsInRect = LT_DOUBLE( abs( Point - V4 ), W, NANO )  &&  norm( V4 - V3 ) < norm( V1 - V3 );    // odleglosc punktu od jego rzutu mniejsza od W/2 i odleglosc rzutu od srodka mniejsz niz Len/2
    
    return  IsInRect || LT_DOUBLE( norm( V1 - Point ), W*W, NANO ) || LT_DOUBLE( norm( V2 - Point ), W*W, NANO );   // jest w prostokacie lub w jednym z okregow
}

wxString PCBsPath::GetSaveString()
{
    return wxString::Format( "%i|%f|%i|%i", sline, Widht, Node[0]->ID, Node[1]->ID );
}

PCBCore *PCBsPath::Duplicate()
{
    PCBNode *NewNode1 = NodeMngr->GetNodeByOriginID( Node[0]->ID );
    PCBNode *NewNode2 = NodeMngr->GetNodeByOriginID( Node[1]->ID );
    
    if ( NewNode1 && NewNode2 ) return new PCBsPath( Widht, NewNode1, NewNode2 );
    else                        return NULL;
}

bool PCBsPath::SelectWithNodes ( bool Sel )
{
    Select(Sel);
    Node[0]->Select(Sel);
    Node[1]->Select(Sel);
    return Sel;
}

void PCBsPath::Draw( double Widht, Cpoint P1, Cpoint P2, wxString Col )
{
    Cpoint V1 = P2 - P1;
    V1 = V1 / Cpoint( abs(V1) / ( Widht / 2 ), 0 );   // wektor o kierunku sciezki i d³ rownej jej szerokosci
    Cpoint V2 = V1 * Cpoint(0,1);                     // mnozenie razy i daje obrot o 90*
    
    DrawQuad( P1 + V2, P2 + V2, P2 - V2, P1 - V2, rxColour( 0, 0, 255 ) );
    
    DrawCircle( P1, Widht/2, rxColour( 0, 0, 255 ) );
    DrawCircle( P2, Widht/2, rxColour( 0, 0, 255 ) );
}

