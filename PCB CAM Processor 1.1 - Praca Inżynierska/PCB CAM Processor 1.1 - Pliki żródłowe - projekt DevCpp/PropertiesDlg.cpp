///-----------------------------------------------------------------
///
/// @file      PropertiesDlg.cpp
/// @author    rado4ever
/// Created:   2016-10-02 22:17:40
/// @section   DESCRIPTION
///            PropertiesDlg class implementation
///
///------------------------------------------------------------------

#include "PropertiesDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// PropertiesDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(PropertiesDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(PropertiesDlg::OnClose)
	
	EVT_TEXT(ID_WXEDIT2,PropertiesDlg::WxEdit2Updated)
	
	EVT_TEXT(ID_WXEDIT1,PropertiesDlg::WxEdit1Updated)
	EVT_LISTBOX(ID_WXLISTBOX1,PropertiesDlg::WxListBox1Selected)
	
	EVT_TEXT(ID_WXCOMBOBOX3,PropertiesDlg::WxComboBox3Updated)
	
	EVT_TEXT(ID_WXCOMBOBOX2,PropertiesDlg::WxComboBox2Updated)
	
	EVT_TEXT(ID_WXCOMBOBOX1,PropertiesDlg::WxComboBox1Updated)
END_EVENT_TABLE()
////Event Table End

PropertiesDlg::PropertiesDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

PropertiesDlg::~PropertiesDlg()
{
} 

void PropertiesDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer3, 0, wxALIGN_CENTER | wxALL, 2);

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, wxT("Œrednica otworu:"), wxPoint(5, 7), wxSize(90, 19), wxST_NO_AUTORESIZE, wxT("WxStaticText1"));
	WxBoxSizer3->Add(WxStaticText1,0,wxALIGN_CENTER | wxALL,5);

	wxArrayString arrayStringFor_WxComboBox1;
	WxComboBox1 = new wxComboBox(this, ID_WXCOMBOBOX1, wxT("WxComboBox1"), wxPoint(105, 5), wxSize(145, 23), arrayStringFor_WxComboBox1, 0, wxDefaultValidator, wxT("WxComboBox1"));
	WxBoxSizer3->Add(WxComboBox1,0,wxALIGN_CENTER | wxEXPAND | wxALL,5);

	WxBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer4, 0, wxALIGN_LEFT | wxALIGN_CENTER | wxALL, 2);

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, wxT("Œrednica pada"), wxPoint(5, 7), wxSize(90, 19), wxST_NO_AUTORESIZE, wxT("WxStaticText2"));
	WxBoxSizer4->Add(WxStaticText2,0,wxALIGN_CENTER | wxALL,5);

	wxArrayString arrayStringFor_WxComboBox2;
	WxComboBox2 = new wxComboBox(this, ID_WXCOMBOBOX2, wxT("WxComboBox2"), wxPoint(105, 5), wxSize(145, 23), arrayStringFor_WxComboBox2, 0, wxDefaultValidator, wxT("WxComboBox2"));
	WxBoxSizer4->Add(WxComboBox2,0,wxALIGN_CENTER | wxEXPAND | wxALL,5);

	WxBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer5, 0, wxALIGN_CENTER | wxALL, 2);

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, wxT("Szerokoœæ œcie¿ki"), wxPoint(5, 7), wxSize(90, 19), wxST_NO_AUTORESIZE, wxT("WxStaticText3"));
	WxBoxSizer5->Add(WxStaticText3,0,wxALIGN_CENTER | wxALL,5);

	wxArrayString arrayStringFor_WxComboBox3;
	WxComboBox3 = new wxComboBox(this, ID_WXCOMBOBOX3, wxT("WxComboBox3"), wxPoint(105, 5), wxSize(145, 23), arrayStringFor_WxComboBox3, 0, wxDefaultValidator, wxT("WxComboBox3"));
	WxBoxSizer5->Add(WxComboBox3,0,wxALIGN_CENTER | wxEXPAND | wxALL,5);

	wxStaticBox* WxStaticBoxSizer1_StaticBoxObj = new wxStaticBox(this, wxID_ANY, wxT("Wêz³y"));
	WxStaticBoxSizer1 = new wxStaticBoxSizer(WxStaticBoxSizer1_StaticBoxObj, wxVERTICAL);
	WxBoxSizer2->Add(WxStaticBoxSizer1, 0, wxALIGN_CENTER | wxALL, 5);

	wxArrayString arrayStringFor_WxListBox1;
	WxListBox1 = new wxListBox(this, ID_WXLISTBOX1, wxPoint(10, 20), wxSize(236, 202), arrayStringFor_WxListBox1, wxLB_SINGLE);
	WxStaticBoxSizer1->Add(WxListBox1,0,wxALIGN_CENTER | wxALL,5);

	WxBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	WxStaticBoxSizer1->Add(WxBoxSizer7, 0, wxALIGN_CENTER | wxALL, 2);

	WxStaticText4 = new wxStaticText(this, ID_WXSTATICTEXT4, wxT("Pozycja X:"), wxPoint(5, 5), wxDefaultSize, 0, wxT("WxStaticText4"));
	WxBoxSizer7->Add(WxStaticText4,0,wxALIGN_CENTER | wxALL,5);

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, wxT("WxEdit1"), wxPoint(72, 5), wxSize(167, 19), 0, wxDefaultValidator, wxT("WxEdit1"));
	WxBoxSizer7->Add(WxEdit1,0,wxALIGN_CENTER | wxALL,5);

	WxBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	WxStaticBoxSizer1->Add(WxBoxSizer8, 0, wxALIGN_CENTER | wxALL, 2);

	WxStaticText5 = new wxStaticText(this, ID_WXSTATICTEXT5, wxT("Pozycja Y:"), wxPoint(5, 5), wxDefaultSize, 0, wxT("WxStaticText5"));
	WxBoxSizer8->Add(WxStaticText5,0,wxALIGN_CENTER | wxALL,5);

	WxEdit2 = new wxTextCtrl(this, ID_WXEDIT2, wxT("WxEdit2"), wxPoint(72, 5), wxSize(167, 19), 0, wxDefaultValidator, wxT("WxEdit2"));
	WxBoxSizer8->Add(WxEdit2,0,wxALIGN_CENTER | wxALL,5);

	SetTitle(wxT("W³aœciwoœci"));
	SetIcon(wxNullIcon);
	
	GetSizer()->Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
	
	// Wpisanie danych do ComboBoxow
    // Otworki
	arrayStringFor_WxComboBox1.Add(wxT("---"));
	arrayStringFor_WxComboBox1.Add(wxT("0.100"));
	arrayStringFor_WxComboBox1.Add(wxT("0.200"));
	arrayStringFor_WxComboBox1.Add(wxT("0.300"));
	arrayStringFor_WxComboBox1.Add(wxT("0.400"));
	arrayStringFor_WxComboBox1.Add(wxT("0.500"));
	arrayStringFor_WxComboBox1.Add(wxT("0.600"));
	arrayStringFor_WxComboBox1.Add(wxT("0.700"));
	arrayStringFor_WxComboBox1.Add(wxT("0.800"));
	arrayStringFor_WxComboBox1.Add(wxT("0.900"));
	arrayStringFor_WxComboBox1.Add(wxT("1.000"));
	arrayStringFor_WxComboBox1.Add(wxT("1.100"));
	arrayStringFor_WxComboBox1.Add(wxT("1.200"));
	arrayStringFor_WxComboBox1.Add(wxT("1.300"));
	arrayStringFor_WxComboBox1.Add(wxT("1.400"));
	arrayStringFor_WxComboBox1.Add(wxT("1.500"));
	arrayStringFor_WxComboBox1.Add(wxT("2.000"));
	arrayStringFor_WxComboBox1.Add(wxT("2.500"));
	arrayStringFor_WxComboBox1.Add(wxT("3.000"));
	arrayStringFor_WxComboBox1.Add(wxT("4.000"));
	arrayStringFor_WxComboBox1.Add(wxT("5.000"));
	// Pady
	arrayStringFor_WxComboBox2.Add(wxT("---"));
	arrayStringFor_WxComboBox2.Add(wxT("0.800"));
	arrayStringFor_WxComboBox2.Add(wxT("0.900"));
	arrayStringFor_WxComboBox2.Add(wxT("1.000"));
	arrayStringFor_WxComboBox2.Add(wxT("1.100"));
	arrayStringFor_WxComboBox2.Add(wxT("1.200"));
	arrayStringFor_WxComboBox2.Add(wxT("1.270"));
	arrayStringFor_WxComboBox2.Add(wxT("1.300"));
	arrayStringFor_WxComboBox2.Add(wxT("1.400"));
	arrayStringFor_WxComboBox2.Add(wxT("1.500"));
	arrayStringFor_WxComboBox2.Add(wxT("1.600"));
	arrayStringFor_WxComboBox2.Add(wxT("1.700"));
	arrayStringFor_WxComboBox2.Add(wxT("1.800"));
	arrayStringFor_WxComboBox2.Add(wxT("1.900"));
	arrayStringFor_WxComboBox2.Add(wxT("2.000"));
	arrayStringFor_WxComboBox2.Add(wxT("2.100"));
	arrayStringFor_WxComboBox2.Add(wxT("2.200"));
	arrayStringFor_WxComboBox2.Add(wxT("2.300"));
	arrayStringFor_WxComboBox2.Add(wxT("2.400"));
	arrayStringFor_WxComboBox2.Add(wxT("2.500"));
	arrayStringFor_WxComboBox2.Add(wxT("2.540"));
	arrayStringFor_WxComboBox2.Add(wxT("3.000"));
	arrayStringFor_WxComboBox2.Add(wxT("4.000"));
	arrayStringFor_WxComboBox2.Add(wxT("5.000"));
	// Sciezki
	arrayStringFor_WxComboBox3.Add(wxT("---"));
	arrayStringFor_WxComboBox3.Add(wxT("0.200"));
	arrayStringFor_WxComboBox3.Add(wxT("0.254"));
	arrayStringFor_WxComboBox3.Add(wxT("0.300"));
	arrayStringFor_WxComboBox3.Add(wxT("0.400"));
	arrayStringFor_WxComboBox3.Add(wxT("0.500"));
	arrayStringFor_WxComboBox3.Add(wxT("0.600"));
	arrayStringFor_WxComboBox3.Add(wxT("0.700"));
	arrayStringFor_WxComboBox3.Add(wxT("0.800"));
	arrayStringFor_WxComboBox3.Add(wxT("0.900"));
	arrayStringFor_WxComboBox3.Add(wxT("1.000"));
	arrayStringFor_WxComboBox3.Add(wxT("1.100"));
	arrayStringFor_WxComboBox3.Add(wxT("1.200"));
	arrayStringFor_WxComboBox3.Add(wxT("1.300"));
	arrayStringFor_WxComboBox3.Add(wxT("1.400"));
	arrayStringFor_WxComboBox3.Add(wxT("1.500"));
	arrayStringFor_WxComboBox3.Add(wxT("2.000"));
	
	WxComboBox1->Append( arrayStringFor_WxComboBox1 );
	WxComboBox2->Append( arrayStringFor_WxComboBox2 );
	WxComboBox3->Append( arrayStringFor_WxComboBox3 );
	
	ReDrawRequest = false;
}

void PropertiesDlg::OnClose(wxCloseEvent& /*event*/)
{
	Show(false);
}

void PropertiesDlg::SetObjects( Group *GroupMeneger )
{
    double       Param, OldParam;
    bool         DifferentParams;
    unsigned int AmountOfObjects;

    /***************************************************************************
    *                      Wylistowanie obiektow
    ****************************************************************************/
    
    // Pobranie wezlow z NodeMenegera
    PCBCore::NodeMngr->GetSelected( &NodeArray );
    // Pobranie obiektow podzielonych na odpowiednie typy z GroupMenegera
    GroupMeneger->GetObjects( &HoleArray,  true, true );
    GroupMeneger->GetObjects( &PadArray,   true, true );
    GroupMeneger->GetObjects( &sPathArray, true, true );
    
    /***************************************************************************
    *                      Ustawienie WxComboBox1
    ****************************************************************************/
    Param = OldParam = 0.0;
    DifferentParams  = false;
    AmountOfObjects  = HoleArray.GetCount();
    
    WxComboBox1->Enable( (bool)AmountOfObjects );
    WxComboBox1->SetSelection(0);
    
    if ( AmountOfObjects )
    {
        for ( unsigned int i = 0; i < AmountOfObjects; i++ ) // sprawdzenie czy parametry sa takie same
        {
            if ( i == 0 ) Param = OldParam = HoleArray.Item(0)->GetDimension();
            else          Param =            HoleArray.Item(i)->GetDimension();
            
            if ( Param != OldParam )
            {
                DifferentParams = true;
                break;
            }
        }
        
        if ( !DifferentParams ) WxComboBox1->SetValue( wxString::Format( "%2.3f", Param ) );
    }
    
    /***************************************************************************
    *                      Ustawienie WxComboBox2
    ****************************************************************************/
    Param = OldParam = 0.0;
    DifferentParams  = false;
    AmountOfObjects  = PadArray.GetCount();
    
    WxComboBox2->Enable( (bool)AmountOfObjects );
    WxComboBox2->SetSelection(0);
    
    if ( AmountOfObjects )
    {
        for ( unsigned int i = 0; i < AmountOfObjects; i++ ) // sprawdzenie czy parametry sa takie same
        {
            if ( i == 0 ) Param = OldParam = PadArray.Item(0)->GetDimension();
            else          Param =            PadArray.Item(i)->GetDimension();
            
            if ( Param != OldParam )
            {
                DifferentParams = true;
                break;
            }
        }
        
        if ( !DifferentParams ) WxComboBox2->SetValue( wxString::Format( "%2.3f", Param ) );
    }
    
    /***************************************************************************
    *                      Ustawienie WxComboBox3
    ****************************************************************************/
    Param = OldParam = 0.0;
    DifferentParams  = false;
    AmountOfObjects  = sPathArray.GetCount();
    
    WxComboBox3->Enable( (bool)AmountOfObjects );
    WxComboBox3->SetSelection(0);
    
    if ( AmountOfObjects )
    {
        for ( unsigned int i = 0; i < AmountOfObjects; i++ ) // sprawdzenie czy parametry sa takie same
        {
            if ( i == 0 ) Param = OldParam = sPathArray.Item(0)->GetWidht();
            else          Param =            sPathArray.Item(i)->GetWidht();
            
            if ( Param != OldParam )
            {
                DifferentParams = true;
                break;
            }
        }
        
        if ( !DifferentParams ) WxComboBox3->SetValue( wxString::Format( "%2.3f", Param ) );
    }
    
    /***************************************************************************
    *                        Ustawienie WxListBox1
    ****************************************************************************/
    
    wxArrayString ArrayForChoice;
    
    WxListBox1->Clear();
    WxEdit1   ->Clear();
    WxEdit2   ->Clear();
    
    AmountOfObjects = NodeArray.GetCount();
    
    WxListBox1->Enable( (bool)AmountOfObjects );
    WxEdit1   ->Enable( (bool)AmountOfObjects );
    WxEdit2   ->Enable( (bool)AmountOfObjects );
    
    if ( AmountOfObjects )
    {
        for ( unsigned int i = 0; i < AmountOfObjects; i++ ) 
            ArrayForChoice.Add( wxString::Format( "ID: %4i", NodeArray.Item(i)->ID ) );

        WxListBox1->Append( ArrayForChoice );

        WxListBox1->SetSelection(0);
        LoadNode(0);
    }
}

void PropertiesDlg::LoadNode( int Index )
{
    PCBNode *Node;
    
    if ( Index > -1 && Index < NodeArray.GetCount() )
    {
        Node = NodeArray.Item( (unsigned int)Index );
        
        if ( Node )
        {
            WxEdit1->SetValue( wxString::Format( "%2.3f", Node->Position.real() ) );
            WxEdit2->SetValue( wxString::Format( "%2.3f", Node->Position.imag() ) );
        }
    }
}

/*
 * WxComboBox1Updated
 */
void PropertiesDlg::WxComboBox1Updated(wxCommandEvent& event )
{
	double Param;
    
    if ( WxComboBox1->GetValue().ToDouble( &Param ) && Param > 0.0 )
    {
        for ( unsigned int i = 0; i < HoleArray.GetCount(); i++ ) HoleArray.Item(i)->SetDimension( Param );
        ReDrawRequest = true;
    }
}

/*
 * WxComboBox2Updated
 */
void PropertiesDlg::WxComboBox2Updated(wxCommandEvent& event )
{
	double Param;
    
    if ( WxComboBox2->GetValue().ToDouble( &Param ) && Param > 0.0 )
    {
        for ( unsigned int i = 0; i < PadArray.GetCount(); i++ ) PadArray.Item(i)->SetDimension( Param );
        ReDrawRequest = true;
    }
}

/*
 * WxComboBox3Updated
 */
void PropertiesDlg::WxComboBox3Updated(wxCommandEvent& event )
{
	double Param;
    
    if ( WxComboBox3->GetValue().ToDouble( &Param ) && Param > 0.0 )
    {
        for ( unsigned int i = 0; i < sPathArray.GetCount(); i++ ) sPathArray.Item(i)->SetWidht( Param );
        ReDrawRequest = true;
    }
}

/*
 * WxListBox1Selected
 */
void PropertiesDlg::WxListBox1Selected(wxCommandEvent& event)
{
	LoadNode( WxListBox1->GetSelection() );
}

/*
 * WxEdit1Updated
 */
void PropertiesDlg::WxEdit1Updated(wxCommandEvent& event)
{
    double Param;
    int Sel = WxListBox1->GetSelection();
    PCBNode *Node;

    if ( Sel > -1 && WxEdit1->GetValue().ToDouble( &Param ) ) 
    {
        Node = NodeArray.Item( (unsigned int)Sel );
        if ( Node ) Node->Position.real() = Param;
        ReDrawRequest = true;
    }
}

/*
 * WxEdit2Updated
 */
void PropertiesDlg::WxEdit2Updated(wxCommandEvent& event)
{
	double Param;
    int Sel = WxListBox1->GetSelection();
    PCBNode *Node;

    if ( Sel > -1 && WxEdit2->GetValue().ToDouble( &Param ) ) 
    {
        Node = NodeArray.Item( (unsigned int)Sel );
        if ( Node ) Node->Position.imag() = Param;
        ReDrawRequest = true;
    }
}


