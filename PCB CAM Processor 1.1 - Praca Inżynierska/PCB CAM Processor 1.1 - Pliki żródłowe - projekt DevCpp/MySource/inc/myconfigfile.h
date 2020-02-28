///-----------------------------------------------------------------
///
/// @file      myconfigfile.h
/// @author    rado4ever
/// Created:   2014-04-17 18:59:34
/// @section   DESCRIPTION
///            MyConfigFile class declaration
///
///------------------------------------------------------------------

#ifndef MYCONFIGFILELIBRARY
#define MYCONFIGFILELIBRARY

#include "wx.h"

class MyConfigFile : public wxTextFile
{
	private:
		 //wxTextFile MyTextFile;
		
	public:
        void MyOpen( wxString FileName );
        void MyClose();
        void MyClear();
        
		int       GetInt( wxString ParamName );
		double    GetDouble( wxString ParamName );
		wxString  GetString( wxString ParamName );

		wxString GetFile( bool WithEnters = true );
		
		void Set( wxString ParamName, int      Value, bool Begin = false );
		void Set( wxString ParamName, double   Value, bool Begin = false  );
		void Set( wxString ParamName, wxString Value, bool Begin = false  );
		
		void Remove( wxString ParamName );
};

#endif
