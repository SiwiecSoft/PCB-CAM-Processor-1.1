///-----------------------------------------------------------------
///
/// @file      PCB CAM ProcessorFrm.h
/// @author    rado4ever
/// Created:   2016-02-08 19:43:24
/// @section   DESCRIPTION
///            PCB_CAM_ProcessorFrm class declaration
///
///------------------------------------------------------------------

#ifndef __PCB_CAM_PROCESSORFRM_H__
#define __PCB_CAM_PROCESSORFRM_H__

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
#include <wx/filedlg.h>
#include <wx/menu.h>
#include <wx/timer.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/aui/aui.h>
////Header Include End

////Dialog Style Start
#undef PCB_CAM_ProcessorFrm_STYLE
#define PCB_CAM_ProcessorFrm_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

#define TOOLCHECKEDTRUE2 32
#define TOOLCHECKEDTRUE  34
#define TOOLCHECKEDFALSE2 0
#define TOOLCHECKEDFALSE  2

#define TOOLBARCOUNT 2

//#include "Geometry/Line.h"
#include "Geometry/Geometry.h"
#include "Geometry/Group.h"
//#include "Geometry/PCBNode.h"
//#include "Geometry/MyGL.h"

// dodatkowe okna
#include "CNCGenFrm.h"
#include "PropertiesDlg.h"


class PCB_CAM_ProcessorFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		PCB_CAM_ProcessorFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("PCB CAM Processor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = PCB_CAM_ProcessorFrm_STYLE);
		virtual ~PCB_CAM_ProcessorFrm();

		HINSTANCE hInst;
        HWND hWnd;
        HDC hDC;
        HGLRC hRC;
        
        wxString FrmTitle;
        
        // dodatkowe okna
        CNCGenFrm     *CNCDialog;
        PropertiesDlg *PropertiesDialog;
        
        //kontenery glowne
        Group               *GroupMeneger;
        NodeMeneger         *NodeMngr;
        PCBHole2SortedArray *PCBHoles;
        
        // konternery pomocnicze
        PrimitiveArray    *PrimitivesToMake;
        PrimitiveArray    *PrimitivesToSim;
        PrimitiveArray    *ObjectPrims;
        PrimitiveArray    *ProductPrims;
        
        PCBHole2Array *HolesToMake;
        PCBHole2Array *HolesToSim;
        
        int SimulationCounter;
        double SimSpeed; // m/s
        Primitive *SimPrim;
        
        double Scale; // px/mm (inch)  scala*grid [px] rozstaw siatki
		double Grid;  // mm (inch)
		
		Dpoint GluSize;
		Dpoint GluPosition;
        
        bool GridVisible;
        bool PathFormatPaint;
        bool PadFormatPaint;
        bool MouseIsDown;
		int AddingMode;
		wxAuiToolBar *WxAuiToolBarTable[TOOLBARCOUNT];
		
		PCBNode *SelectedNode;
		
		bool ReDrawRequest;
		
		bool OnSelectClick;
		bool Shift;
		Cpoint ClickCpoint;
		Cpoint ClickCpointGrid;
		
		void CalcContour( double CutterRadius = 0.0 );
		void DrawWorkSpace();
		void DrawMillPreView();
		void DrawDrillPreView();
		
		bool SingleSelectClick();
		void DeleteSelectedItem();
        
        void CalculateGluSize();
        
        void SetSimView( bool SimView = true );
        
        Dpoint GetMousePosition ( bool RoundToGrid = true );
        Cpoint GetCMousePosition( bool RoundToGrid = true );
        
        
		void PCB_CAM_ProcessorFrmLeftDown(wxMouseEvent& event);
        
        void DrawGrid();
		
		bool IsToolChecked( wxAuiToolBarItem *Tool );
		void SetToolCheck( wxAuiToolBarItem *Tool, bool Check );
		void PCB_CAM_ProcessorFrmMouseWheel(wxMouseEvent& event);
		void RadioToolCheck( wxAuiToolBarItem *Tool ); // troche dziwna
		
		//zapis odczyt
		wxString MainFileName;
		wxString MainFilePath;
		
		void     SetWindowSettings( wxString Settings );
		wxString GetWindowSettings();
		
		void SaveProject( wxString FileName );
		void OpenProject( wxString FileName );
		
		// Metody w CAM.cpp
		void PrepareMillSim();
		void MakeMillFile();
		
		void PrepareDrillSim();
		void MakeDrillFile();
		
		

		void WxChoice1Selected(wxCommandEvent& event );
		void PCB_CAM_ProcessorFrmLeftUP(wxMouseEvent& event);
		void WxToolButton1Click(wxCommandEvent& event);
		void WxToolButton2Click(wxCommandEvent& event);
		void WxToolButton3Click(wxCommandEvent& event);
		void WxToolButton4Click(wxCommandEvent& event);
		void WxToolButton5Click(wxCommandEvent& event);
		void WxToolButton6Click(wxCommandEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		void PCB_CAM_ProcessorFrmSize(wxSizeEvent& event);
		void WxChoice2Selected(wxCommandEvent& event );
		void WxChoice3Selected(wxCommandEvent& event );
		void WxChoice4Selected(wxCommandEvent& event );
		void MenuNew(wxCommandEvent& event);
		void MenuOpen(wxCommandEvent& event);
		void MenuSave(wxCommandEvent& event);
		void MenuSaveAs(wxCommandEvent& event);
		void OpenGeneratorDialog(wxCommandEvent& event);
		void PCB_CAM_ProcessorFrmMouseEvents(wxMouseEvent& event);
		void WxTimerSimulationTimer(wxTimerEvent& event);
		void WxToolButton9Click(wxCommandEvent& event);
		void WxToolButton10Click(wxCommandEvent& event);
		void MenuCopy(wxCommandEvent& event);
		void MenuPaste(wxCommandEvent& event);
		void MenuCut(wxCommandEvent& event);
		void PCB_CAM_ProcessorFrmKeyDown(wxKeyEvent& event);
		void MenuDelete(wxCommandEvent& event);
		void MenuProperties(wxCommandEvent& event);
		void PCB_CAM_ProcessorFrmRightDown(wxMouseEvent& event);
		void PCB_CAM_ProcessorFrmKeyUp(wxKeyEvent& event);
		void WxChoice5Selected(wxCommandEvent& event );

		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxFileDialog *WxSaveFileDialog1;
		wxMenuBar *WxMenuBar1;
		wxTimer *WxTimer1;
		wxFileDialog *WxOpenFileDialog1;
		wxMenu *WxPopupMenu1;
		wxTimer *WxTimerSimulation;
		wxAuiManager *WxAuiManager1;
		wxStatusBar *WxStatusBar1;
		wxChoice *WxChoice1;
		wxAuiToolBar *WxAuiToolBar3;
		wxChoice *WxChoice3;
		wxChoice *WxChoice2;
		wxAuiToolBar *WxAuiToolBar2;
		wxChoice *WxChoice4;
		wxAuiToolBar *WxAuiToolBar1;
		wxTextCtrl *WxEdit1;
		wxChoice *WxChoice5;
		wxAuiToolBar *WxAuiToolBar5;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_MNU_PLIK_1023 = 1023,
			ID_MNU_NOWY_1025 = 1025,
			ID_MNU_OTW_RZ_1026 = 1026,
			ID_MNU_ZAPISZ_1027 = 1027,
			ID_MNU_ZAPISZJAKO_1028 = 1028,
			ID_MNU_NARZ_DZIA_1024 = 1024,
			ID_MNU_GENERATORCNC_1029 = 1029,
			
			ID_WXTIMER1 = 1015,
			ID_MNU_KOPIUJ_1036 = 1036,
			ID_MNU_WKLEJ_1037 = 1037,
			ID_MNU_WYTNIJ_1038 = 1038,
			ID_MNU_USU__1040 = 1040,
			ID_MNU_W_A_CIWO_CI_1042 = 1042,
			
			ID_WXTIMERSIMULATION = 1030,
			ID_WXSTATUSBAR1 = 1016,
			ID_WXCHOICE1 = 1014,
			ID_WXTOOLBUTTON1 = 1006,
			ID_WXAUITOOLBAR3 = 1005,
			ID_WXCHOICE3 = 1018,
			ID_WXCHOICE2 = 1017,
			ID_WXTOOLBUTTON4 = 1010,
			ID_WXTOOLBUTTON3 = 1009,
			ID_WXTOOLBUTTON2 = 1007,
			ID_WXAUITOOLBAR2 = 1004,
			ID_WXCHOICE4 = 1019,
			ID_WXTOOLBUTTON6 = 1012,
			ID_WXTOOLBUTTON5 = 1011,
			ID_WXAUITOOLBAR1 = 1003,
			ID_WXTOOLBUTTON10 = 1035,
			ID_WXTOOLBUTTON9 = 1034,
			ID_WXEDIT1 = 1033,
			ID_WXCHOICE5 = 1032,
			ID_WXAUITOOLBAR5 = 1031,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
