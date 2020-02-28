///-----------------------------------------------------------------
///
/// @file      xmlfunc.cpp
/// @author    rado4ever
/// Created:   2016-03-09 15:50:58
/// @section   DESCRIPTION
///            Obsluga plikow typu xml
///
///------------------------------------------------------------------

#include "xmlfunc.h"

wxString GetXLMBlock( wxString InText, wxString BlockDesc, bool FirstUse, unsigned char Mode )
{
    static int Start = 0;
    if ( FirstUse ) Start = 0;
    
    wxString Label, Mark;
    int OpenLabelEnd, OpenLabelBegin, BlockEnd, CloseLabelEnd, MarkCount = 1;
    int PosOpenMark = 0, PosCloseMark = 0;
    
    OpenLabelEnd = OpenLabelBegin = InText.find( BlockDesc, Start );
    
    for ( int i = OpenLabelBegin; i >= 0; i-- ) // szukanie pocz etykiety
    {
        if ( InText[i] == '<' ) 
        {
            OpenLabelBegin = i;
            break;
        }
    }
    
    for ( int i = OpenLabelEnd; i < InText.Len(); i++ ) // szukanie konca etykiety
    {
        if ( InText[i] == '>' ) 
        {
            OpenLabelEnd = i;
            break;
        }
    }
    
    Label = InText.Mid( OpenLabelBegin, OpenLabelEnd - OpenLabelBegin +1 );
    
    Mark  = InText.Mid( OpenLabelBegin, OpenLabelEnd - OpenLabelBegin ); // bez ostatniego '>'
    Mark  = Mark.BeforeFirst(' ');
    Mark  = Mark.AfterFirst('<');
    
    BlockEnd = OpenLabelEnd; // zaczynamy szukac od koncowki etykiety
    
    while ( MarkCount != 0 )
    {
        PosOpenMark  = InText.find( "<"  + Mark, BlockEnd );
        PosCloseMark = InText.find( "</" + Mark, BlockEnd );
        
        if ( PosOpenMark == -1 ) // jest znacznik zamykanacy
        {
            if ( PosCloseMark == -1 ) return "";
            else
            {
                MarkCount--;
                BlockEnd = PosCloseMark +1;
            }

        }
        else if ( PosCloseMark == -1 ) // byl znaczik otw
        {
            MarkCount++;
            BlockEnd = PosOpenMark +1;
        }
        else
        {
            if ( PosOpenMark < PosCloseMark ) // znalezjono znacznik otwierajacy
            {
                MarkCount++;
                BlockEnd = PosOpenMark +1;
            }
            else // znalezjono znacznik otwierajacy
            { 
                MarkCount--;
                BlockEnd = PosCloseMark +1;
            }
        }
    }
    
    BlockEnd -= 2; // to jest pozycja ostetniego znaku bloku np <a> wer</a> r jest ostatnim znakiem bloku a
    
    for ( int i = BlockEnd +1; i < InText.Len(); i++ ) // szukanie konca etykiety koncowej
    {
        if ( InText[i] == '>' ) 
        {
            CloseLabelEnd = i;
            break;
        }
    }
    
    Start =  CloseLabelEnd +1; // dla przyszlych wywolan
    
    // formulowanie wynikow
    if ( Mode == 0 ) return InText.Mid( OpenLabelBegin, CloseLabelEnd - OpenLabelBegin +1 ); // calosc z etykietami
    if ( Mode == 1 ) return InText.Mid( OpenLabelEnd +1, BlockEnd - OpenLabelEnd  );         // srodek bez etykiet
    if ( Mode == 2 ) return Label;                                                           // sama etykieta 
}

int GetXLMBlocks( wxString InText, wxString BlockDesc, wxArrayString *Ans, unsigned char Mode )
{
    wxString Item = GetXLMBlock( InText, BlockDesc, true, Mode );
    Ans->Clear();
    
    while ( !Item.IsEmpty() )
    {
        Ans->Add(Item);
        Item = GetXLMBlock( InText, BlockDesc, false, Mode );
    }
}
