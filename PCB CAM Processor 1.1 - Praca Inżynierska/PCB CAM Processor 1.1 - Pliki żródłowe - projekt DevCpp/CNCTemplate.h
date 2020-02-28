///-----------------------------------------------------------------
///
/// @file      CNCTemplate.h
/// @author    rado4ever
/// Created:   2016-04-18 17:38:13
/// @section   DESCRIPTION
///            CNCTemplate class declaration
///
///------------------------------------------------------------------

#ifndef CNCTEMP
#define CNCTEMP

#include <wx/wx.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/notebook.h>

#include "MySource/inc/rx.h"
#include "MySource/inc/mybox.h"

class cncTemplate;
WX_DEFINE_ARRAY( cncTemplate*, cncArrayTemplate ); 
WX_DEFINE_ARRAY( wxTextCtrl*,  wxArrayTextCtrl ); 
WX_DEFINE_ARRAY( wxButton*,    wxArrayButton ); 


class cncTemplate
{
    public:
        cncTemplate( wxNotebook *Notebook, wxString Name, wxString Params, wxString Codes );
        void Resize() { mainbox->SetSize( notebookpage->GetSize() ); };
        void ButtonClick( unsigned int ButtonID );
        
        void Clear();
        
        // Getters functions
        bool Get( wxString VarName, wxString &Var );
        bool Get( wxString VarName, int &Var );
        bool Get( wxString VarName, double &Var );
        wxString GetName() { return name; };
        // Setters functions
        bool Set( wxString VarName, wxString Var );
        bool Set( wxString VarName, int Var );
        bool Set( wxString VarName, double Var );
        
        //save load
        wxString GetDataString();
        bool LoadDataFromString( wxString Text );

        
    private:
        wxPanel *notebookpage; 
        MyBox* mainbox;
        MyBoxArray      hideboxarray;
        wxArrayTextCtrl editarray;
        wxArrayButton   buttonarray;
        wxArrayString   editnames;
        wxString        name;
        wxString        sep;
        
        int countindex( wxString varname );
};

#endif    
