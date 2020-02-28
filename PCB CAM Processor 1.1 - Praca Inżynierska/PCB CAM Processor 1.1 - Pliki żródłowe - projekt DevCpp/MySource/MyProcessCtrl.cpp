///-----------------------------------------------------------------
///
/// @file      MyProcessCtrl.cpp
/// @author    Rado4ever
/// Created:   2015-02-22 16:04:50
/// @section   DESCRIPTION
///            MyProcessCtrl class implementation
///
///------------------------------------------------------------------

#include "inc/myprocessctrl.h"

//***************** TO JEST FUNKCJA WINDOWSA KTORA DZIALA!!! *******************

BOOL IsProcessRunning(DWORD pid)
{
    HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
    DWORD ret = WaitForSingleObject(process, 0);
    CloseHandle(process);
    return ret == WAIT_TIMEOUT;
}

//******************************************************************************

BOOL SendCloseToProcess(DWORD SetOfPID)
{
    HANDLE h = OpenProcess(PROCESS_ALL_ACCESS,false, SetOfPID);

    HWND hwnd = ::GetTopWindow(NULL);
    while(hwnd)
    {
        DWORD pid;
        DWORD dwThreadId = ::GetWindowThreadProcessId(hwnd, &pid);
         if(pid == SetOfPID)
         {    
              break;
         }
         hwnd = ::GetNextWindow(hwnd, GW_HWNDNEXT);
    }
    //DestroyWindow(hwnd);
    bool temp = IsWindow(hwnd); 
    LRESULT res = ::SendMessage(hwnd, WM_CLOSE, NULL, NULL);
    DWORD err = GetLastError(); 
    CloseHandle(hwnd);
    CloseHandle(h);
    return 0;
}

BOOL TerminateProcess(DWORD dwProcessId, UINT uExitCode)
{
    DWORD dwDesiredAccess = PROCESS_TERMINATE;
    BOOL  bInheritHandle  = FALSE;
    HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
    if (hProcess == NULL)
        return FALSE;

    BOOL result = TerminateProcess(hProcess, uExitCode);

    CloseHandle(hProcess);

    return result;
}

MyProcessCtrl::MyProcessCtrl( wxString Cmd ) // bez new konstruktor sie tez wykonuje !!!
{
    PID = -1;
    if( !Cmd.IsEmpty() )    Open( Cmd );
}

MyProcessCtrl::~MyProcessCtrl()
{
    if ( Exists() ) Kill();
}

void MyProcessCtrl::Open( wxString Cmd )
{
    process = wxProcess::Open(Cmd);
    cmd.Clear();
    
    if ( !process )
    {
        wxLogError(_T("Failed to launch the command."));
        return;
    }
    
    PID = process->GetPid();

    out = process->GetOutputStream();
    if ( !out )
    {
        wxLogError(_T("Failed to connect to child stdin"));
        return;
    }

    in = process->GetInputStream();
    if ( !in )
    {
        wxLogError(_T("Failed to connect to child stdout"));
        return;
    }
    
    ClearConsole();
    cmd = Cmd;
}

void MyProcessCtrl::Write( wxString Cmd )
{
    if ( Exists() )
    {
        out->Write(Cmd.c_str(), Cmd.Len());
    }
    else
    {
        wxLogError(_T("Proces nie istnieje"));
    }
}

wxString MyProcessCtrl::Read()
{
    wxString String;
    String.Clear();
    
    if ( Exists() )
    {
        while ( in->CanRead() )
        {
            wxChar buffer[4096];
            buffer[in->Read(buffer, WXSIZEOF(buffer) - 1).LastRead()] = _T('\0');

            String += buffer;
            console += buffer;
        }
    }
    /*else
    {
        wxLogError(_T("Proces nie istnieje"));
    }*/
    
    return String;
}

wxString MyProcessCtrl::GetConsole()
{
    Read();
    return console;
}

void MyProcessCtrl::ClearConsole()
{
    console.Clear();
}

long MyProcessCtrl::GetPID()
{
    return PID;
}

wxString MyProcessCtrl::GetCmd()
{
    return cmd;
}

void MyProcessCtrl::Kill( wxSignal Signal )
{
    if ( Exists() )
    {
        wxProcess::Kill( process->GetPid(), Signal );
    }
    else
    {
        wxLogError(_T("Proces nie istnieje"));
    }
    
    cmd.Clear();
    PID = -1;
}

bool MyProcessCtrl::Exists()
{
    //return ( PID >= 0 && wxProcess::Exists( PID ) );
    return ( PID >= 0 && IsProcessRunning( PID ) );
}
