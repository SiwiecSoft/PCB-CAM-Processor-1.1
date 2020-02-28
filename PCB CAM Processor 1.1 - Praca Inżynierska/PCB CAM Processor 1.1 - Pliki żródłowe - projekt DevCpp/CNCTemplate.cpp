///-----------------------------------------------------------------
///
/// @file      CNCTemplate.cpp
/// @author    rado4ever
/// Created:   2016-04-18 17:38:13
/// @section   DESCRIPTION
///            CNCTemplate class implementation
///
///------------------------------------------------------------------

#include "CNCTemplate.h"

cncTemplate::cncTemplate( wxNotebook *Notebook, wxString Name, wxString Params, wxString Codes ) : name(Name)
{
    MyBox *TextBox;
	MyBox *MemoBox;
	MyBox *ParamBox;
	wxTextCtrl *Edit;
	wxButton   *Button;
	wxString N, D, T;
	
	sep = " ", sep[0] = 255;
    
    notebookpage = new wxPanel( Notebook, 0, wxPoint(0, 0), wxSize(0, 0));
	Notebook->AddPage( notebookpage, Name );
	
	mainbox = new MyBox( FIX_SIZE,0,VERTICAL );
	
	TextBox = new MyBox( FIX_SIZE,30,HORIZONTAL );
	TextBox->AddBox( new MyBox( FROM_CONTROL,0,HORIZONTAL,AUTO_SIZE,ALIGN_CENTER,Marg(5),MyBox::NewStaticText( notebookpage, "Parametry" ) ) );
	TextBox->AddBox( new MyBox( FLOAT_SIZE,0,VERTICAL ) );
	Button = new wxButton( notebookpage, 100000, wxT("Zwiñ") );
	buttonarray.Add( Button );
    TextBox->AddBox( new MyBox( FIX_SIZE,70,HORIZONTAL,AUTO_SIZE,ALIGN_CENTER,Marg(5), Button ) );
    mainbox->AddBox( TextBox );
    
    ParamBox = new MyBox( FIX_SIZE, Params.Freq(';') *20 +10, VERTICAL );
    hideboxarray.Add( ParamBox );
    mainbox->AddBox( ParamBox );
    
    if ( Params.Freq(';') < 2 )
    {
        TextBox->Hide();
        ParamBox->Hide();
    }
    
    for ( unsigned int i = 1; ; i++ )
	{
        N = ElementOfString( i*3 -2, Params, ';' );
        D = ElementOfString( i*3 -1, Params, ';' );
        T = ElementOfString( i*3   , Params, ';' );
        
        if ( N.IsEmpty() || D.IsEmpty() || T.IsEmpty() ) break;
        
        editnames.Add(N);
        
        Edit = new wxTextCtrl( notebookpage, 0, wxEmptyString );
        Edit->SetToolTip(T);
        editarray.Add( Edit );
        
        ParamBox->AddBox( new MyBox( FIX_SIZE,25,HORIZONTAL,AUTO_SIZE,ALIGN_CENTER,Marg(0,0,15,0),MyBox::NewStaticText( notebookpage, D ) ) );
        ParamBox->AddBox( new MyBox( FIX_SIZE,35,HORIZONTAL,AUTO_SIZE,ALIGN_CENTER,Marg(0,15,20,7), Edit ) );
    }
	
	for ( unsigned int i = 1; ; i++ )
	{
        N = ElementOfString( i*3 -2, Codes, ';' );
        D = ElementOfString( i*3 -1, Codes, ';' );
        T = ElementOfString( i*3   , Codes, ';' );
        
        if ( N.IsEmpty() || D.IsEmpty() || T.IsEmpty() ) break;
        
        editnames.Add(N);
	
    	TextBox = new MyBox( FIX_SIZE,30,HORIZONTAL );
    	TextBox->AddBox( new MyBox( FROM_CONTROL,0,HORIZONTAL,AUTO_SIZE,ALIGN_CENTER,Marg(5),MyBox::NewStaticText( notebookpage, D ) ) );
    	TextBox->AddBox( new MyBox( FLOAT_SIZE,0,VERTICAL ) );
    	Button = new wxButton( notebookpage, 100000 +i, wxT("Zwiñ") );
    	buttonarray.Add( Button );
        TextBox->AddBox( new MyBox( FIX_SIZE,70,HORIZONTAL,AUTO_SIZE,ALIGN_CENTER,Marg(5), Button ) );
        
        Edit = new wxTextCtrl( notebookpage, 0, wxEmptyString, wxPoint(0,0), wxSize(0,0), wxTE_DONTWRAP | wxTE_MULTILINE );
        Edit->SetToolTip(T);
        editarray.Add( Edit );
        MemoBox = new MyBox( FLOAT_SIZE,0,HORIZONTAL,AUTO_SIZE,ALIGN_CENTER,Marg(5,10,10,10),Edit );
        hideboxarray.Add( MemoBox );
        
        mainbox->AddBox( TextBox );
        mainbox->AddBox( MemoBox );
        
        if ( i > 1 ) ButtonClick( 100000 +i );
    }
    
    Resize();
}

void cncTemplate::Clear()
{
    for ( unsigned int i = 0; i < editarray.GetCount(); i++ ) editarray.Item(i)->Clear();
}

int cncTemplate::countindex( wxString varname )
{
    for ( unsigned int i = 0; i < editnames.GetCount(); i++ )
        if ( editnames.Item(i) == varname ) return i;
        
    return -1;
}

// Getters functions

bool cncTemplate::Get( wxString VarName, wxString &Var )
{    
    int i = countindex( VarName );
    if ( i > -1 ) { Var = editarray.Item(i)->GetValue(); return true; }
    return false;
}

bool cncTemplate::Get( wxString VarName, int &Var )
{    
    int i = countindex( VarName );
    if ( i > -1 ) { Var = wxAtoi( editarray.Item(i)->GetValue() ); return true; }
    return false;
}

bool cncTemplate::Get( wxString VarName, double &Var )
{    
    int i = countindex( VarName );
    if ( i > -1 ) { editarray.Item(i)->GetValue().ToDouble( &Var ); return true; }
    return false;
}

// Setters functions

bool cncTemplate::Set( wxString VarName, wxString Var )
{    
    int i = countindex( VarName );
    if ( i > -1 ) { editarray.Item(i)->SetValue( Var ); return true; }
    return false;
}

bool cncTemplate::Set( wxString VarName, int Var )
{    
    int i = countindex( VarName );
    if ( i > -1 ) { editarray.Item(i)->SetValue( wxString::Format( "%d", Var ) ); return true; }
    return false;
}

bool cncTemplate::Set( wxString VarName, double Var )
{    
    int i = countindex( VarName );
    if ( i > -1 ) { editarray.Item(i)->SetValue( wxString::Format( "%f", Var ) ); return true; }
    return false;
}

// Funkcja do obslugi zdarzenia

void cncTemplate::ButtonClick( unsigned int ButtonID )
{
    ButtonID -= 100000;
    if ( hideboxarray.Item( ButtonID )->IsHide() ) 
    {
        hideboxarray.Item( ButtonID )->Hide(false);
        buttonarray.Item( ButtonID )->SetLabel("Zwiñ");
    }
    else                                           
    {
        hideboxarray.Item( ButtonID )->Hide(true);
        buttonarray.Item( ButtonID )->SetLabel("Rozwiñ");
    }
    
    Resize();
}

wxString cncTemplate::GetDataString()
{
    char enter[3] = {13,10,0};
    
    wxString EditVal, Ret = "#START#" + name + enter;
    for ( unsigned int i = 0; i < editarray.GetCount(); i++ ) 
    {   
        EditVal = editarray.Item(i)->GetValue();
        if ( EditVal.IsEmpty() ) EditVal += " ";
        EditVal.Replace( "\n", sep );
        Ret += EditVal + enter;
    }
    return Ret + "#END#" + name;
}

bool cncTemplate::LoadDataFromString( wxString Text )
{
    wxString EditVal;
    Text = GetExpression( Text, "#START#" + name + "(.*?)#END#" + name, 1 );
    if ( Text.IsEmpty() ) return false;
    
    for ( unsigned int i = 0; i < editarray.GetCount() ; i++ )
	{
        EditVal = ElementOfString( i+1, Text, '\n' );
        EditVal.Replace( sep, "\n" );
        editarray.Item(i)->SetValue(EditVal);
    }
    
    return true;
}

