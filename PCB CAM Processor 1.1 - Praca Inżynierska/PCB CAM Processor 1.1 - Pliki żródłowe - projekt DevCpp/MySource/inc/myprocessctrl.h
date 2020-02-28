///-----------------------------------------------------------------
///
/// @file      MyProcessCtrl.h
/// @author    Rado4ever
/// Created:   2015-02-22 16:04:50
/// @section   DESCRIPTION
///            MyProcessCtrl class declaration
///
///------------------------------------------------------------------

#ifndef MYPROCESSCTRL
#define MYPROCESSCTRL

#include <wx/wx.h>
#include <wx/process.h>
#include <wx/dynarray.h>

class MyProcessCtrl
{
    public:
        
        MyProcessCtrl( wxString Cmd = wxEmptyString );
        ~MyProcessCtrl();
        
        void Open( wxString Cmd );
        void Write( wxString Cmd );
        wxString Read();                // czyta bufor - ostatnie wpisy
        wxString GetConsole();          // czyta bufor i zwraca cala konsole 
        void ClearConsole();            // czysci konsole
        long GetPID();
        wxString GetCmd();
        void Kill( wxSignal Signal = wxSIGKILL );
        bool Exists();

    private:
        
        wxProcess *process;
        wxOutputStream *out;
        wxInputStream *in;
        long PID;
        wxString console;
        wxString cmd;
};

WX_DEFINE_ARRAY_PTR( MyProcessCtrl *, MyProcessCtrlArray );

#endif
