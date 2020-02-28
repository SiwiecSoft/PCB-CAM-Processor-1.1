///-----------------------------------------------------------------
///
/// @file      MyRequester.cpp
/// @author    Rado4ever
/// Created:   2014-04-22 22:26:53
/// @section   DESCRIPTION
///            MyRequester class implementation
///
///------------------------------------------------------------------

#include "inc/myrequester.h"

MyRequester::MyRequester( wxWindow *Parent )
{
    parent = Parent;
}

bool MyRequester::StringInclude( wxString Source, wxString Criterion )
{
    bool IsOk = false;
    
    for ( unsigned int i = 0; i < Source.Len(); i++ )
    {
        IsOk = false;
        
        for ( unsigned int j = 0; j < Criterion.Len(); j++ )
        {
            if ( Source[i] == Criterion[j] ) IsOk = true;
        }
        if ( !IsOk ) return false;
    }
    
    return true;
}

bool MyRequester::StringNotInclude( wxString Source, wxString Criterion )
{
    for ( unsigned int i = 0; i < Source.Len(); i++ )
    {
        for ( unsigned int j = 0; j < Criterion.Len(); j++ )
        {
            if ( Source[i] == Criterion[j] ) return false;
        }
    }
    
    return true;
}

void MyRequester::ReplaceChars( wxString& Source, wxString OldChars, char NewChar )
{
    for ( unsigned int i = 0; i < Source.Len(); i++ )
    {
        for ( unsigned int j = 0; j < OldChars.Len(); j++ )
        {
            if ( Source[i] == OldChars[j] ) Source[i] = NewChar;
        }
    }
}

double MyRequester::StringToDouble( wxString Source, wxString Separators )
{
    double Val = 0;
    
    ReplaceChars( Source, Separators, '.' );
    Source.ToDouble( &Val );
    
    return Val;
}

wxString MyRequester::IntToString( int Value, wxString Format )
{
    return wxString::Format( Format, Value );
}

wxString MyRequester::DoubleToString( double Value, wxString Format )
{
    return wxString::Format( Format, Value );
}

bool MyRequester::StringIsIntBetween( wxString Source, int min, int max )
{
    return ( !Source.IsEmpty() && Source.IsNumber() && wxAtoi( Source ) >= min && wxAtoi( Source ) <= max  );
}

bool MyRequester::StringIsIntBetween( wxString Source )
{
    return ( !Source.IsEmpty() && Source.IsNumber() );
}

bool MyRequester::StringIsDoubleBetween( wxString Source, double min, double max, wxString Separators )  // dokoñczyc
{
    double Val;
    
    ReplaceChars( Source, Separators, '.' );
    
    return ( !Source.IsEmpty() && Source.ToDouble( &Val ) && Val >= min && Val <= max  );
}

bool MyRequester::StringIsDoubleBetween( wxString Source, wxString Separators )
{
    double Val;
    
    ReplaceChars( Source, Separators, '.' );
    
    return ( !Source.IsEmpty() && Source.ToDouble( &Val ) );
}

bool MyRequester::AskUserInt( wxString InitValue, wxString Title )
{
    if ( DialogPos.x == 0 ) TextDialog = new wxTextEntryDialog( parent, "", Title, InitValue ,wxOK | wxCANCEL | wxCENTRE );
    else                    TextDialog = new wxTextEntryDialog( parent, "", Title, InitValue ,wxOK | wxCANCEL, DialogPos );
    
    do{
        if ( TextDialog->ShowModal() == wxID_OK )
        {
            s_Value = TextDialog->GetValue();
            i_Value = wxAtoi( s_Value );

            if ( StringIsIntBetween( s_Value ) )
            {   
                DialogPos = TextDialog->GetPosition();
                delete TextDialog;
                return true;
            }
        }
        else break;
    } 
    while ( !StringIsIntBetween( s_Value ) ); 
    
    DialogPos = TextDialog->GetPosition();
    delete TextDialog;
    return false;
}

bool MyRequester::AskUserInt( int min, int max, wxString InitValue, wxString Title )
{
    if ( DialogPos.x == 0 ) TextDialog = new wxTextEntryDialog( parent, wxString::Format("Dopuszczalny zakres [%d ; %d]",min, max ), Title, InitValue ,wxOK | wxCANCEL | wxCENTRE );
    else                    TextDialog = new wxTextEntryDialog( parent, wxString::Format("Dopuszczalny zakres [%d ; %d]",min, max ), Title, InitValue ,wxOK | wxCANCEL, DialogPos );
    
    do{
        if ( TextDialog->ShowModal() == wxID_OK )
        {
            s_Value = TextDialog->GetValue();
            i_Value = wxAtoi( s_Value );

            if ( StringIsIntBetween( s_Value, min, max ) )
            {   
                DialogPos = TextDialog->GetPosition();
                delete TextDialog;
                return true;
            }
        }
        else break;
    } 
    while ( !StringIsIntBetween( s_Value, min, max ) ); 
    
    DialogPos = TextDialog->GetPosition();
    delete TextDialog;
    return false;
}

bool MyRequester::AskUserDouble( wxString InitValue, wxString Title )
{
    if ( DialogPos.x == 0 ) TextDialog = new wxTextEntryDialog( parent, "", Title, InitValue ,wxOK | wxCANCEL | wxCENTRE );
    else                    TextDialog = new wxTextEntryDialog( parent, "", Title, InitValue ,wxOK | wxCANCEL, DialogPos );
    
    do{
        if ( TextDialog->ShowModal() == wxID_OK )
        {
            s_Value = TextDialog->GetValue();
            d_Value = StringToDouble( s_Value, s_Separators );
            
            if ( StringIsDoubleBetween( s_Value, s_Separators ) )
            {
                DialogPos = TextDialog->GetPosition();
                delete TextDialog;
                return true;
            }
        }
        else break;
    }
    while ( !StringIsDoubleBetween( s_Value, s_Separators ) );
    
    DialogPos = TextDialog->GetPosition();
    delete TextDialog;
    return false;
}

bool MyRequester::AskUserDouble( double min, double max, wxString InitValue, wxString Title )
{
    if ( DialogPos.x == 0 ) TextDialog = new wxTextEntryDialog( parent, wxString::Format("Dopuszczalny zakres [%f ; %f]",min, max ), Title, InitValue ,wxOK | wxCANCEL | wxCENTRE );
    else                    TextDialog = new wxTextEntryDialog( parent, wxString::Format("Dopuszczalny zakres [%f ; %f]",min, max ), Title, InitValue ,wxOK | wxCANCEL, DialogPos );
    
    do{
        if ( TextDialog->ShowModal() == wxID_OK )
        {
            s_Value = TextDialog->GetValue();
            d_Value = StringToDouble( s_Value, s_Separators );
            
            if ( StringIsDoubleBetween( s_Value, min, max, s_Separators ) )
            {
                DialogPos = TextDialog->GetPosition();
                delete TextDialog;
                return true;
            }
        }
        else break;
    }
    while ( !StringIsDoubleBetween( s_Value, min, max, s_Separators ) );
    
    DialogPos = TextDialog->GetPosition();
    delete TextDialog;
    return false;
}

bool MyRequester::AskUserStringInclude( wxString Criterion, wxString InitValue, wxString Title )
{
    if ( DialogPos.x == 0 ) TextDialog = new wxTextEntryDialog( parent, "Dopuszczalne znaki: " + Criterion, Title, InitValue ,wxOK | wxCANCEL | wxCENTRE );
    else                    TextDialog = new wxTextEntryDialog( parent, "Dopuszczalne znaki: " + Criterion, Title, InitValue ,wxOK | wxCANCEL, DialogPos );
    
    do{
        if ( TextDialog->ShowModal() == wxID_OK )
        {
            s_Value = TextDialog->GetValue();
            
            if ( !( s_Value.IsEmpty() || !StringInclude( s_Value, Criterion ) ) )
            {
                DialogPos = TextDialog->GetPosition();
                delete TextDialog;
                return true;
            }
        }
        else break;
    }
    while ( s_Value.IsEmpty() || !StringInclude( s_Value, Criterion ) );
    
    DialogPos = TextDialog->GetPosition();
    delete TextDialog;
    return false;
}

bool MyRequester::AskUserStringNotInclude( wxString Criterion, wxString InitValue, wxString Title )
{
    if ( DialogPos.x == 0 ) TextDialog = new wxTextEntryDialog( parent, Criterion.IsEmpty() ? "" : "Niedopuszczalne znaki: " + Criterion, Title, InitValue ,wxOK | wxCANCEL | wxCENTRE );
    else                    TextDialog = new wxTextEntryDialog( parent, Criterion.IsEmpty() ? "" : "Niedopuszczalne znaki: " + Criterion, Title, InitValue ,wxOK | wxCANCEL, DialogPos );

    do{
        if ( TextDialog->ShowModal() == wxID_OK )
        {
            s_Value = TextDialog->GetValue();
            
            if ( !( s_Value.IsEmpty() || !StringNotInclude( s_Value, Criterion ) ) )
            {
                DialogPos = TextDialog->GetPosition();
                delete TextDialog;
                return true;
            }
        }
        else break;
    }
    while ( s_Value.IsEmpty() || !StringNotInclude( s_Value, Criterion ) );
    
    DialogPos = TextDialog->GetPosition();
    delete TextDialog;
    return false;
}


int MyRequester::GetInt()
{
    return i_Value;
}

double MyRequester::GetDouble()
{
    return d_Value;
}

wxString MyRequester::GetString()
{
    return s_Value;
}

void MyRequester::SetDecimalSeparators( wxString Separators )
{
    if ( !Separators.IsEmpty() ) s_Separators = Separators;
}

wxString MyRequester::GetDecimalSeparators()
{
    return s_Separators;
}
