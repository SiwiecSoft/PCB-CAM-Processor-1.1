///-----------------------------------------------------------------
///
/// @file      CAM.cpp
/// @author    rado4ever
/// Created:   2016-05-01 21:43:24
/// @section   DESCRIPTION
///            PCB_CAM_ProcessorFrm class CAM modul extension
///
///------------------------------------------------------------------

#include "PCB CAM ProcessorFrm.h"

void PCB_CAM_ProcessorFrm::PrepareMillSim()
{ 
    Cpoint PrimBegin, PrimEnd, SimBegin( 0, 0 ), SimEnd;
    double Norm, Normb, Norme, MinNorm;
    int CurrentPrim = 0;
    bool ReverseRequired = false;
    
    WX_CLEAR_ARRAY( *PrimitivesToSim );
    
    // sotrowanie prymitywow w kolejnosci od punktu startowego kolejno w lancuch
    while ( PrimitivesToMake->GetCount() )
    {
        MinNorm = 1000000000000.0;
        CurrentPrim = -1;
        for ( int i = 0; i < PrimitivesToMake->GetCount(); i++ )
        {
            PrimBegin = PrimitivesToMake->Item(i)->GetBeginPoint();
            PrimEnd   = PrimitivesToMake->Item(i)->GetEndPoint();
            
            Normb = norm( PrimBegin - SimBegin ); // kwadraty odleglosci punktow koncowych od poczatku symilacji
            Norme = norm( PrimEnd   - SimBegin );
            Norm = ( Normb < Norme ) ? Normb : Norme;

            if ( LT_DOUBLE( Norm, MinNorm, MICRO ) || /* jesli jest naprawde blizej od innych*/
                 EQ_DOUBLE( Norm, MinNorm, MICRO ) &&  /*lub jesli jaest tak samo blisko*/
                 ( EQ_DOUBLE( PrimBegin.imag(), SimBegin.imag(), MICRO ) || EQ_DOUBLE( PrimEnd.imag(), SimBegin.imag(), MICRO ) ) ) /* i ma ta samo na y'ku dla ktoregos konca*/
            {
                MinNorm = Norm;
                CurrentPrim = i;
                
                if ( Normb < Norme ) 
                { 
                    SimEnd   = PrimEnd; 
                    ReverseRequired = false;
                }  
                else 
                { 
                    SimEnd   = PrimBegin; 
                    ReverseRequired = true;
                }
            }
        }
        
        if ( CurrentPrim == -1 ) return; // bardzo dziwna i niebezpieczna sytuacja

        PrimitivesToMake->Item( CurrentPrim )->Reverse( ReverseRequired );
        
        PrimitivesToSim->Add( PrimitivesToMake->Item( CurrentPrim ) );
        PrimitivesToMake->RemoveAt( CurrentPrim );
        
        SimBegin = SimEnd; // koniec staje sie poczatkiem dla kolejnej iteracji
    }
    
}

void PCB_CAM_ProcessorFrm::MakeMillFile()
{
    wxString PieceOfCode, Line, FileName, Name, ProgName, ProgExtension;
    double BeginX, BeginY, _R, _CR, _P;
    Cpoint BP,EP,MP,IJ;
    Primitive *Prim;
    cncTemplate *cncTemp = CNCDialog->cncTemplateArray1->Item(1);
    
    cncTemp->Get( "X", BeginX ); 
    cncTemp->Get( "Y", BeginY ); 
    
    ProgName = "Mill";
    cncTemp->Get( "Ext", ProgExtension ); 
    if ( !ProgExtension.IsEmpty() && ProgExtension[0] != '.' ) ProgExtension = "." + ProgExtension;
    
    Name = MainFileName + "_" + ProgName;
    Name.Replace( " ", "_" );
    Name.Replace( ".", "_" );
    FileName = Name + ProgExtension;
    
    MyConfigFile MillFile;
	wxString Enter = "  ";
	Enter[0] = 13; Enter[1] = 10;
	
	MillFile.MyOpen( FileName );
	MillFile.Clear();
	
	cncTemp->Get( "Start", PieceOfCode ); 
	PieceOfCode.Replace( "@NAME@", Name );
	PieceOfCode.Replace( "\n", Enter );
	MillFile.AddLine( PieceOfCode );
	
	int i = 0;
	while ( i < PrimitivesToSim->GetCount() )
	{
	    Prim = PrimitivesToSim->Item(i);
        BP   = Prim->GetBeginPoint();
       
        cncTemp->Get( "In", PieceOfCode ); 
        PieceOfCode.Replace( "@X@", wxString::Format( "%f", BP.real() + BeginX ) );
        PieceOfCode.Replace( "@Y@", wxString::Format( "%f", BP.imag() + BeginY ) );
        PieceOfCode.Replace( "\n", Enter );
        MillFile.AddLine( PieceOfCode );
        
        for ( ; i < PrimitivesToSim->GetCount(); i++ )
        {
            Prim = PrimitivesToSim->Item(i);
            BP   = Prim->GetBeginPoint();
            EP   = Prim->GetEndPoint();
            MP   = Prim->GetMiddlePoint();
            
            if ( Prim->GetType() == line ) cncTemp->Get( "Lin", PieceOfCode ); 
            else
            {
                IJ  = Prim->GetCenterPoint() - BP;
                _R  = Prim->GetR();
                _P  = Prim->AngleLen() * 180.0 / M_PI;
                _CR = _P < 180.0 ? _R : -_R;
                
                if ( Prim->IsReverse() ) cncTemp->Get( "G2", PieceOfCode ); 
                else cncTemp->Get( "G3", PieceOfCode ); 

                PieceOfCode.Replace( "@AX@", wxString::Format( "%f", MP.real() + BeginX ) );
                PieceOfCode.Replace( "@AY@", wxString::Format( "%f", MP.imag() + BeginY ) );
                PieceOfCode.Replace( "@I@", wxString::Format( "%f", IJ.real() ) );
                PieceOfCode.Replace( "@J@", wxString::Format( "%f", IJ.imag() ) );
                PieceOfCode.Replace( "@R@", wxString::Format( "%f", _R ) );
                PieceOfCode.Replace( "@CR@", wxString::Format( "%f", _CR ) );
                PieceOfCode.Replace( "@P@", wxString::Format( "%f", _P ) );
            }
            
            PieceOfCode.Replace( "@X@", wxString::Format( "%f",  EP.real() + BeginX ) );
            PieceOfCode.Replace( "@Y@", wxString::Format( "%f",  EP.imag() + BeginY ) );
            
            PieceOfCode.Replace( "\n", Enter );
            MillFile.AddLine( PieceOfCode );
            
            if ( i+1 < PrimitivesToSim->GetCount() )
            {
                if ( !EQ_DOUBLE( PrimitivesToSim->Item(i+1)->GetMinNorm(BP), 0.0, MICRO ) &&
                     !EQ_DOUBLE( PrimitivesToSim->Item(i+1)->GetMinNorm(EP), 0.0, MICRO ) )     break;
            }
        }
        
        cncTemp->Get( "Out", PieceOfCode ); 
        PieceOfCode.Replace( "@X@", wxString::Format( "%f", EP.real() + BeginX ) );
        PieceOfCode.Replace( "@Y@", wxString::Format( "%f", EP.imag() + BeginY ) );
        PieceOfCode.Replace( "\n", Enter );
        MillFile.AddLine( PieceOfCode );
        
        i++;
    }
    
    cncTemp->Get( "End", PieceOfCode ); 
    PieceOfCode.Replace( "\n", Enter );
	MillFile.AddLine( PieceOfCode );
	
	MillFile.MyClose();
	
	ShellExecute(NULL, "open", "Notepad", FileName, NULL, SW_SHOWNORMAL );
}

void PCB_CAM_ProcessorFrm::PrepareDrillSim()
{
    Cpoint LastPoint = Cpoint( 0.0, 0.0 );
    double Dist2, NextDist2, Diam;
    PCBHole2 *CurrentHole, *NextHole;
    bool ChangeDiam;
    int i;
    
    GroupMeneger->GetObjects( PCBHoles );
    
    HolesToMake->Clear();
    HolesToSim->Clear();
    
    for ( int i = 0; i < PCBHoles->GetCount(); i++ ) HolesToMake->Add( PCBHoles->Item(i) ); // przepisanie obiektow do nowej tablicy
    
    while ( HolesToMake->GetCount() ) // przypisanie pierwszego otworu
    {
        CurrentHole = HolesToMake->Item(0);
        Dist2 = norm( CurrentHole->GetPosition() - LastPoint );
        Diam  = CurrentHole->GetDimension();
        ChangeDiam = false;
    
        for ( i = 1; i < HolesToMake->GetCount(); i++ ) // szukanie najbliszego o tej sr co pierwszy
        {
            NextHole  = HolesToMake->Item(i);
            ChangeDiam = !EQ_DOUBLE( NextHole->GetDimension(), Diam, NANO );
            
            if ( ChangeDiam ) break;
            
            NextDist2 = norm( NextHole->GetPosition() - LastPoint ); // odleglosc badanego hola od ostatniego punktu
            if ( LT_DOUBLE( NextDist2, Dist2, MICRO ) || /* jesli jest naprawde blizej od innych*/
                 EQ_DOUBLE( NextDist2, Dist2, MICRO ) && EQ_DOUBLE( NextHole->GetPosition().imag(), LastPoint.imag(), MICRO ) ) /*lub jesli jaest tak samo blisko i ma tao samo na y'ku*/
            {
                CurrentHole = NextHole;
                Dist2 = NextDist2;
            }
        }
        
        if ( ChangeDiam && i == 1 ) LastPoint = Cpoint( 0.0, 0.0 );
        else                        LastPoint = CurrentHole->GetPosition(); // jedziemy rzad takich samych otworow a jak sie koncza to znow od poczatku ukl wsp             
        
        HolesToSim->Add( CurrentHole );
        HolesToMake->Remove( CurrentHole );
    }

}

void PCB_CAM_ProcessorFrm::MakeDrillFile()
{
    wxString PieceOfCode, Line, FileName, Name, ProgName, ProgExtension;
    double BeginX, BeginY;
    
    CNCDialog->cncTemplateArray1->Item(0)->Get( "X", BeginX ); 
    CNCDialog->cncTemplateArray1->Item(0)->Get( "Y", BeginY ); 
    
    ProgName = "Drill";
    CNCDialog->cncTemplateArray1->Item(0)->Get( "Ext", ProgExtension ); 
    if ( !ProgExtension.IsEmpty() && ProgExtension[0] != '.' ) ProgExtension = "." + ProgExtension;
    
    Name = MainFileName + "_" + ProgName;
    Name.Replace( " ", "_" );
    Name.Replace( ".", "_" );
    FileName = Name + ProgExtension;
    
    MyConfigFile DrillFile;
	wxString Enter = "  ";
	Enter[0] = 13; Enter[1] = 10;
	
	DrillFile.MyOpen( FileName );
	DrillFile.Clear();
	
	CNCDialog->cncTemplateArray1->Item(0)->Get( "Start", PieceOfCode ); 
	PieceOfCode.Replace( "@NAME@", Name );
	PieceOfCode.Replace( "\n", Enter );
	DrillFile.AddLine( PieceOfCode );
	
	CNCDialog->cncTemplateArray1->Item(0)->Get( "Drill", PieceOfCode ); 
	PieceOfCode.Replace( "\n", Enter );
    for ( int i = 0; i < HolesToSim->GetCount(); i++ ) // wiercenie
    {
        Line = PieceOfCode;
        Line.Replace( "@X@", wxString::Format( "%f", HolesToSim->Item(i)->GetPosition().real() + BeginX ) );
        Line.Replace( "@Y@", wxString::Format( "%f", HolesToSim->Item(i)->GetPosition().imag() + BeginY ) );
        
        DrillFile.AddLine( Line );
    }
    
    CNCDialog->cncTemplateArray1->Item(0)->Get( "End", PieceOfCode ); 
    PieceOfCode.Replace( "\n", Enter );
	DrillFile.AddLine( PieceOfCode );
	
	DrillFile.MyClose();
	
	ShellExecute(NULL, "open", "Notepad", FileName, NULL, SW_SHOWNORMAL );
}
