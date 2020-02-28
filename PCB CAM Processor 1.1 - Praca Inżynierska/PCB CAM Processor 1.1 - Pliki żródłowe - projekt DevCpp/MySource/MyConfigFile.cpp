///-----------------------------------------------------------------
///
/// @file      MyConfigFile.cpp
/// @author    rado4ever
/// Created:   2014-04-17 18:59:34
/// @section   DESCRIPTION
///            MyConfigFile class implementation
///
///------------------------------------------------------------------

#include "inc/myconfigfile.h"

void MyConfigFile::MyOpen( wxString FileName )
{
    if ( wxFileExists( FileName ) )
    {
        Clear();
        Open( FileName );
    }
    else
    {
        Create( FileName );
        Open( FileName );
    }
}

void MyConfigFile::MyClose()
{
    if ( IsOpened() )
    {
        Write();
        Close();
    }
}

void MyConfigFile::MyClear()
{
    Clear();
}

int MyConfigFile::GetInt( wxString ParamName )
{
    unsigned int i = 0;
    int Val = 0;
    
    while ( i < GetLineCount() && GetLine(i) != ParamName ) i++;
    
    if ( ++i < GetLineCount() ) Val = wxAtoi( GetLine(i) );
    
    return Val;
}

double MyConfigFile::GetDouble( wxString ParamName )
{
    unsigned int i = 0;
    double Val = 0.0;
    
    while ( i < GetLineCount() && GetLine(i) != ParamName ) i++;
    
    if ( ++i < GetLineCount() ) GetLine(i).ToDouble( &Val );
    
    return Val;
}

wxString MyConfigFile::GetString( wxString ParamName )
{
    unsigned int i = 0;
    wxString Val = "";
    
    while ( i < GetLineCount() && GetLine(i) != ParamName ) i++;
    
    if ( ++i < GetLineCount() ) Val = GetLine(i);
    
    return Val;
}

wxString MyConfigFile::GetFile( bool WithEnters )
{
    wxString Val = "";
    
    for ( unsigned int i = 0; i < GetLineCount(); i++ )
    {
        Val += GetLine(i);
        if ( WithEnters ) Val += "\n";
    }
    
    return Val;
}

void MyConfigFile::Set( wxString ParamName, int Value, bool Begin )
{
    unsigned int i = 0;
    
    while ( i < GetLineCount() && GetLine(i) != ParamName ) i++;
    
    if ( i + 1 < GetLineCount() ) 
    {
        InsertLine( wxString::Format( "%d", Value ), i + 1 );
        RemoveLine( i + 2 );
    }
    else if ( i < GetLineCount() && GetLine(i) == ParamName ) 
    {
        AddLine( wxString::Format( "%d", Value ) );
    }
    else
    {
        if ( !Begin )
        {
            AddLine( ParamName );
            AddLine( wxString::Format( "%d", Value ) );
        }
        else
        {
            InsertLine( ParamName, 0 );
            InsertLine( wxString::Format( "%d", Value ), 1 );
        }
    }
}

void MyConfigFile::Set( wxString ParamName, double Value, bool Begin )
{
    unsigned int i = 0;
    
    while ( i < GetLineCount() && GetLine(i) != ParamName ) i++;
    
    if ( i + 1 < GetLineCount() ) 
    {
        InsertLine( wxString::Format( "%f", Value ), i + 1 );
        RemoveLine( i + 2 );
    }
    else if ( i < GetLineCount() && GetLine(i) == ParamName ) 
    {
        AddLine( wxString::Format( "%f", Value ) );
    }
    else
    {
        if ( !Begin )
        {
            AddLine( ParamName );
            AddLine( wxString::Format( "%f", Value ) );
        }
        else
        {
            InsertLine( ParamName, 0 );
            InsertLine( wxString::Format( "%f", Value ), 1 );
        }
    }
}

void MyConfigFile::Set( wxString ParamName, wxString Value, bool Begin )
{
    unsigned int i = 0;
    
    while ( i < GetLineCount() && GetLine(i) != ParamName ) i++;
    
    if ( i + 1 < GetLineCount() ) 
    {
        InsertLine( Value, i + 1 );
        RemoveLine( i + 2 );
    }
    else if ( i < GetLineCount() && GetLine(i) == ParamName ) 
    {
        AddLine( Value );
    }
    else
    {
        if ( !Begin )
        {
            AddLine( ParamName );
            AddLine( Value );
        }
        else
        {
            InsertLine( ParamName, 0 );
            InsertLine( Value, 1 );
        }
    }
}

void MyConfigFile::Remove( wxString ParamName )
{
    unsigned int i = 0;
    
    while ( i < GetLineCount() && GetLine(i) != ParamName ) i++;
    
    if ( i < GetLineCount() ) RemoveLine(i);
    if ( i < GetLineCount() ) RemoveLine(i);
}
