///-----------------------------------------------------------------
///
/// @file      Primitive.cpp
/// @author    rado4ever
/// Created:   2016-04-26 22:01:15
/// @section   DESCRIPTION
///            LinePrim class implementation
///
///------------------------------------------------------------------

#include "Primitive.h"
#include "MyGL.h"

// konstruktoty line

Primitive::Primitive( Cpoint Begin, Cpoint End, PCBObject *Owner )   
: begin( Begin ), 
  end( End ), 
  owner( Owner ),
  type( line ),
  rev( false )
{
    Calc();
}

// konstruktoty circ

Primitive::Primitive( Cpoint Begin, Cpoint End, Cpoint Center, PCBObject *Owner )   
: begin( Begin ), 
  end( End ), 
  center( Center ),
  owner( Owner ),
  type( arc ),
  rev( false )
{
    Calc();
}

Primitive::~Primitive()
{
}

void Primitive::addpoint( Cpoint Point )
{
    if ( type == line )
    {
        ComPointsArray->Add( new Cpoint( Point ) );
    }
    else
    {
        Angle Ang = arg( Point - center );
        if ( Ang < BeginAngle ) Ang += 2*M_PI;
        ArcAngleArray->Add( new Angle( Ang ) );
    }
}

void Primitive::Calc()
{
    if ( type == line )
    {
    }
    else
    {
        BeginAngle = arg( begin - center );
        EndAngle =   arg( end   - center );
        R = abs( begin - center ) + 0.000000001;
    }
}

void Primitive::Draw( wxString Col )
{
    if ( type == line ) 
    {
        DrawLine( begin, end, rxColour(Col) );
        DrawCircle( GetMiddlePoint(),0.03,rxColour("RED") ); 
        //DrawCircle( *begin,0.04,rxColour("RED") ); 
        //DrawCircle( *end,0.04,rxColour("BLACK") ); 
    }
    else              
    { 
        DrawArc ( center, abs( begin - center ), arg( begin - center ), arg( end - center ), rxColour(Col) ); 
        //DrawCircle( *begin,0.04,rxColour("RED") ); 
        //DrawCircle( *end,0.04,rxColour("BLACK") ); 
        DrawCircle( GetMiddlePoint(),0.03,rxColour("GREEN") ); 
    }
  
}

void Primitive::Init()
{
    if ( type == line )
    {
        ComPointsArray = new CpointSortedArray( CompareThrowLine );
        
        ComPointsArray->Add( new Cpoint( begin ) );
        ComPointsArray->Add( new Cpoint( end ) );
    }
    else
    {
        ArcAngleArray = new AngleSortedArray( CompareAngle );

        Angle Ang = EndAngle;
        if( Ang < BeginAngle ) Ang += 2*M_PI;
   
        ArcAngleArray->Add( new Angle( BeginAngle ) );
        ArcAngleArray->Add( new Angle( Ang ) );
    }
        
}

void Primitive::Cut( Primitive *Prim )
{
    if ( IsInLine( Prim ) || owner == Prim->owner ) return;
    
    if ( type == line && Prim->type == line )
    {
        double A[2],B[2],C[2],W,x,y;
        Cpoint D, Dp;
        Cpoint ComPoint;
        
        D  =       begin -       end;
        Dp = Prim->begin - Prim->end;
        
        // wyznaczenie równania mojej prostej
        if ( D.real() == 0 ) { A[0] = 1;                     B[0] = 0; C[0] = -begin.real(); }
        else                 { A[0] = -D.imag() / D.real();  B[0] = 1; C[0] = -A[0] * begin.real() - begin.imag(); }  // normalna funkcja y = ax + b
        
        // wyznaczenie równania prostej Prim
        if ( Dp.real() == 0 ) { A[1] = 1;                       B[1] = 0; C[1] = -Prim->begin.real(); }
        else                  { A[1] = -Dp.imag() / Dp.real();  B[1] = 1; C[1] = -A[1] * Prim->begin.real() - Prim->begin.imag(); }  // normalna funkcja y = ax + b
        
        // Wyliczenie punktu przeciecia
        W  = A[0]*B[1] - B[0]*A[1];
        if ( W != 0 )
        {
            ComPoint = Cpoint( ( B[0]*C[1] - C[0]*B[1] ) / W,
                               ( C[0]*A[1] - A[0]*C[1] ) / W );
            
            if ( IsLine(       &begin, &ComPoint,       &end ) &&
                 IsLine( &Prim->begin, &ComPoint, &Prim->end ) )
            {
                addpoint( ComPoint );
                Prim->addpoint( ComPoint );
            }
        }
    }
    else if ( type == line && Prim->type == arc )
    {
        // http://www.algorytm.org/geometria-obliczeniowa/wyznaczenie-punktow-przeciecia-okregu-z-prosta.html
        Prim->Calc();
        Cpoint V3 = GetPointOnLine( begin, end, Prim->center );
        double L1 = abs( Prim->center - V3 );
        
        if ( L1 <= Prim->R  )
        {
            double L2 = sqrt( Prim->R * Prim->R - L1*L1 );
            Cpoint Vp = ( end - begin ) * ( L2 / Len() );
            
            Cpoint V4 = Cpoint( V3+Vp );
            Cpoint V5 = Cpoint( V3-Vp );
            
            if ( IsLine( &begin, &V4, &end ) && Prim->IsIn( V4 ) ) { addpoint( V4 ); Prim->addpoint( V4 ); }
            if ( IsLine( &begin, &V5, &end ) && Prim->IsIn( V5 ) ) { addpoint( V5 ); Prim->addpoint( V5 ); }
        }
    }
    else if ( type == arc && Prim->type == line )
    {
        // http://www.algorytm.org/geometria-obliczeniowa/wyznaczenie-punktow-przeciecia-okregu-z-prosta.html
        Calc();
        Cpoint V3 = GetPointOnLine( Prim->begin, Prim->end, center );
        double L1 = abs( center - V3 );
        
        if ( L1 <= R )
        {
            double L2 = sqrt( R*R - L1*L1 );
            Cpoint Vp = ( Prim->end - Prim->begin ) * ( L2 / Prim->Len() );
            
            Cpoint V4 = V3+Vp;
            Cpoint V5 = V3-Vp;
            
            if ( IsLine( &Prim->begin, &V4, &Prim->end ) && IsIn( V4 ) ) { addpoint( V4 ); Prim->addpoint( V4 ); }
            if ( IsLine( &Prim->begin, &V5, &Prim->end ) && IsIn( V5 ) ) { addpoint( V5 ); Prim->addpoint( V5 ); }
        }
    }
    else if ( type == arc && Prim->type == arc )
    {
        // http://obliczeniowo.jcom.pl/?id=175&ckattempt=1
        Calc();
        Prim->Calc();
        Cpoint TempPoint;
        
        double L1 = abs( Prim->center - center );
        if ( abs( R - Prim->R ) < L1  &&  R + Prim->R > L1 )
        {
            Angle  ArgC1_C2 = arg( Prim->center - center ); // laczy moj srodek z jego
            Angle  A = acos( ( L1*L1 + R*R - Prim->R * Prim->R ) / ( 2 * L1 * R ) );

            TempPoint = center + polar( R, ArgC1_C2 + A );
            if( IsIn( TempPoint ) && Prim->IsIn( TempPoint ) ) { addpoint( TempPoint ); Prim->addpoint( TempPoint ); }
            
            TempPoint = center + polar( R, ArgC1_C2 - A );
            if( IsIn( TempPoint ) && Prim->IsIn( TempPoint ) ) { addpoint( TempPoint ); Prim->addpoint( TempPoint ); }
        }
    }
}

void Primitive::GetFragments( PrimitiveArray *OutArray )
{
    if ( type == line )
    {
        for ( int i = 0; i < ComPointsArray->GetCount() -1; i++ )
            OutArray->Add( new Primitive( *ComPointsArray->Item(i)  , 
                                          *ComPointsArray->Item(i+1), owner ) );
            
        WX_CLEAR_ARRAY( *ComPointsArray );
        delete ComPointsArray;
    }
    else
    {
        for ( int i = 0; i < ArcAngleArray->GetCount() -1; i++ )
            OutArray->Add( new Primitive( Cpoint( polar( R, *ArcAngleArray->Item(i) )   + center ), 
                                          Cpoint( polar( R, *ArcAngleArray->Item(i+1) ) + center ), 
                                          center, owner ) );
        
        WX_CLEAR_ARRAY( *ArcAngleArray );
        delete ArcAngleArray;  
    }
    
}

Cpoint Primitive::GetMiddlePoint() // dorobic dla luku !!!!
{
    if ( type == line )
    {
        return ( begin + end ) / Cpoint(2,0);
    }
    else
    {
        Calc();
        Angle Ang = EndAngle;
        if( Ang < BeginAngle ) Ang += 2*M_PI;
        return center + polar( R, ( BeginAngle + Ang ) / 2 );
    }
    
    
}

double Primitive::GetMinNorm( Cpoint Base )
{
    double nb = norm( begin - Base ), ne = norm( end - Base );
    return ( nb < ne ) ? nb : ne;
}

double Primitive::Len()
{
    if ( type == line ) return abs( begin - end );
    else                return R * AngleLen();
}

double Primitive::AngleLen()
{
    if ( type == line ) return -1.0;
    else
    {
        Angle Ang = EndAngle;
        if( Ang < BeginAngle ) Ang += 2*M_PI;
        return ( Ang - BeginAngle );
    }
}

bool Primitive::IsIn( Cpoint Point )
{
    if ( type == line ) // odleglosci punktow od ich rzotow sa zerowe
    {
        double B_E = abs( begin - end );
        double B_P = abs( begin - Point );
        double P_E = abs( Point  - end );
        
        if ( B_E - B_P > -MICRO && B_E - P_E > -MICRO ) return true; // B_P < B_E           
    }
    else
    {
        double Arg = arg( Point - center );
        if ( EndAngle < BeginAngle )
        {
            if  ( GELE_DOUBLE( Arg, BeginAngle, M_PI, MICRO ) || GELE_DOUBLE( Arg, -M_PI, EndAngle, MICRO ) ) return true;
        }
        else if ( GELE_DOUBLE( Arg, BeginAngle, EndAngle, MICRO ) ) return true;
    }
        
    return false;
}

bool Primitive::IsInLine( Primitive *Prim )
{
    if ( type == Prim->type )
    {
        if ( type == line ) // odleglosci punktow od ich rzotow sa zerowe
        {
            Cpoint pBB = GetPointOnLine( begin, end, Prim->begin );
            Cpoint pEE = GetPointOnLine( begin, end, Prim->end );
            
            double pBB_pB = abs( pBB - Prim->begin );
            double pEE_pE = abs( pEE - Prim->end );
            
            if ( pBB_pB < NANO && pEE_pE < NANO ) return true;
        }
        else // wspolsrodkowe i o tym samym promieniu
        {
            if ( abs( center - Prim->center ) < ZERO && 
                 abs( R      -  Prim->R )     < ZERO )  return true;
        }
    }
    
    return false;
}

bool Primitive::Join( Primitive *Prim )
{
    bool B, E, pB, pE;
    
    if ( IsInLine( Prim ) )
    {
        pB = IsIn( Prim->begin );
        pE = IsIn( Prim->end );
        
        B  = Prim->IsIn( begin );
        E  = Prim->IsIn( end );
        
        //wxMessageBox(wxString::Format("%d,%d   %d,%d", E,B,pE,pB));
        
        if ( E && B   &&   pE && pB )          // oba calkowicie w sobie
        {
            if ( abs( GetMiddlePoint() - Prim->GetMiddlePoint() ) < MICRO ); // wszpolne srodki to sa to te same prymitywy ( linie czy luki )
            else // sa to luki tworzace pelne kolo
            {
            }
        }
        else if ( E && B   &&   !(pE && pB) ) //2 przypadki wchlaniania - jeden calkowicie w drugim a drugi nie calkowicie w srodku czyli maja wspolny poczatek(koniec) ale jeden jest dluzszy
        {
            end   = Prim->end;
            begin = Prim->begin;
        }
        else if ( !(E && B)   &&   pE && pB );
        else if ( E && pB ) // 2 przypadki laczenia
        {
            end = Prim->end;
        }
        else if ( B && pE )
        {
            begin = Prim->begin;
        }
        else return false;
        
        return true;
    }
    
    return false;

}

Primitive *Primitive::GetPercentFragment( double Val )
{
    if ( type == line )
        return new Primitive( GetBeginPoint(), 
                              GetBeginPoint() + ( GetEndPoint() - GetBeginPoint() ) * Cpoint( Val, 0 ) );
    else
    {
        Calc();
        Angle NewAng, Ang = EndAngle;
        if( Ang < BeginAngle ) Ang += 2*M_PI;
        
        if ( rev )
        {
            NewAng = Ang + ( BeginAngle - Ang ) * Val;
            return new Primitive( center + polar( R, NewAng ), 
                                  end,
                                  center );
        }
        else
        {
            NewAng = BeginAngle + ( Ang - BeginAngle ) * Val;
            return new Primitive( begin, 
                                  center + polar( R, NewAng ),
                                  center );
        }
    }
}


