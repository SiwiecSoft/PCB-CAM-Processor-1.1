///-----------------------------------------------------------------
///
/// @file      rxRandom.cpp
/// @author    Rado4ever
/// Created:   2015-07-08 14:17:53
///
///------------------------------------------------------------------

#include "inc/rx.h"

int RandomValue( int min, int max )
{
    LARGE_INTEGER Val;
    long long Counter;
                
    QueryPerformanceCounter(&Val);
    Counter = Val.QuadPart;
                
    return (int)( Counter % ( max - min + 1 ) + min );
}

wxString RandomElement( wxString FileName )                                     // losuje jedna z lini pliku
{
    wxTextFile File;
    wxString Ret;
                
    File.Open( FileName );
    Ret = File.GetLine( RandomValue( 0, File.GetLineCount() -1 ) );
    File.Close();
    
    return Ret;
}

wxString RandomElement( wxTextFile* File )                                      // losuje jedna z lini pliku
{
    return File->GetLine( RandomValue( 0, File->GetLineCount() -1 ) );
}

wxString RandomElement( wxString SeparatedString, wxChar Separator )            // losuje element z separowanego tekstu
{
    return ElementOfString( RandomValue( 1, SeparatedString.Freq( Separator ) ), SeparatedString, Separator);   
}

wxString RandomPassword( int PasswordLen )                                      // losuje jedna z lini pliku
{
    // 48 - 57 - cyfry (1) grupa symboli
    // 65 - 90 - litery du¿e (2) grupa symboli
    // 97 - 122 - litery ma³e (3) grupa symboli
    
    wxString Ret = "";
    
    if ( PasswordLen > 0 )
    {
        for ( int i = 0; i < PasswordLen; i++ )
        {
            switch ( RandomValue(0,2) ) // wybór grupy symboli
            {
                case 0: Ret += RandomValue(48,57); Sleep(10);  break;
                case 1: Ret += RandomValue(65,90); Sleep(10);  break;              
                case 2: Ret += RandomValue(97,122); Sleep(10);  break;
            }
        }
                    
        Ret[ RandomValue( 0, PasswordLen -1 ) ] = '@'; // dodanie znaku specjalnego
    }
    return Ret;
}

