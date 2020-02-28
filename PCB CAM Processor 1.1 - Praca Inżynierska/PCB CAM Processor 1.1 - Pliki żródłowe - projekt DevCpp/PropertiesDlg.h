///-----------------------------------------------------------------
///
/// @file      PropertiesDlg.h
/// @author    rado4ever
/// Created:   2016-10-02 22:17:40
/// @section   DESCRIPTION
///            PropertiesDlg class declaration
///
///------------------------------------------------------------------

#ifndef __PROPERTIESDLG_H__
#define __PROPERTIESDLG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/combobox.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
////Header Include End

////Dialog Style Start
#undef PropertiesDlg_STYLE
#define PropertiesDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxSTAY_ON_TOP | wxDIALOG_NO_PARENT | wxCLOSE_BOX
////Dialog Style End

#include "Geometry/Group.h"

class PropertiesDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
		PCBNodeArray  NodeArray;
		PCBHole2Array HoleArray;
		PCBPadArray   PadArray;
		PCBsPathArray sPathArray;
		
	public:
		PropertiesDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("W³aœciwoœci"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = PropertiesDlg_STYLE);
		virtual ~PropertiesDlg();
		
		bool ReDrawRequest;
		
		void SetObjects( Group *GroupMeneger );
		void LoadNode( int Index );
		
		
		void WxComboBox2Updated(wxCommandEvent& event );
		void WxComboBox1Updated(wxCommandEvent& event );
		void WxComboBox3Updated(wxCommandEvent& event );
		void WxEdit1Updated(wxCommandEvent& event);
		void WxEdit2Updated(wxCommandEvent& event);
		void WxListBox1Selected(wxCommandEvent& event);
		
		
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTextCtrl *WxEdit2;
		wxStaticText *WxStaticText5;
		wxBoxSizer *WxBoxSizer8;
		wxTextCtrl *WxEdit1;
		wxStaticText *WxStaticText4;
		wxBoxSizer *WxBoxSizer7;
		wxListBox *WxListBox1;
		wxStaticBoxSizer *WxStaticBoxSizer1;
		wxComboBox *WxComboBox3;
		wxStaticText *WxStaticText3;
		wxBoxSizer *WxBoxSizer5;
		wxComboBox *WxComboBox2;
		wxStaticText *WxStaticText2;
		wxBoxSizer *WxBoxSizer4;
		wxComboBox *WxComboBox1;
		wxStaticText *WxStaticText1;
		wxBoxSizer *WxBoxSizer3;
		wxBoxSizer *WxBoxSizer2;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXEDIT2 = 1032,
			ID_WXSTATICTEXT5 = 1030,
			ID_WXEDIT1 = 1031,
			ID_WXSTATICTEXT4 = 1029,
			ID_WXLISTBOX1 = 1034,
			ID_WXCOMBOBOX3 = 1016,
			ID_WXSTATICTEXT3 = 1013,
			ID_WXCOMBOBOX2 = 1015,
			ID_WXSTATICTEXT2 = 1012,
			ID_WXCOMBOBOX1 = 1014,
			ID_WXSTATICTEXT1 = 1011,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
