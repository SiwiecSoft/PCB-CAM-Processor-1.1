///-----------------------------------------------------------------
///
/// @file      CNCGenFrm.h
/// @author    rado4ever
/// Created:   2016-02-15 21:18:13
/// @section   DESCRIPTION
///            CNCGenFrm class declaration
///
///------------------------------------------------------------------

#ifndef __CNCGENFRM_H__
#define __CNCGENFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/timer.h>
#include <wx/filedlg.h>
////Header Include End

////Dialog Style Start
#undef CNCGenFrm_STYLE
#define CNCGenFrm_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxSTAY_ON_TOP | wxMAXIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

#include "MySource/inc/rx.h"

#include "MySource/inc/myconfigfile.h"
#include "MySource/inc/myrequester.h"
#include "MySource/inc/mybox.h"

#include "CNCTemplate.h"

class CNCGenFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		CNCGenFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Generator CNC"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = CNCGenFrm_STYLE);
		virtual ~CNCGenFrm();
	
		void Resize();
		
		void SetReView( bool State );
		
		wxString MainFileName;
		wxString MainFilePath;
		
		bool Review;
		bool CreatingDone;
		
		wxMenu *GenMenu;
		
		// obsluga szablonow
		cncArrayTemplate* cncTemplateArray1;
		void TemplateButtonClick(wxCommandEvent& event);
		
		void TemplateNew(wxCommandEvent& event);
		void TemplateOpen(wxCommandEvent& event);
		void TemplateSave(wxCommandEvent& event);
		void TemplateSaveAs(wxCommandEvent& event);
		void GenCNC(wxCommandEvent& event);
		void ReView(wxCommandEvent& event);
		void CNCGenFrmSize(wxSizeEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxNotebook *WxNotebook1;
		wxMenuBar *WxMenuBar1;
		wxFileDialog *WxSaveFileDialog1;
		wxTimer *WxTimer1;
		wxFileDialog *WxOpenFileDialog1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXNOTEBOOK1 = 1056,
			ID_MNU_SZABLON_1001 = 1001,
			ID_MNU_NOWY_1002 = 1002,
			ID_MNU_OTW_RZ_1003 = 1003,
			ID_MNU_ZAPISZ_1004 = 1004,
			ID_MNU_ZAPISZJAKO_1005 = 1005,
			ID_MNU_GENEROWANIE_1006 = 1006,
			ID_MNU_WYGENERUJKODCNC_1007 = 1007,
			ID_MNU_PODGL_D_1008 = 1008,
			
			ID_WXTIMER1 = 1048,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
