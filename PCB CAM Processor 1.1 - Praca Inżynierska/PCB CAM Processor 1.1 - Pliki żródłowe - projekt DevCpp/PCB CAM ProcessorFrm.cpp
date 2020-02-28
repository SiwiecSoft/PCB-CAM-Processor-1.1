///-----------------------------------------------------------------
///
/// @file      PCB CAM ProcessorFrm.cpp
/// @author    rado4ever
/// Created:   2016-02-08 19:43:24
/// @section   DESCRIPTION
///            PCB_CAM_ProcessorFrm class implementation
///
///------------------------------------------------------------------

/*******************************************************************************
*             UWAGA w celu zmiany w progtamie szukaj etykuet
* 
*                              [TOEDIT]
*
*
********************************************************************************/

#include "PCB CAM ProcessorFrm.h"

#define INITSPEED 0.050

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/PCB_CAM_ProcessorFrm_WxToolButton1_XPM.xpm"
#include "Images/PCB_CAM_ProcessorFrm_WxToolButton4_XPM.xpm"
#include "Images/PCB_CAM_ProcessorFrm_WxToolButton3_XPM.xpm"
#include "Images/PCB_CAM_ProcessorFrm_WxToolButton2_XPM.xpm"
#include "Images/PCB_CAM_ProcessorFrm_WxToolButton6_XPM.xpm"
#include "Images/PCB_CAM_ProcessorFrm_WxToolButton5_XPM.xpm"
////Header Include End

#include "Images/stopm.xpm"
#include "Images/playpause.xpm"

#include <wx/dynarray.h>

// deklaracje kontenerów
        
void PCB_CAM_ProcessorFrm::CalculateGluSize()
{
    GluSize.x = (double)GetClientSize().x / Scale;
    GluSize.y = (double)(GetClientSize().y + WxStatusBar1->GetSize().y ) / Scale;
}




/******** Nie wiem po co to   ******/
/******** Nie wiem po co to   ******/
/******** Nie wiem po co to   ******/
/******** Nie wiem po co to   ******/
int NodeId[3] = {-1,-1,-1};
int NodeIdCount;
/******** Nie wiem po co to   ******/
/******** Nie wiem po co to   ******/
/******** Nie wiem po co to   ******/
/******** Nie wiem po co to   ******/




//----------------------------------------------------------------------------
// PCB_CAM_ProcessorFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(PCB_CAM_ProcessorFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(PCB_CAM_ProcessorFrm::OnClose)
	EVT_KEY_UP(PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmKeyUp)
	EVT_KEY_DOWN(PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmKeyDown)
	EVT_SIZE(PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmSize)
	EVT_LEFT_DOWN(PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmLeftDown)
	EVT_LEFT_UP(PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmLeftUP)
	EVT_RIGHT_DOWN(PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmRightDown)
	EVT_MOUSEWHEEL(PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmMouseWheel)
	EVT_MOUSE_EVENTS(PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmMouseEvents)
	EVT_MENU(ID_MNU_NOWY_1025, PCB_CAM_ProcessorFrm::MenuNew)
	EVT_MENU(ID_MNU_OTW_RZ_1026, PCB_CAM_ProcessorFrm::MenuOpen)
	EVT_MENU(ID_MNU_ZAPISZ_1027, PCB_CAM_ProcessorFrm::MenuSave)
	EVT_MENU(ID_MNU_ZAPISZJAKO_1028, PCB_CAM_ProcessorFrm::MenuSaveAs)
	EVT_MENU(ID_MNU_GENERATORCNC_1029, PCB_CAM_ProcessorFrm::OpenGeneratorDialog)
	EVT_TIMER(ID_WXTIMER1,PCB_CAM_ProcessorFrm::WxTimer1Timer)
	EVT_MENU(ID_MNU_KOPIUJ_1036 , PCB_CAM_ProcessorFrm::MenuCopy)
	EVT_MENU(ID_MNU_WKLEJ_1037 , PCB_CAM_ProcessorFrm::MenuPaste)
	EVT_MENU(ID_MNU_WYTNIJ_1038 , PCB_CAM_ProcessorFrm::MenuCut)
	EVT_MENU(ID_MNU_USU__1040 , PCB_CAM_ProcessorFrm::MenuDelete)
	EVT_MENU(ID_MNU_W_A_CIWO_CI_1042 , PCB_CAM_ProcessorFrm::MenuProperties)
	EVT_TIMER(ID_WXTIMERSIMULATION,PCB_CAM_ProcessorFrm::WxTimerSimulationTimer)
	EVT_CHOICE(ID_WXCHOICE1,PCB_CAM_ProcessorFrm::WxChoice1Selected)
	EVT_MENU(ID_WXTOOLBUTTON1,PCB_CAM_ProcessorFrm::WxToolButton1Click)
	EVT_CHOICE(ID_WXCHOICE3,PCB_CAM_ProcessorFrm::WxChoice3Selected)
	EVT_CHOICE(ID_WXCHOICE2,PCB_CAM_ProcessorFrm::WxChoice2Selected)
	EVT_MENU(ID_WXTOOLBUTTON4,PCB_CAM_ProcessorFrm::WxToolButton4Click)
	EVT_MENU(ID_WXTOOLBUTTON3,PCB_CAM_ProcessorFrm::WxToolButton3Click)
	EVT_MENU(ID_WXTOOLBUTTON2,PCB_CAM_ProcessorFrm::WxToolButton2Click)
	EVT_CHOICE(ID_WXCHOICE4,PCB_CAM_ProcessorFrm::WxChoice4Selected)
	EVT_MENU(ID_WXTOOLBUTTON6,PCB_CAM_ProcessorFrm::WxToolButton6Click)
	EVT_MENU(ID_WXTOOLBUTTON5,PCB_CAM_ProcessorFrm::WxToolButton5Click)
	EVT_MENU(ID_WXTOOLBUTTON10,PCB_CAM_ProcessorFrm::WxToolButton10Click)
	EVT_MENU(ID_WXTOOLBUTTON9,PCB_CAM_ProcessorFrm::WxToolButton9Click)
	EVT_CHOICE(ID_WXCHOICE5,PCB_CAM_ProcessorFrm::WxChoice5Selected)
END_EVENT_TABLE()
////Event Table End

PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	// kontenery glowne
    PCBHoles     = new PCBHole2SortedArray( CompareThrowDiameter );
    NodeMngr     = new NodeMeneger();
    GroupMeneger = new Group();
    
    // konternery pomocnicze
    PrimitivesToMake = new PrimitiveArray();
    PrimitivesToSim  = new PrimitiveArray();
    
    ObjectPrims   = new PrimitiveArray();
    ProductPrims  = new PrimitiveArray();
    
    HolesToMake = new PCBHole2Array();
    HolesToSim  = new PCBHole2Array();
    
    CreateGUIControls();
}

PCB_CAM_ProcessorFrm::~PCB_CAM_ProcessorFrm()
{
}

void PCB_CAM_ProcessorFrm::CreateGUIControls()
{
	wxBitmap WxToolButton9_BITMAP (playpause_xpm);
    wxBitmap WxToolButton10_BITMAP (stopm_xpm);

    //Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	wxInitAllImageHandlers();   //Initialize graphic format handlers

	
	WxAuiManager1 = new wxAuiManager(this, wxAUI_MGR_ALLOW_FLOATING  | wxAUI_MGR_TRANSPARENT_HINT  | wxAUI_MGR_HINT_FADE  | wxAUI_MGR_NO_VENETIAN_BLINDS_FADE );

	WxAuiToolBar5 = new wxAuiToolBar(this, ID_WXAUITOOLBAR5, wxPoint(745, 2), wxSize(251, 22));

	wxArrayString arrayStringFor_WxChoice5;
	WxChoice5 = new wxChoice(WxAuiToolBar5, ID_WXCHOICE5, wxPoint(0, 0), wxSize(120, 23), arrayStringFor_WxChoice5, 0, wxDefaultValidator, wxT("WxChoice5"));
	WxChoice5->SetSelection(-1);
	WxAuiToolBar5->AddControl(WxChoice5);

	WxEdit1 = new wxTextCtrl(WxAuiToolBar5, ID_WXEDIT1, wxT("WxEdit1"), wxPoint(120, 0), wxSize(55, 23), 0, wxDefaultValidator, wxT("WxEdit1"));
	WxAuiToolBar5->AddControl(WxEdit1);

//	wxBitmap WxToolButton9_BITMAP (wxNullBitmap);
	wxBitmap WxToolButton9_DISABLE_BITMAP (wxNullBitmap);
	WxAuiToolBar5->AddTool(ID_WXTOOLBUTTON9, wxT("WxToolButton9"), WxToolButton9_BITMAP, WxToolButton9_DISABLE_BITMAP, wxITEM_NORMAL, wxT(""), wxT(""), NULL);

//	wxBitmap WxToolButton10_BITMAP (wxNullBitmap);
	wxBitmap WxToolButton10_DISABLE_BITMAP (wxNullBitmap);
	WxAuiToolBar5->AddTool(ID_WXTOOLBUTTON10, wxT("WxToolButton10"), WxToolButton10_BITMAP, WxToolButton10_DISABLE_BITMAP, wxITEM_NORMAL, wxT(""), wxT(""), NULL);

	WxAuiToolBar1 = new wxAuiToolBar(this, ID_WXAUITOOLBAR1, wxPoint(419, 2), wxSize(150, 22));

	wxBitmap WxToolButton5_BITMAP (PCB_CAM_ProcessorFrm_WxToolButton5_XPM);
	wxBitmap WxToolButton5_DISABLE_BITMAP (wxNullBitmap);
	WxAuiToolBar1->AddTool(ID_WXTOOLBUTTON5, wxT("WxToolButton5"), WxToolButton5_BITMAP, WxToolButton5_DISABLE_BITMAP, wxITEM_CHECK, wxT(""), wxT(""), NULL);

	wxBitmap WxToolButton6_BITMAP (PCB_CAM_ProcessorFrm_WxToolButton6_XPM);
	wxBitmap WxToolButton6_DISABLE_BITMAP (wxNullBitmap);
//	WxAuiToolBar1->AddTool(ID_WXTOOLBUTTON6, wxT("WxToolButton6"), WxToolButton6_BITMAP, WxToolButton6_DISABLE_BITMAP, wxITEM_CHECK, wxT(""), wxT(""), NULL);

	wxArrayString arrayStringFor_WxChoice4;
	arrayStringFor_WxChoice4.Add(wxT("0.2"));
	arrayStringFor_WxChoice4.Add(wxT("0.254"));
	arrayStringFor_WxChoice4.Add(wxT("0.3"));
	arrayStringFor_WxChoice4.Add(wxT("0.4"));
	arrayStringFor_WxChoice4.Add(wxT("0.5"));
	arrayStringFor_WxChoice4.Add(wxT("0.6"));
	arrayStringFor_WxChoice4.Add(wxT("0.7"));
	arrayStringFor_WxChoice4.Add(wxT("0.8"));
	arrayStringFor_WxChoice4.Add(wxT("0.9"));
	arrayStringFor_WxChoice4.Add(wxT("1.0"));
	arrayStringFor_WxChoice4.Add(wxT("1.1"));
	arrayStringFor_WxChoice4.Add(wxT("1.2"));
	arrayStringFor_WxChoice4.Add(wxT("1.3"));
	arrayStringFor_WxChoice4.Add(wxT("1.4"));
	arrayStringFor_WxChoice4.Add(wxT("1.5"));
	arrayStringFor_WxChoice4.Add(wxT("2.0"));
	arrayStringFor_WxChoice4.Add(wxT("Inna"));
	WxChoice4 = new wxChoice(WxAuiToolBar1, ID_WXCHOICE4, wxPoint(48, 0), wxSize(60, 23), arrayStringFor_WxChoice4, 0, wxDefaultValidator, wxT("WxChoice4"));
	WxChoice4->SetToolTip(wxT("Szerokoœæ œcie¿ki"));
	WxChoice4->SetSelection(3);
	WxAuiToolBar1->AddControl(WxChoice4);

	WxAuiToolBar2 = new wxAuiToolBar(this, ID_WXAUITOOLBAR2, wxPoint(174, 2), wxSize(232, 22));

	wxBitmap WxToolButton2_BITMAP (PCB_CAM_ProcessorFrm_WxToolButton2_XPM);
	wxBitmap WxToolButton2_DISABLE_BITMAP (wxNullBitmap);
	WxAuiToolBar2->AddTool(ID_WXTOOLBUTTON2, wxT("WxToolButton2"), WxToolButton2_BITMAP, WxToolButton2_DISABLE_BITMAP, wxITEM_CHECK, wxT(""), wxT(""), NULL);

	wxBitmap WxToolButton3_BITMAP (PCB_CAM_ProcessorFrm_WxToolButton3_XPM);
	wxBitmap WxToolButton3_DISABLE_BITMAP (wxNullBitmap);
	WxAuiToolBar2->AddTool(ID_WXTOOLBUTTON3, wxT("WxToolButton3"), WxToolButton3_BITMAP, WxToolButton3_DISABLE_BITMAP, wxITEM_CHECK, wxT(""), wxT(""), NULL);

	wxBitmap WxToolButton4_BITMAP (PCB_CAM_ProcessorFrm_WxToolButton4_XPM);
	wxBitmap WxToolButton4_DISABLE_BITMAP (wxNullBitmap);
	WxAuiToolBar2->AddTool(ID_WXTOOLBUTTON4, wxT("WxToolButton4"), WxToolButton4_BITMAP, WxToolButton4_DISABLE_BITMAP, wxITEM_CHECK, wxT(""), wxT(""), NULL);

	wxArrayString arrayStringFor_WxChoice2;
	arrayStringFor_WxChoice2.Add(wxT("0.8"));
	arrayStringFor_WxChoice2.Add(wxT("0.9"));
	arrayStringFor_WxChoice2.Add(wxT("1.0"));
	arrayStringFor_WxChoice2.Add(wxT("1.1"));
	arrayStringFor_WxChoice2.Add(wxT("1.2"));
	arrayStringFor_WxChoice2.Add(wxT("1.27"));
	arrayStringFor_WxChoice2.Add(wxT("1.3"));
	arrayStringFor_WxChoice2.Add(wxT("1.4"));
	arrayStringFor_WxChoice2.Add(wxT("1.5"));
	arrayStringFor_WxChoice2.Add(wxT("1.6"));
	arrayStringFor_WxChoice2.Add(wxT("1.7"));
	arrayStringFor_WxChoice2.Add(wxT("1.8"));
	arrayStringFor_WxChoice2.Add(wxT("1.9"));
	arrayStringFor_WxChoice2.Add(wxT("2.0"));
	arrayStringFor_WxChoice2.Add(wxT("2.1"));
	arrayStringFor_WxChoice2.Add(wxT("2.2"));
	arrayStringFor_WxChoice2.Add(wxT("2.3"));
	arrayStringFor_WxChoice2.Add(wxT("2.4"));
	arrayStringFor_WxChoice2.Add(wxT("2.5"));
	arrayStringFor_WxChoice2.Add(wxT("2.54"));
	arrayStringFor_WxChoice2.Add(wxT("3.0"));
	arrayStringFor_WxChoice2.Add(wxT("4.0"));
	arrayStringFor_WxChoice2.Add(wxT("5.0"));
	arrayStringFor_WxChoice2.Add(wxT("Inna"));
	WxChoice2 = new wxChoice(WxAuiToolBar2, ID_WXCHOICE2, wxPoint(72, 0), wxSize(60, 23), arrayStringFor_WxChoice2, 0, wxDefaultValidator, wxT("WxChoice2"));
	WxChoice2->SetToolTip(wxT("Œrednica pada"));
	WxChoice2->SetSelection(11);
	WxAuiToolBar2->AddControl(WxChoice2);

	wxArrayString arrayStringFor_WxChoice3;
	arrayStringFor_WxChoice3.Add(wxT("0.1"));
	arrayStringFor_WxChoice3.Add(wxT("0.2"));
	arrayStringFor_WxChoice3.Add(wxT("0.3"));
	arrayStringFor_WxChoice3.Add(wxT("0.4"));
	arrayStringFor_WxChoice3.Add(wxT("0.5"));
	arrayStringFor_WxChoice3.Add(wxT("0.6"));
	arrayStringFor_WxChoice3.Add(wxT("0.7"));
	arrayStringFor_WxChoice3.Add(wxT("0.8"));
	arrayStringFor_WxChoice3.Add(wxT("0.9"));
	arrayStringFor_WxChoice3.Add(wxT("1.0"));
	arrayStringFor_WxChoice3.Add(wxT("1.1"));
	arrayStringFor_WxChoice3.Add(wxT("1.2"));
	arrayStringFor_WxChoice3.Add(wxT("1.3"));
	arrayStringFor_WxChoice3.Add(wxT("1.4"));
	arrayStringFor_WxChoice3.Add(wxT("1.5"));
	arrayStringFor_WxChoice3.Add(wxT("2.0"));
	arrayStringFor_WxChoice3.Add(wxT("2.5"));
	arrayStringFor_WxChoice3.Add(wxT("3.0"));
	arrayStringFor_WxChoice3.Add(wxT("4.0"));
	arrayStringFor_WxChoice3.Add(wxT("5.0"));
	arrayStringFor_WxChoice3.Add(wxT("Inna"));
	WxChoice3 = new wxChoice(WxAuiToolBar2, ID_WXCHOICE3, wxPoint(132, 0), wxSize(60, 23), arrayStringFor_WxChoice3, 0, wxDefaultValidator, wxT("WxChoice3"));
	WxChoice3->SetToolTip(wxT("Œrednica otworu"));
	WxChoice3->SetSelection(9);
	WxAuiToolBar2->AddControl(WxChoice3);

	WxAuiToolBar3 = new wxAuiToolBar(this, ID_WXAUITOOLBAR3, wxPoint(11, 2), wxSize(150, 22));

	wxBitmap WxToolButton1_BITMAP (PCB_CAM_ProcessorFrm_WxToolButton1_XPM);
	wxBitmap WxToolButton1_DISABLE_BITMAP (wxNullBitmap);
	WxAuiToolBar3->AddTool(ID_WXTOOLBUTTON1, wxT("WxToolButton1"), WxToolButton1_BITMAP, WxToolButton1_DISABLE_BITMAP, wxITEM_CHECK, wxT(""), wxT(""), NULL);

	wxArrayString arrayStringFor_WxChoice1;
	arrayStringFor_WxChoice1.Add(wxT("1.0"));
	arrayStringFor_WxChoice1.Add(wxT("1.27"));
	arrayStringFor_WxChoice1.Add(wxT("0.635"));
	arrayStringFor_WxChoice1.Add(wxT("0.3175"));
	arrayStringFor_WxChoice1.Add(wxT("0.15875"));
	arrayStringFor_WxChoice1.Add(wxT("--------"));
	arrayStringFor_WxChoice1.Add(wxT("Inna"));
	WxChoice1 = new wxChoice(WxAuiToolBar3, ID_WXCHOICE1, wxPoint(24, 0), wxSize(70, 23), arrayStringFor_WxChoice1, 0, wxDefaultValidator, wxT("WxChoice1"));
	WxChoice1->SetSelection(1);
	WxAuiToolBar3->AddControl(WxChoice1);

	WxStatusBar1 = new wxStatusBar(this, ID_WXSTATUSBAR1);

	WxTimerSimulation = new wxTimer();
	WxTimerSimulation->SetOwner(this, ID_WXTIMERSIMULATION);

	WxPopupMenu1 = new wxMenu(wxT(""));WxPopupMenu1->Append(ID_MNU_KOPIUJ_1036, wxT("Kopiuj"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_WKLEJ_1037, wxT("Wklej"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_WYTNIJ_1038, wxT("Wytnij"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_USU__1040, wxT("Usuñ"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->AppendSeparator();
	WxPopupMenu1->Append(ID_MNU_W_A_CIWO_CI_1042, wxT("W³aœciwoœci"), wxT(""), wxITEM_NORMAL);

	WxOpenFileDialog1 =  new wxFileDialog(this, wxT("Zapisz"), wxT(""), wxT(""), wxT("*.pcb*"), wxOPEN);

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(40);

	WxMenuBar1 = new wxMenuBar();
	wxMenu *ID_MNU_PLIK_1023_Mnu_Obj = new wxMenu(0);
	ID_MNU_PLIK_1023_Mnu_Obj->Append(ID_MNU_NOWY_1025, wxT("Nowy"), wxT(""), wxITEM_NORMAL);
	ID_MNU_PLIK_1023_Mnu_Obj->Append(ID_MNU_OTW_RZ_1026, wxT("Otwórz"), wxT(""), wxITEM_NORMAL);
	ID_MNU_PLIK_1023_Mnu_Obj->Append(ID_MNU_ZAPISZ_1027, wxT("Zapisz"), wxT(""), wxITEM_NORMAL);
	ID_MNU_PLIK_1023_Mnu_Obj->Append(ID_MNU_ZAPISZJAKO_1028, wxT("Zapisz jako"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_PLIK_1023_Mnu_Obj, wxT("Plik"));
	
	WxMenuBar1->Append(WxPopupMenu1, wxT("Edycja"));
	
	wxMenu *ID_MNU_NARZ_DZIA_1024_Mnu_Obj = new wxMenu(0);
	ID_MNU_NARZ_DZIA_1024_Mnu_Obj->Append(ID_MNU_GENERATORCNC_1029, wxT("Generator CNC"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_NARZ_DZIA_1024_Mnu_Obj, wxT("Narzêdzia"));
	SetMenuBar(WxMenuBar1);

	WxSaveFileDialog1 =  new wxFileDialog(this, wxT("Wybierz plik"), wxT(""), wxT(""), wxT("*.pcb*"), wxSAVE);

	SetStatusBar(WxStatusBar1);
	WxAuiToolBar3->SetToolBitmapSize(wxSize(23,23));
	WxAuiToolBar3->Realize();
	WxAuiManager1->AddPane(WxAuiToolBar3, wxAuiPaneInfo().Name(wxT("WxAuiToolBar3_Pane")).Caption(wxT("WxAuiToolBar3")).Top().Dockable(false).CaptionVisible(false).DestroyOnClose(false).Floatable(false).Gripper(false).ToolbarPane().Row(0).Position(0).Layer(10));
	WxAuiToolBar2->SetToolBitmapSize(wxSize(24,24));
	WxAuiToolBar2->Realize();
	WxAuiManager1->AddPane(WxAuiToolBar2, wxAuiPaneInfo().Name(wxT("WxAuiToolBar2_Pane")).Caption(wxT("WxAuiToolBar2")).Top().Dockable(false).CaptionVisible(false).DestroyOnClose(false).Floatable(false).Gripper(false).ToolbarPane().Row(0).Position(0).Layer(10));
	WxAuiToolBar1->SetToolBitmapSize(wxSize(24,24));
	WxAuiToolBar1->Realize();
	WxAuiManager1->AddPane(WxAuiToolBar1, wxAuiPaneInfo().Name(wxT("WxAuiToolBar1_Pane")).Caption(wxT("WxAuiToolBar1")).Top().Dockable(false).CaptionVisible(false).DestroyOnClose(false).Floatable(false).Gripper(false).ToolbarPane().Row(0).Position(0).Layer(10));
	WxAuiToolBar5->Realize();
	WxAuiManager1->AddPane(WxAuiToolBar5, wxAuiPaneInfo().Name(wxT("WxAuiToolBar5_Pane")).Caption(wxT("WxAuiToolBar5")).Top().Dockable(false).CaptionVisible(false).DestroyOnClose(false).Floatable(false).Gripper(false).ToolbarPane().Row(0).Position(0).Layer(10));
	SetTitle(wxT("PCB CAM Processor"));
	SetIcon(wxNullIcon);
	SetSize(8,8,1217,600);
	Center();
	WxAuiManager1->Update();
	
	////GUI Items Creation End
	
	FrmTitle = wxT("PCB CAM Processor ver. 1.1");
	SetTitle( FrmTitle );
	
	SetSize(0,0,1100,600);
	SetMinSize( wxSize(750,580) );
	Center();
	
	WxPopupMenu1->FindItem( ID_MNU_KOPIUJ_1036 )->SetText( "Grupuj" );
	WxPopupMenu1->FindItem( ID_MNU_WKLEJ_1037 ) ->SetText( "Rozgrupuj" );
	WxPopupMenu1->FindItem( ID_MNU_WYTNIJ_1038 )->SetText( "Duplikuj" );

	
	SetFocus(); // MUSI BY? !!!!
    hInst = GetModuleHandle(NULL);
    hWnd = (HWND)GetHandle();
    EnableOpenGL(hWnd, &hDC, &hRC);

	WxAuiToolBarTable[0] = WxAuiToolBar1;
	WxAuiToolBarTable[1] = WxAuiToolBar2;
	
	//WxAuiToolBar2->FindToolByIndex(0)->Show(false);
	
	GridVisible     = true;
	PathFormatPaint = false;
    PadFormatPaint  = false;
    Shift = false;
	AddingMode = none;
	SetToolCheck( WxAuiToolBar3->FindTool( ID_WXTOOLBUTTON1 ), GridVisible );
	
	SetFocus();
	
	// itial value
	
	Scale = 10; // px/mm (inch)  scala*grid [px] rozstaw siatki
	//Grid  = 1;  // mm (inch)
	WxChoice1->GetStringSelection().ToDouble( &Grid );
	
	CalculateGluSize();
	
	GluPosition = Dpoint (-3.0, -3.0 );
    SimSpeed = INITSPEED;
    
    NodeIdCount  = 0;
    
    SimPrim = new Primitive ( Cpoint( 0,0 ), Cpoint( 0,0 ) );
    
    // Dodatkowe okna
    CNCDialog        = new CNCGenFrm(this);
    PropertiesDialog = new PropertiesDlg(this);
    
    ReDrawRequest = true;
    
    // Dodanie nazw szablonow do listy wybierasa na glownym menu
    for ( unsigned int i = 0; i < CNCDialog->cncTemplateArray1->GetCount(); i++ ) WxChoice5->Append( CNCDialog->cncTemplateArray1->Item(i)->GetName() );
    WxChoice5->SetSelection(0);
    
    WxEdit1->SetValue( wxString::Format( "%3.2f",INITSPEED ) );
    
    SetSimView(false);
    
    PCBCore::SetNodeMeneger( NodeMngr );
}

void PCB_CAM_ProcessorFrm::SetSimView( bool SimView )
{
    if ( SimView )
    {
        WxAuiToolBar2->Enable(false);
        WxAuiToolBar1->Enable(false);
        WxAuiToolBar5->Enable(true);
    }
    else
    {
        WxAuiToolBar2->Enable(true);
        WxAuiToolBar1->Enable(true);
        WxAuiToolBar5->Enable(false);
    }
    
    ReDrawRequest = true;
}

void PCB_CAM_ProcessorFrm::OnClose(wxCloseEvent& event)
{
    DisableOpenGL(hWnd, hDC, hRC);
    Destroy();
}

Dpoint PCB_CAM_ProcessorFrm::GetMousePosition( bool RoundToGrid )
{
    Dpoint MousePoint = GluPosition;
	
	MousePoint.x +=       (double)ScreenToClient( wxGetMousePosition() ).x / (double) GetClientSize().x * GluSize.x;
	MousePoint.y += ( 1 - (double)ScreenToClient( wxGetMousePosition() ).y / (double)(GetClientSize().y + WxStatusBar1->GetSize().y ) ) * GluSize.y;
	
	if ( RoundToGrid )
	{
        MousePoint.x = round( MousePoint.x / Grid ) * Grid;
        MousePoint.y = round( MousePoint.y / Grid ) * Grid;
    }
	
	return MousePoint;
}

Cpoint PCB_CAM_ProcessorFrm::GetCMousePosition( bool RoundToGrid )
{
    Dpoint MousePoint = GetMousePosition( RoundToGrid );
    return Cpoint( MousePoint.x, MousePoint.y );
}

bool PCB_CAM_ProcessorFrm::IsToolChecked( wxAuiToolBarItem *Tool )
{
    if ( Tool->GetState() == TOOLCHECKEDTRUE || Tool->GetState() == TOOLCHECKEDTRUE2 ) return true;
    else                                                                               return false;

}

void PCB_CAM_ProcessorFrm::SetToolCheck( wxAuiToolBarItem *Tool, bool Check )
{
    if ( Check ) Tool->SetState( TOOLCHECKEDTRUE );
    else         Tool->SetState( TOOLCHECKEDFALSE );
}

void PCB_CAM_ProcessorFrm::RadioToolCheck( wxAuiToolBarItem *Tool )
{
    for ( unsigned int i = 0; i < TOOLBARCOUNT; i++ )
    {
        for ( unsigned int j = 0; j < WxAuiToolBarTable[i]->GetToolCount() ; j++ ) 
        {
            SetToolCheck( WxAuiToolBarTable[i]->FindToolByIndex(j), false );
        }
        //WxAuiToolBarTable[i]->Update();
    }
    if ( Tool != NULL ) SetToolCheck( Tool, true );
}

/*
 * WxChoice1Selected
 */
void PCB_CAM_ProcessorFrm::WxChoice1Selected(wxCommandEvent& event ) //[TOEDIT]
{
	if ( WxChoice1->GetSelection() == 4 )
	{
        wxMessageBox("finest");
    }
    else if ( WxChoice1->GetSelection() == 5 )
    {
        wxMessageBox("urzytkownika");
    }
    else WxChoice1->GetStringSelection().ToDouble( &Grid );
    
    SetFocus();
    ReDrawRequest = true;
}

/*
 * WxToolButton1Click
 */
void PCB_CAM_ProcessorFrm::WxToolButton1Click(wxCommandEvent& event)  // siatka
{
    GridVisible = IsToolChecked( WxAuiToolBar3->FindTool( ID_WXTOOLBUTTON1 ) );
    ReDrawRequest = true;
}

/*
 * WxToolButton2Click
 */
void PCB_CAM_ProcessorFrm::WxToolButton2Click(wxCommandEvent& event) // okragly pad
{
	if ( IsToolChecked( WxAuiToolBar2->FindTool( ID_WXTOOLBUTTON2 ) ) ) 
    {
        AddingMode = rpad;
        RadioToolCheck( WxAuiToolBar2->FindTool( ID_WXTOOLBUTTON2 ) );
    }
    else AddingMode = none;
}

/*
 * WxToolButton3Click
 */
void PCB_CAM_ProcessorFrm::WxToolButton3Click(wxCommandEvent& event)  //kwadratowy pad
{
	if ( IsToolChecked( WxAuiToolBar2->FindTool( ID_WXTOOLBUTTON3 ) ) ) 
    {
        AddingMode = spad;
        RadioToolCheck( WxAuiToolBar2->FindTool( ID_WXTOOLBUTTON3 ) );
    }
    else AddingMode = none;
}

/*
 * WxToolButton4Click
 */
void PCB_CAM_ProcessorFrm::WxToolButton4Click(wxCommandEvent& event)  // oktagonalny pad
{
	if ( IsToolChecked( WxAuiToolBar2->FindTool( ID_WXTOOLBUTTON4 ) ) ) 
    {
        AddingMode = opad;
        RadioToolCheck( WxAuiToolBar2->FindTool( ID_WXTOOLBUTTON4 ) );
    }
    else AddingMode = none;
}

/*
 * WxToolButton5Click
 */
void PCB_CAM_ProcessorFrm::WxToolButton5Click(wxCommandEvent& event) // prosta sciezka
{
	if ( IsToolChecked( WxAuiToolBar1->FindTool( ID_WXTOOLBUTTON5 ) ) ) 
    {
        AddingMode = sline;
        RadioToolCheck( WxAuiToolBar1->FindTool( ID_WXTOOLBUTTON5 ) );
    }
    else AddingMode = none;
}

/*
 * WxToolButton6Click
 */
void PCB_CAM_ProcessorFrm::WxToolButton6Click(wxCommandEvent& event) // okragla sciezka
{
	if ( IsToolChecked( WxAuiToolBar1->FindTool( ID_WXTOOLBUTTON6 ) ) ) 
    {
        AddingMode = rline;
        RadioToolCheck( WxAuiToolBar1->FindTool( ID_WXTOOLBUTTON6 ) );
    }
    else AddingMode = none;
}



void PCB_CAM_ProcessorFrm::DrawGrid()
{
    double Startx = (int)(GluPosition.x / Grid) * Grid;
    double Starty = (int)(GluPosition.y / Grid) * Grid;
    
    for ( double x = Startx ; x < GluSize.x + GluPosition.x; x += Grid )
    {
        DrawLine( Cpoint( x, GluPosition.y ),Cpoint( x, GluSize.y + GluPosition.y ),rxColour("LIGHT GREY") );
    }
    for ( double y = Starty; y < GluSize.y + GluPosition.y; y += Grid )
    {
        DrawLine( Cpoint( GluPosition.x, y ),Cpoint( GluSize.x + GluPosition.x, y ),rxColour("LIGHT GREY") );
    }
}

/*******************************************************************************
*                        Liczenie konturu
*******************************************************************************/

void PCB_CAM_ProcessorFrm::CalcContour( double CutterRadius ) 
{
    int CalcCounter = 0;

    WX_CLEAR_ARRAY( *PrimitivesToMake );
    SimulationCounter = 0;
    WX_CLEAR_ARRAY( *ObjectPrims );
    ProductPrims->Clear();
    
    // Deklaracja lokalna nie wiem czy dobrze ale chyba tak
    PCBObjectArray PCBObjects;
    // Odczytanie listy obiekrow z GroupMenegera
    GroupMeneger->GetObjects( &PCBObjects );
    
    for ( int i = 0; i < PCBObjects.GetCount();  i++ )  PCBObjects.Item(i)->GetPrimitives( ObjectPrims, CutterRadius ); // wyczytanie wszystkich prymitywów [TOEDIT]
    for ( int i = 0; i < ObjectPrims->GetCount(); i++ ) ObjectPrims->Item(i)->Init();                                   // inicjalizacja prymitywów
    
    for ( int i = 0; i < ObjectPrims->GetCount() -1; i++ )
        for ( int j = i+1; j < ObjectPrims->GetCount(); j++ )
            ObjectPrims->Item(i)->Cut( ObjectPrims->Item(j) ); // funkcja cut sprawdzi czy wlasciciele sa rózni
    
    for ( int i = 0; i < ObjectPrims->GetCount(); i++ ) ObjectPrims->Item(i)->GetFragments( ProductPrims ); // odpytanie o wyniki
    
    for ( int i = 0; i < ProductPrims->GetCount(); i++ )
    {
        bool IsOK;
        
        for ( int j = 0; j < PCBObjects.GetCount(); j++ ) if ( ProductPrims->Item(i)->GetOwner() != PCBObjects.Item(j) )
        {
            CalcCounter++;
            
            if ( PCBObjects.Item(j)->IsPointInside( ProductPrims->Item(i)->GetMiddlePoint(), CutterRadius ) ) { IsOK = false; break; }
            else IsOK = true;
        }
        
        if ( IsOK ) PrimitivesToMake->Add( ProductPrims->Item(i) );
        else delete ProductPrims->Item(i);
    }
    
    ReDrawRequest = true;
    
    // scalanie
   
    int i = 0;
    int j = 0;
    bool WasJoin;
    
    for ( i = 0; i < PrimitivesToMake->GetCount() -1; i++ )
    {  
        WasJoin = false;
        for ( j = i+1; j < PrimitivesToMake->GetCount(); j++ )
        {
            if ( PrimitivesToMake->Item(i)->Join( PrimitivesToMake->Item(j) ) )
            {
                delete PrimitivesToMake->Item(j);
                PrimitivesToMake->RemoveAt(j);
                
                WasJoin = true;
            }
        }
        if ( WasJoin ) i--;
    }
    
    for ( i = 0; i < PrimitivesToMake->GetCount(); i++ )
    {
        if ( PrimitivesToMake->Item(i)->Len() < MICRO )
        {
            delete PrimitivesToMake->Item(i);
            PrimitivesToMake->RemoveAt(i);
            i--;
        }
    }
    
    
    double SumLen = 0.0;
    for ( int i = 0; i < PrimitivesToMake->GetCount(); i++ ) SumLen += PrimitivesToMake->Item(i)->Len();

    
    wxMessageBox( wxString::Format( "obiektów: %i\nlini do wykonania: %i( %f mm )\nwykonano iteracji: %i",PCBObjects.GetCount(), PrimitivesToMake->GetCount(),SumLen, CalcCounter ) );
}

void PCB_CAM_ProcessorFrm::DrawWorkSpace()
{
    Cpoint CMouseCords;
    double Dimension,Hole,Widht;
    
    if ( AddingMode == none )  CMouseCords = GetCMousePosition( false );
    else                       CMouseCords = GetCMousePosition();
    
    //WxChoice1->GetStringSelection().ToDouble( &Grid );
    WxChoice2->GetStringSelection().ToDouble( &Dimension );
    WxChoice3->GetStringSelection().ToDouble( &Hole );
    WxChoice4->GetStringSelection().ToDouble( &Widht );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(GluPosition.x, GluPosition.x + GluSize.x,   GluPosition.y, GluPosition.y + GluSize.y );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    // uklad wsp
    
    DrawRect( Cpoint(0.0,-0.15),Cpoint(5.0,0.15),rxColour("GREEN") );
    DrawRect( Cpoint(-0.15,0.0),Cpoint(0.15,5.0),rxColour("RED") );
    DrawCircle( Cpoint(0,0),0.5,rxColour("BLACK") );
    
    // wizualizacja dodawania czyli robimy niejako wlasny kursor
    
    switch( AddingMode )
    { 
        case rpad: 
            PCBrPad::Draw( Dimension, CMouseCords );
            PCBHole2::Draw( Hole, CMouseCords );  break;
            
        case spad:
            PCBsPad::Draw( Dimension, CMouseCords );
            PCBHole2::Draw( Hole, CMouseCords );  break;
            
        case opad:
            PCBoPad::Draw( Dimension, CMouseCords );
            PCBHole2::Draw( Hole, CMouseCords );  break;
            
        case sline:
            PCBNode *BeginNode = NodeMngr->GetNodeByIndex(NodeId[0]);
            if ( BeginNode ) PCBsPath::Draw( Widht, CMouseCords, BeginNode->Position ); 
            
            break;
            
        case duplicate:
            GroupMeneger->DrawSelected( CMouseCords - ClickCpointGrid );
    }
    
    
    
    /****************************************************************************
    *             Wyrysowanie wszystkich obiektów jednym poleceniem
    ***************************************************************************/
    
    GroupMeneger->Draw();
    GroupMeneger->DrawSelected();

    if ( GridVisible ) DrawGrid();
    
    /****************************************************************************
    *                Obs³uga zaznaczanie przez prostok¹t [TOEDIT]
    ***************************************************************************/
    if ( MouseIsDown && !OnSelectClick && AddingMode == none ) 
    {
        DrawRect( ClickCpoint, CMouseCords, rxColour("BLACK"), false );
        GroupMeneger->MakeSelection( ClickCpoint, CMouseCords, Shift ); // nie powinno tu tego byc [TOEDIT]
    }
    
    glFlush();
    SwapBuffers( hDC );
}

void PCB_CAM_ProcessorFrm::DrawMillPreView()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(GluPosition.x, GluPosition.x + GluSize.x,   GluPosition.y, GluPosition.y + GluSize.y );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    // uklad wsp
    
    DrawRect( Cpoint(0.0,-0.15),Cpoint(5.0,0.15),rxColour("GREEN") );
    DrawRect( Cpoint(-0.15,0.0),Cpoint(0.15,5.0),rxColour("RED") );
    DrawCircle( Cpoint(0,0),0.5,rxColour("BLACK") );  
    
    if ( GridVisible ) DrawGrid();

    /////////////////////////////////////////////////////////////////////
    //// rysowanie konrurow  ////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    
    for ( int i = 0; i < PrimitivesToSim->GetCount(); i++ ) PrimitivesToSim->Item(i)->Draw( WxTimerSimulation->IsRunning() ? "LIGHT GREY" : "BLACK" );
    
    if ( WxTimerSimulation->IsRunning() ) 
    {
        for ( int i = 0; i < SimulationCounter; i++ ) PrimitivesToSim->Item(i)->Draw("RED");
        SimPrim->Draw("RED");
    }
    
    glFlush();
    SwapBuffers( hDC );
}

void PCB_CAM_ProcessorFrm::DrawDrillPreView()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(GluPosition.x, GluPosition.x + GluSize.x,   GluPosition.y, GluPosition.y + GluSize.y );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    // uklad wsp
    
    DrawRect( Cpoint(0.0,-0.15),Cpoint(5.0,0.15),rxColour("GREEN") );
    DrawRect( Cpoint(-0.15,0.0),Cpoint(0.15,5.0),rxColour("RED") );
    DrawCircle( Cpoint(0,0),0.5,rxColour("BLACK") );  
    
    if ( GridVisible ) DrawGrid();

    /////////////////////////////////////////////////////////////////////
    //// rysowanie otworow  ////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    
    for ( int i = 0; i < HolesToSim->GetCount(); i++ ) HolesToSim->Item(i)->Draw( Cpoint( 0.0, 0.0 ), WxTimerSimulation->IsRunning() ? "LIGHT GREY" : "BLACK" );
    
    if ( WxTimerSimulation->IsRunning() ) 
        for ( int i = 0; i < SimulationCounter; i++ ) HolesToSim->Item(i)->Draw( Cpoint( 0.0, 0.0 ), "RED" );
    
    glFlush();
    SwapBuffers( hDC );
}

bool PCB_CAM_ProcessorFrm::SingleSelectClick()
{
    if ( AddingMode == duplicate )
    {
        GroupMeneger->DuplicateSelected( GetCMousePosition() - ClickCpointGrid );
        AddingMode = none;
    }
    
    ClickCpointGrid = GetCMousePosition();
    ClickCpoint     = GetCMousePosition(false);
    
    OnSelectClick = GroupMeneger->MakeSelection( ClickCpoint, Shift );
    
    // zapisanie obecnych pozycji nodow w ich specjalnym rejestrze
    for ( int i = 0; i < NodeMngr->GetCount(); i++ ) NodeMngr->GetNodeByIndex(i)->SaveOldPosition(); // byc moze sie zmieni po uzyciu nodemenegera [TOEDIT]
    
    PropertiesDialog->SetObjects( GroupMeneger );
    
    ReDrawRequest = true;
    SetFocus();
    
    return OnSelectClick;
}

void PCB_CAM_ProcessorFrm::DeleteSelectedItem()
{
    GroupMeneger->DeleteSelected();
    PropertiesDialog->SetObjects( GroupMeneger );
    
    ReDrawRequest = true;
}


/*
 * WxTimer1Timer
 */
void PCB_CAM_ProcessorFrm::WxTimer1Timer(wxTimerEvent& event) // timer od rysowania
{ 
    Dpoint MouseCords; // [TOEDIT] wyrzucic stad dpinty i jak co to wg mousecord no i cala funkcja do poprawki
    double Dimension,Hole,Widht;
    
    if ( AddingMode == none )  MouseCords = GetMousePosition( false );
    else                       MouseCords = GetMousePosition();
    
    Cpoint CMouseCords;
    CMouseCords = Cpoint( MouseCords.x, MouseCords.y );
    
    if ( CNCDialog->Review )
    {
        if ( ReDrawRequest || PropertiesDialog->ReDrawRequest )
        {
            if ( WxChoice5->GetSelection() == 0 ) DrawDrillPreView();
            else                                  DrawMillPreView();
            
            ReDrawRequest = PropertiesDialog->ReDrawRequest = false;
            PropertiesDialog->Show(false);
        }
    }
    else
    {
        if ( ReDrawRequest || PropertiesDialog->ReDrawRequest )
        {
            DrawWorkSpace();
            ReDrawRequest = PropertiesDialog->ReDrawRequest = false;
        }
        
        // Poruszanie wezlami
        if (  AddingMode == none )
        {
            if ( MouseIsDown && OnSelectClick && !Shift ) 
            {
                // obliczenie obecnej pozycji na podstawie przesuniecia myszy i starej pozycji
                for ( int i = 0; i < NodeMngr->GetCount(); i++ ) 
                    if ( NodeMngr->GetNodeByIndex(i)->IsSelected() ) NodeMngr->GetNodeByIndex(i)->ShiftPosition( GetCMousePosition() - ClickCpointGrid );
            }
        }
    }
    
    WxStatusBar1->SetStatusText( wxString::Format("X: %f mm (%f inch), Y: %f mm (%f inch)",MouseCords.x, MouseCords.x / 25.4, MouseCords.y, MouseCords.y / 25.4 ) );
}

/*
 * PCB_CAM_ProcessorFrmMouseWheel
 */
void PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmMouseWheel(wxMouseEvent& event)
{
	Dpoint OldGluSize = GluSize;
	Dpoint CenterPoint;
	
	CenterPoint.x = GetClientSize().x - event.GetPosition().x;
	CenterPoint.y = event.GetPosition().y;
    
    if ( CenterPoint.x > 0 && CenterPoint.y > 0 && CenterPoint.x < GetClientSize().x && CenterPoint.y < GetClientSize().y )
    {
        if ( event.GetWheelRotation() > 0 ) 
        {
            Scale *= 1.1;
            CalculateGluSize();
        }
    	else
        {
            Scale /= 1.1;
            CalculateGluSize();
        }
        
        GluPosition.x += ( OldGluSize.x - GluSize.x )*( 1 - CenterPoint.x /   GetClientSize().x );
        GluPosition.y += ( OldGluSize.y - GluSize.y )*( 1 - CenterPoint.y / ( GetClientSize().y + WxStatusBar1->GetSize().y ) ); 
    }
    
    ReDrawRequest = true;
}

/*
 * PCB_CAM_ProcessorFrmSize
 */
void PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmSize(wxSizeEvent& event)
{
	Dpoint OldGluSize = GluSize;
    DisableOpenGL(hWnd, hDC, hRC);
    EnableOpenGL(hWnd, &hDC, &hRC);
	CalculateGluSize();
	
	GluPosition.x += ( OldGluSize.x - GluSize.x )/2;
    GluPosition.y += ( OldGluSize.y - GluSize.y )/2; 
    
    ReDrawRequest = true;
}

/*
 * PCB_CAM_ProcessorFrmLeftDown
 */
void PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmLeftDown(wxMouseEvent& event)
{
    if ( CNCDialog->Review ) return; //Uwalenie tego dla wrybu symulacji
    
    MouseIsDown = true;
    SingleSelectClick();  
}

/*
 * PCB_CAM_ProcessorFrmRightDown
 */
void PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmRightDown(wxMouseEvent& event)
{
	if ( CNCDialog->Review ) return; //Uwalenie tego dla wrybu symulacji
    
    // Wy³¹czenie edycji
    AddingMode = none;
	RadioToolCheck( NULL );
	// Pokazanie menu
    if ( !Shift && SingleSelectClick() ) PopupMenu( WxPopupMenu1 );
}

/*
 * PCB_CAM_ProcessorFrmMouseEvents
 */
void PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmMouseEvents(wxMouseEvent& event)
{
	ReDrawRequest = true;
	SetFocus();
}

/*
 * PCB_CAM_ProcessorFrmLeftUP [TOEDIT] - przerabiamy dodawanie obiektow
 */
void PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmLeftUP(wxMouseEvent& event)
{
    if ( CNCDialog->Review ) return; //Uwalenie tego dla wrybu symulacji
    
    Cpoint CMouseCords;
    PCBPadArray ExtractedPads;
    
    int NodeCount = NodeMngr->GetCount();
    static int EventCount = 0;
    double Dimension,Hole;
    
    MouseIsDown = false;
    
    if ( AddingMode == none )  
    {
        CMouseCords = GetCMousePosition( false );
        PropertiesDialog->SetObjects( GroupMeneger );
    }
    else 
    {
        CMouseCords = GetCMousePosition();
        
        for ( int i = 0; i < NodeMngr->GetCount(); i++ )
        {
            if ( EQ_DOUBLE( NodeMngr->GetNodeByIndex(i)->Position.real(), CMouseCords.real(), MICRO ) &&
                 EQ_DOUBLE( NodeMngr->GetNodeByIndex(i)->Position.imag(), CMouseCords.imag(), MICRO ) )   // jest juz wezel w tym miejscu
            {
                NodeId[EventCount] = i;
                break;
            }
        }
    }
    
    switch( AddingMode )
    {
        case none:
            break;
            
        case rpad: case spad: case opad:
            
            if ( NodeId[EventCount] == -1 ) // brak wezla w tym miejscu mozna dodac
            {
                NodeMngr->AddNode( new PCBNode( 0, CMouseCords ) ); 
                NodeId[EventCount] = NodeCount;
            }
            // Sprawdzenie padów
            GroupMeneger->GetObjects( &ExtractedPads );
            for ( int i = 0; i < ExtractedPads.GetCount(); i++ )
            {
                //if( ExtractedPads.Item(i)->GetNodeID() == PCBNodes.Item(NodeId[EventCount])->ID ) // koniec funkcji
                if( ExtractedPads.Item(i)->GetNodeID() == NodeMngr->GetNodeByIndex(NodeId[EventCount])->ID ) // koniec funkcji
                {
                    wxMessageBox("Nie mo¿na umieœciæ pada na innym padzie");
                    NodeId[0] = -1;
                    return;
                } 
            }
    
            WxChoice2->GetStringSelection().ToDouble( &Dimension );
            WxChoice3->GetStringSelection().ToDouble( &Hole );
            
            // Zapisanie na chwile tego noda zeby nie pisac takich dlugich zapisow
            PCBNode *NodeForObject = NodeMngr->GetNodeByIndex( NodeId[ EventCount ] );
            
            if ( AddingMode == rpad )      GroupMeneger->AddChildGroup( new Group( new PCBrPad( Dimension, NodeForObject ), new PCBHole2( Hole, NodeForObject ) ) );
            else if ( AddingMode == spad ) GroupMeneger->AddChildGroup( new Group( new PCBsPad( Dimension, NodeForObject ), new PCBHole2( Hole, NodeForObject ) ) );
            else if ( AddingMode == opad ) GroupMeneger->AddChildGroup( new Group( new PCBoPad( Dimension, NodeForObject ), new PCBHole2( Hole, NodeForObject ) ) );

            NodeId[0] = -1;
            break;
            
        case sline: case rline:
            
            if ( NodeId[EventCount] == -1 ) // brak wezla w tym miejscu mozna dodac
            {
                NodeMngr->AddNode( new PCBNode( 0, CMouseCords ) );
                NodeId[EventCount] = NodeCount;
            }
            
            EventCount++;
            
            if ( EventCount == 2 ) 
            {
                WxChoice4->GetStringSelection().ToDouble( &Dimension );
                // Dodanie sciezki
                if ( AddingMode == sline )        GroupMeneger->AddChildGroup( new Group( new PCBsPath( Dimension,  NodeMngr->GetNodeByIndex(NodeId[0]), NodeMngr->GetNodeByIndex(NodeId[1]) ) ) );
                else if ( AddingMode == rline );
                EventCount = 0;
                for ( int i = 0; i < 3; i++ ) NodeId[i] = -1;
            }
            break;
    }
    ReDrawRequest = true;
}

/*
 * WxChoice2Selected
 */
void PCB_CAM_ProcessorFrm::WxChoice2Selected(wxCommandEvent& event ) // srednica pada
{
	SetFocus();
}

/*
 * WxChoice3Selected
 */
void PCB_CAM_ProcessorFrm::WxChoice3Selected(wxCommandEvent& event ) // srednica otworu
{
	SetFocus();
}

/*
 * WxChoice4Selected
 */
void PCB_CAM_ProcessorFrm::WxChoice4Selected(wxCommandEvent& event ) // szerokosc sciezki
{
	SetFocus();
}


/*
 * MenuNew
 */
void PCB_CAM_ProcessorFrm::MenuNew(wxCommandEvent& event)
{
    GroupMeneger->Clear();
    NodeMngr    ->Clear();
	
	MainFileName.Clear();
	MainFilePath.Clear();
	SetTitle( FrmTitle ); 
	
	ReDrawRequest = true;
}

/*
 * MenuOpen
 */
void PCB_CAM_ProcessorFrm::MenuOpen(wxCommandEvent& event)
{
    if ( WxOpenFileDialog1->ShowModal() == wxID_OK )
    {
        MainFilePath = WxOpenFileDialog1->GetPath();
        MainFileName = WxOpenFileDialog1->GetFilename();
    
        SetTitle( FrmTitle + " - [ " + MainFileName + " ] - " + MainFilePath );
	
    	OpenProject( MainFilePath );
    }
    
    ReDrawRequest = true;
}

/*
 * MenuSave
 */
void PCB_CAM_ProcessorFrm::MenuSave(wxCommandEvent& event)
{
    bool MakeSave = false;
    
    if ( MainFileName.IsEmpty() )
    {
        if ( WxSaveFileDialog1->ShowModal() == wxID_OK )
        {
            MainFilePath = WxSaveFileDialog1->GetPath();
            MainFileName = WxSaveFileDialog1->GetFilename();
            if ( MainFileName.AfterLast('.') != "pcb" ) { MainFileName += ".pcb"; MainFilePath += ".pcb"; }
            SetTitle( FrmTitle + " - [ " + MainFileName + " ] - " + MainFilePath );
            MakeSave = true;
        }
    }
    else MakeSave = true;

    if ( MakeSave ) SaveProject( MainFilePath );
}

/*
 * MenuSaveAs
 */
void PCB_CAM_ProcessorFrm::MenuSaveAs(wxCommandEvent& event)
{
	if ( WxSaveFileDialog1->ShowModal() == wxID_OK )
    {
        MainFilePath = WxSaveFileDialog1->GetPath();
        MainFileName = WxSaveFileDialog1->GetFilename();
        if ( MainFileName.AfterLast('.') != "pcb" ) { MainFileName += ".pcb"; MainFilePath += ".pcb"; }
        SetTitle( FrmTitle + " - [ " + MainFileName + " ] - " + MainFilePath );
        
        SaveProject( MainFilePath );
    }
}

/*
 * OpenGeneratorDialog
 */
void PCB_CAM_ProcessorFrm::OpenGeneratorDialog(wxCommandEvent& event)
{
	CNCDialog->Show();
}

void PCB_CAM_ProcessorFrm::SetWindowSettings( wxString Settings )
{
    if ( Settings.IsEmpty() ) return;
    
    wxString sGluPosition = GetXLMBlock( Settings, "viewpoint", true, 1 );
    
    ElementOfString( 1, sGluPosition, ',' ).ToDouble( &GluPosition.x );
    ElementOfString( 2, sGluPosition, ',' ).ToDouble( &GluPosition.y );
    
    GetXLMBlock( Settings, "scale", true, 1 ).ToDouble( &Scale );
    
    CalculateGluSize();
}

wxString PCB_CAM_ProcessorFrm::GetWindowSettings()
{
    wxString Ret;
    
    Ret += "<settings>\n";
        Ret += wxString::Format( "\t<viewpoint>%f, %f</viewpoint>\n", GluPosition.x, GluPosition.y );
        Ret += wxString::Format( "\t<scale>%f</scale>\n",             Scale );
    Ret += "</settings>\n";
    
    return Ret;
}

void PCB_CAM_ProcessorFrm::SaveProject( wxString FileName )
{
	wxString SaveString;
    MyConfigFile File;
    
    File.MyOpen( FileName );
    File.Clear();
        File.AddLine( GetWindowSettings() );
        File.AddLine( NodeMngr->GetSaveString() );
        GroupMeneger->MakeSaveString( &SaveString );
        File.AddLine( SaveString );
    File.MyClose();
}

void PCB_CAM_ProcessorFrm::OpenProject( wxString FileName ) // [TOEDIT]
{
    MyConfigFile File;
    wxString     Str;
    PCBCore     *NewCore;
    
    File.Open( FileName );
    
        Str = File.GetFile();
        
        GroupMeneger->Clear();
        NodeMngr    ->Clear();
        
        if ( Str.Find("nodes") > -1 ) // Nowy plik
        {
            SetWindowSettings( GetXLMBlock( Str, "settings", true, 1 ) );
            
            NodeMngr    ->LoadContent( GetXLMBlock( Str, "nodes", true, 1 ) );
            GroupMeneger->LoadContent( GetXLMBlock( Str, "group", true, 1 ) );
        }
        else // Stary plik
        {
            for ( Str = File.GetFirstLine(); !File.Eof(); Str = File.GetNextLine() )
            {
                NodeMngr->LoadNode( Str );
                
                NewCore = Group::CreateObjectFromString( Str );
                if ( NewCore ) GroupMeneger->AddChildGroup( new Group( NewCore ) );
            }
        }
        
    File.Close();
}

/*
 * WxTimerSimulationTimer
 */
void PCB_CAM_ProcessorFrm::WxTimerSimulationTimer(wxTimerEvent& event)
{
    static double PrimLenCounter = 0;
    double PrimLen;
    static int TimeMs = 0;
    
    WxEdit1->GetValue().ToDouble( &SimSpeed );
    
    if ( WxChoice5->GetSelection() == 0 ) // wiercenie
    {
        if ( SimulationCounter < HolesToSim->GetCount() ) 
        {
                TimeMs += WxTimerSimulation->GetInterval();
                if ( TimeMs > 300 ) 
                {
                    SimulationCounter++;
                    TimeMs = 0;
                }
        }
        else WxTimerSimulation->Stop();
    }
    else
    {
        if ( SimulationCounter < PrimitivesToSim->GetCount() ) 
        {
            PrimLenCounter += SimSpeed * (double)WxTimerSimulation->GetInterval(); // m/s * liczba sekund jescze powem na mm czyli * 1000 co skraca te 1000 ms z wczesniej
            PrimLen  = PrimitivesToSim->Item( SimulationCounter )->Len();
            
            if ( PrimLenCounter > PrimLen ) PrimLenCounter = PrimLen; 
            
            delete SimPrim;
            SimPrim = PrimitivesToSim->Item( SimulationCounter )->GetPercentFragment( PrimLenCounter / PrimLen );
            
            if ( PrimLenCounter >= PrimLen )
            {
                SimulationCounter++;
                PrimLenCounter = 0;
            }
        }
        else WxTimerSimulation->Stop();
    }
    
    ReDrawRequest = true;
}

/*
 * WxChoice5Selected
 */
void PCB_CAM_ProcessorFrm::WxChoice5Selected(wxCommandEvent& event )
{
	ReDrawRequest = true;
}

/*
 * WxToolButton9Click
 */
void PCB_CAM_ProcessorFrm::WxToolButton9Click(wxCommandEvent& event) // play pause button
{
	SimulationCounter = 0;
    WxTimerSimulation->Start(40);
}

/*
 * WxToolButton10Click
 */
void PCB_CAM_ProcessorFrm::WxToolButton10Click(wxCommandEvent& event) // stop sim
{
	SimulationCounter = 0;
    WxTimerSimulation->Stop();
    ReDrawRequest = true;
}

/*******************************************************************************
                       Menu kontekstowe dla obiektów
********************************************************************************/
/*
 * MenuCopy
 */
void PCB_CAM_ProcessorFrm::MenuCopy(wxCommandEvent& event) // Grupuj
{
	GroupMeneger->JoinSelected();
}

/*
 * MenuPaste
 */
void PCB_CAM_ProcessorFrm::MenuPaste(wxCommandEvent& event) // Rozgrupuj
{
	GroupMeneger->SplitSelected();
}

/*
 * MenuCut
 */
void PCB_CAM_ProcessorFrm::MenuCut(wxCommandEvent& event) // Duplikuj
{
	AddingMode = duplicate; // uruchomienie duplikacji
}

/*
 * MenuDelete
 */
void PCB_CAM_ProcessorFrm::MenuDelete(wxCommandEvent& event)
{
	DeleteSelectedItem();
}

/*
 * MenuProperties
 */
void PCB_CAM_ProcessorFrm::MenuProperties(wxCommandEvent& event)
{
	PropertiesDialog->Show();
}
/*******************************************************************************
********************************************************************************
********************************************************************************/


/*******************************************************************************
                           Obsluga klawiatury
********************************************************************************/
/*
 * PCB_CAM_ProcessorFrmKeyDown
 */
void PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmKeyDown(wxKeyEvent& event) // http://docs.wxwidgets.org/trunk/defs_8h.html#a41c4609211685cff198618963ec8f77da02c178f08c2061bd418482a305024bb0
{  
    switch ( event.GetKeyCode() )
    {
        //case WXK_SPACE: if ( wxKeyboardState::GetModifiers() == wxMOD_CONTROL ) Destroy(); break;   
        case WXK_SHIFT: Shift = true; break;
    }
}

/*
 * PCB_CAM_ProcessorFrmKeyUp
 */
void PCB_CAM_ProcessorFrm::PCB_CAM_ProcessorFrmKeyUp(wxKeyEvent& event)
{
	switch ( event.GetKeyCode() )
    {
        case WXK_DELETE: DeleteSelectedItem(); break;
        case WXK_SHIFT:  Shift = false; break;
        case WXK_ESCAPE: 
            AddingMode = none; 
            RadioToolCheck( NULL );
            CNCDialog->SetReView( false ); //[TOEDIT] zmiana musi isc tez na druga strone
            SetSimView( false );
            break;
    }
}
/*******************************************************************************
********************************************************************************
********************************************************************************/

