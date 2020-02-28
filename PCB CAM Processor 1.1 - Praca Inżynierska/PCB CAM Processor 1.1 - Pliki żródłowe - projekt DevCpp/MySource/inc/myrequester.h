///-----------------------------------------------------------------
///
/// @file      myrequester.h
/// @author    Rado4ever
/// Created:   2014-04-22 22:26:53
/// @section   DESCRIPTION
///            MyRequester class declaration
///
///------------------------------------------------------------------

#ifndef MYREQUESTERLIBRARY
#define MYREQUESTERLIBRARY

#include "wx.h"

class MyRequester
{
    private:
	wxWindow *parent;
        int i_Value;
        double d_Value;
        wxString s_Value;
        wxString s_Separators;
        
        wxPoint DialogPos;
        wxTextEntryDialog *TextDialog;
    
    public:
	MyRequester( wxWindow *Parent = NULL );
	
        bool StringInclude( wxString Source, wxString Criterion );
        bool StringNotInclude( wxString Source, wxString Criterion );
        void ReplaceChars( wxString& Source, wxString OldChars, char NewChar );
        
        double StringToDouble( wxString Source, wxString Separators = "." );
        wxString IntToString( int Value, wxString Format = "%d" );
        wxString DoubleToString( double Value, wxString Format = "%f" );
        
        bool StringIsIntBetween( wxString Source );
        bool StringIsIntBetween( wxString Source, int min, int max );
        bool StringIsDoubleBetween( wxString Source, wxString Separators = "." );
        bool StringIsDoubleBetween( wxString Source, double min, double max, wxString Separators = "." );
        
        bool AskUserInt( wxString InitValue = "", wxString Title = "Podaj liczbê ca³kowit¹" );
        bool AskUserInt( int min, int max, wxString InitValue = "", wxString Title = "Podaj liczbê ca³kowit¹" );
        bool AskUserDouble( wxString InitValue = "", wxString Title = "Podaj liczbê rzeczywist¹" );
        bool AskUserDouble( double min, double max, wxString InitValue = "", wxString Title = "Podaj liczbê rzeczywist¹" );
        bool AskUserStringInclude( wxString Criterion, wxString InitValue = "", wxString Title = "Podaj text" );
        bool AskUserStringNotInclude( wxString Criterion = "", wxString InitValue = "", wxString Title = "Podaj text" );
        
        int GetInt();
        double GetDouble();
        wxString GetString();
        
        void SetDecimalSeparators( wxString Separators );
        wxString GetDecimalSeparators();
        
};

#endif
