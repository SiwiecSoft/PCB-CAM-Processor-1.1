///-----------------------------------------------------------------
///
/// @file      Group.cpp
/// @author    rado4ever
/// Created:   2016-09-26 22:33:12
/// @section   DESCRIPTION
///            Group class implementation
///
///------------------------------------------------------------------

#include "Group.h"

Group::Group( PCBCore *Obj1, PCBCore *Obj2, PCBCore *Obj3, PCBCore *Obj4, PCBCore *Obj5 )
{
    Change   = false;
    Selected = false;
    
    if ( Obj1 != NULL ) Objects.Add( Obj1 ); else return;
    if ( Obj2 != NULL ) Objects.Add( Obj2 ); else return;
    if ( Obj3 != NULL ) Objects.Add( Obj3 ); else return;
    if ( Obj4 != NULL ) Objects.Add( Obj4 ); else return;
    if ( Obj5 != NULL ) Objects.Add( Obj5 ); else return; 
}

Group::~Group()
{
    Clear();
}

bool Group::IsInside( Cpoint Point )
{
    for ( unsigned int i = 0; i < Objects.Count(); i++ )     if ( Objects.Item(i)->IsPointInside( Point ) )  return true;
    for ( unsigned int i = 0; i < ChildGroups.Count(); i++ ) if ( ChildGroups.Item(i)->IsInside( Point ) )   return true;

    return false;
}

bool Group::IsInside( PCBNode *NodeToTest )
{
    for ( unsigned int i = 0; i < Objects.Count(); i++ )     if ( Objects.Item(i)->IsNodeInside( NodeToTest ) )  return true;
    for ( unsigned int i = 0; i < ChildGroups.Count(); i++ ) if ( ChildGroups.Item(i)->IsInside( NodeToTest ) )  return true;

    return false;
}

bool Group::IsInside( PCBNodeArray *NodeArrayToTest )
{
    
}

bool Group::Select( bool Sel )
{
    Selected = Sel; // zaznacz siebie
    for ( unsigned int i = 0; i < Objects.Count(); i++ )     Objects.Item(i)->Select( Sel ); // swoje elementy
    SelectChildren( Sel );                                                                   // przekaz dzieciom
    return Sel;
}

bool Group::SelectChildren( bool Sel )
{
    for ( unsigned int i = 0; i < ChildGroups.Count(); i++ ) ChildGroups.Item(i)->Select( Sel );      // zaznacz dzieci
    return Sel;
}

bool Group::SelectWithNodes( bool Sel )
{
    Selected = Sel; // zaznacz siebie
    for ( unsigned int i = 0; i < Objects.Count(); i++ )     Objects.Item(i)->SelectWithNodes( Sel ); // swoje elementy
    SelectChildrenWithNodes( Sel );                                                                   // przekaz dzieciom
    return Sel;
}

bool Group::SelectChildrenWithNodes( bool Sel )
{
    for ( unsigned int i = 0; i < ChildGroups.Count(); i++ ) ChildGroups.Item(i)->SelectWithNodes( Sel );      // zaznacz dzieci
    return Sel;
}

bool Group::MakeSelection( Cpoint Point, bool Shift )
{  
    // Zmienna mowiaca o tym czy klikniecie wywolalo zaznaczaenie 
    bool OnSelectClick = false;
    
    // jesli kliknienie jest na jakims zaznaczonym objekcie to nic sie nie dzieje a gdy shift to sie go odznacza
    for ( int i = 0; i < ChildGroups.GetCount(); i++ ) 
    {
        if ( ChildGroups.Item(i)->IsSelected() && ChildGroups.Item(i)->IsInside( Point ) )
        {
            OnSelectClick = true;
            if ( Shift ) ChildGroups.Item(i)->SelectWithNodes(false); // wypadaloby jeszcze zrobic ze jesli nody tego obiektu sa zaznaczone przez inne to on ich nie odznacza [TOEDIT] - ciekawa uwaga nie wyrzucac
            else break; // przerwanie gdy nie ma shift'a
        }
    }
    
    if ( !OnSelectClick )
    {
        // odzaczenie wszystkich objektow gdy nie ma wcisnietego shift'a
        if ( !Shift ) SelectChildrenWithNodes(false);
        
        // zaznaczenie pierwszego obiektu ktory jest w punkcie klikniecia ( lub wszystkich z shiftem )*
        for ( int i = 0; i < ChildGroups.GetCount(); i++ ) 
        {
            if ( ChildGroups.Item(i)->IsInside( Point ) )
            {
                ChildGroups.Item(i)->SelectWithNodes(); 
                OnSelectClick = true;
                if( !Shift ) break;
            }
        }        
    }
    
    return OnSelectClick;
}

void Group::MakeSelection( Cpoint P1, Cpoint P2, bool Shift )
{
    if ( !Shift ) SelectChildrenWithNodes(false); // gdy nie ma shifta to odznaczamy wszystko zeby przygotowac grunt :)
    
    // zaznaczenie nodow ktore sa w tym obszarze rect  
    PCBCore::NodeMngr->SelectByRect( P1, P2 );  
    
    for ( int i = 0; i < PCBCore::NodeMngr->GetCount(); i++ ) if ( PCBCore::NodeMngr->GetNodeByIndex(i)->IsSelected() )
    {
        // Zaznaczenie grup krore kozystaja z tych wezlow
        for ( int j = 0; j < ChildGroups.GetCount(); j++ ) 
            if ( ChildGroups.Item(j)->IsInside( PCBCore::NodeMngr->GetNodeByIndex(i) ) ) 
                 ChildGroups.Item(j)->Select();
    }
}

void Group::Draw( Cpoint Shift, bool OnlySelected )
{
    PCBsPathArray AllPaths;
    PCBPadArray   AllPads;
    PCBHole2Array AllHoles;
    
    GetObjects( &AllPaths, true, OnlySelected );
    GetObjects( &AllPads,  true, OnlySelected );
    GetObjects( &AllHoles, true, OnlySelected );
    // Rysowanie w kolejnosci sciezki, pady, otwory z uzyciem przelacznika OnlySelected aby rysowac tylko zaznaczone
    for ( unsigned int i = 0; i < AllPaths.Count(); i++ )     AllPaths.Item(i)->Draw( Shift );      // swoim sciezkom
    for ( unsigned int i = 0; i < AllPads.Count(); i++ )      AllPads.Item(i)->Draw( Shift );       // swoim padom
    for ( unsigned int i = 0; i < AllHoles.Count(); i++ )     AllHoles.Item(i)->Draw( Shift );       // swoim padom
}

void Group::DrawSelected( Cpoint Shift )
{
    Draw( Shift, true );
}

bool Group::IsAnyChildSelected()
{
    for ( unsigned int i = 0; i < ChildGroups.Count(); i++ ) if ( ChildGroups.Item(i)->IsSelected() ) return true;
    return false;
}

void Group::DeleteSelected()
{
    for ( unsigned int i = 0; i < ChildGroups.Count(); i++ ) if ( ChildGroups.Item(i)->IsSelected() )
    {
        delete ChildGroups.Item(i);                 // usuniecie obiektu
        ChildGroups.Remove( ChildGroups.Item(i) ); // usuniecie pustedo wskaznika z tablicy;
        i--;                                      // cofamy licznik aby sprawdzic wszystkie zaznaczone
    }
}

void Group::Clear()
{
    WX_CLEAR_ARRAY( Objects );
    WX_CLEAR_ARRAY( ChildGroups );   
}

void Group::SaveToFile( MyConfigFile *FileObj, wxString Spacing )
{
    wxString NextSpacing = Spacing + "\t";
    
    FileObj->AddLine( "\n" + Spacing + "<group>" );
    
        FileObj->AddLine( NextSpacing + wxString::Format( "%i", ID ) );
        
        // Zapisujemy swoje obiekty
        for ( unsigned int i = 0; i < Objects.Count(); i++ )
        {
            FileObj->AddLine( "\n" + NextSpacing + "<element>" );
                FileObj->AddLine( NextSpacing + "\t" + Objects.Item(i)->GetSaveString() );
            FileObj->AddLine( NextSpacing + "</element>\n" );
        }

        //przekazanie dzieciom
        for ( unsigned int i = 0; i < ChildGroups.Count(); i++ ) ChildGroups.Item(i)->SaveToFile( FileObj, NextSpacing );
    
    FileObj->AddLine( Spacing + "</group>\n" );
}

void Group::MakeSaveString( wxString *StringToWrite, wxString Spacing )
{
    wxString SpacingPlus1 = Spacing      + "\t";
    wxString SpacingPlus2 = SpacingPlus1 + "\t";
    
    *StringToWrite += Spacing + "<group>\n";
        
        // Zapisujemy swoje obiekty
        *StringToWrite += SpacingPlus1 + "<elements>\n";
            for ( unsigned int i = 0; i < Objects.Count(); i++ )
            {
                *StringToWrite += SpacingPlus2 + "<element>" + Objects.Item(i)->GetSaveString() + "</element>\n";
            }
        *StringToWrite += SpacingPlus1 + "</elements>\n";
        
        *StringToWrite += SpacingPlus1 + "<groups>\n";
            //przekazanie dzieciom
            for ( unsigned int i = 0; i < ChildGroups.Count(); i++ ) ChildGroups.Item(i)->MakeSaveString( StringToWrite, SpacingPlus2 );
        *StringToWrite += SpacingPlus1 + "</groups>\n";
    
    *StringToWrite += Spacing + "</group>\n";
}

void Group::LoadContent( wxString XMLData )
{
    PCBCore *NewElement;
    Group   *NewGroup;
    
    wxString sElements = GetXLMBlock( XMLData, "elements", true, 1 );
    wxString sGroups   = GetXLMBlock( XMLData, "groups",   true, 1 );
    
    wxArrayString asElements, asGroups;
    
    GetXLMBlocks( sElements, "element", &asElements, 1 );
    GetXLMBlocks( sGroups,   "group",   &asGroups,   1 );
    
    // Dodawanie elementów
    for ( unsigned int i = 0; i < asElements.Count(); i++ )
    {
        NewElement = CreateObjectFromString( asElements.Item(i) );
        if ( NewElement != NULL ) Objects.Add( NewElement );
    }
    // Dodawanie grup
    for ( unsigned int i = 0; i < asGroups.Count(); i++ )
    {
        NewGroup = new Group();
        AddChildGroup( NewGroup );
        NewGroup->LoadContent( asGroups.Item(i) );
    }  
}

PCBCore *Group::CreateObjectFromString( wxString Params )
{
    PCBCore *NewPCBObject;

    NewPCBObject = PCBHole2::New( Params );
    if ( NewPCBObject ) return NewPCBObject;
    
    NewPCBObject = PCBsPad::New( Params );
    if ( NewPCBObject ) return NewPCBObject;
    NewPCBObject = PCBrPad::New( Params );
    if ( NewPCBObject ) return NewPCBObject;
    NewPCBObject = PCBoPad::New( Params );
    if ( NewPCBObject ) return NewPCBObject;
    
    NewPCBObject = PCBsPath::New( Params );
    if ( NewPCBObject ) return NewPCBObject;
    
    return NULL;
}

Group *Group::Duplicate()
{
    Group *NewGroup = new Group();
    
    // Duplikacja obiektów
    for ( unsigned int i = 0; i < Objects.Count(); i++ )
    {
        PCBCore *NewCore = Objects.Item(i)->Duplicate();
        if ( NewCore ) NewGroup->Objects.Add( NewCore );
    }
    // Duplikacja grup
    for ( unsigned int i = 0; i < ChildGroups.Count(); i++ )
    {
        NewGroup->AddChildGroup( ChildGroups.Item(i)->Duplicate() );
    }
    
    return NewGroup;
}

void Group::DuplicateSelected( Cpoint Shift )
{
    PCBCore::NodeMngr->DuplicateSelected( Shift );
    
    unsigned int ChildAmount = ChildGroups.Count();
    
    for ( unsigned int i = 0; i < ChildAmount; i++ ) // po wszyskich dzieciach
    {
        if ( ChildGroups.Item(i)->IsSelected() ) // jesli zaznaczone
        {
            AddChildGroup( ChildGroups.Item(i)->Duplicate() );
        }
    }     
    
    PCBCore::NodeMngr->ClearOriginIDs();     
}

void Group::JoinSelected()
{
    if ( IsAnyChildSelected() )
    {
        Group *NewGroup = new Group();
        
        for ( unsigned int i = 0; i < ChildGroups.Count(); i++ )
        {
            if ( ChildGroups.Item(i)->IsSelected() )
            {
                NewGroup->AddChildGroup( ChildGroups.Item(i) ); // Podepnij zaznaczona moja grupe pod nowa grupe
                ChildGroups.RemoveAt(i);                        // I odepnij ja ode mnie 
                i--;
            }
        }
        AddChildGroup( NewGroup ); // Dodaj nowa grupe pode mnie
    }
}

void Group::SplitSelected()
{
    bool HasChildren;
    unsigned int ChildAmount = ChildGroups.Count();
    
    for ( unsigned int i = 0; i < ChildAmount; i++ ) // po wszyskich dzieciach
    {
        if ( ChildGroups.Item(i)->IsSelected() ) // jesli zaznaczone
        {
            HasChildren = false;
            for ( unsigned int j = 0; j < ChildGroups.Item(i)->ChildGroups.Count(); j++ ) // to po jego dzieciach
            {
                AddChildGroup( ChildGroups.Item(i)->ChildGroups.Item(j) ); // j-te dziecko mojego i-tego dziecka czyli wnuk jest teraz moim dzieckiem
                HasChildren = true;
            }
            if ( HasChildren )
            {
                ChildGroups.Item(i)->ChildGroups.Clear(); // czyszczenie tablicy dziecka ( dziecko zapomina o dzieciach wnuki sa teraz u mnie ) a nie niszczenie obiektu
                
                delete ChildGroups.Item(i); // moje wnuki sa sierotami
                ChildGroups.RemoveAt(i);    // zapominam o dziecku
                
                i--;
                ChildAmount--; // aby pojechac tylko po swoich dzieciach a nie po swiezo dopientych wnukach
            }
        }
    }
}

/*******************************************************************************
*                  Szablonowa funkcja exportu obiektow
*******************************************************************************/

template < class Type, class ArrayType > //u¿ywamy szablonu
void Group::TemplateGetObjects( ArrayType *ReturnTable, bool ClearTable, bool OnlySelected )
{
    Type *Object;
    if ( ClearTable ) ReturnTable->Clear();  
    // Dla wszystkich moich obiektow
    for ( unsigned int i = 0; i < Objects.Count(); i++ )
        if ( !OnlySelected || Objects.Item(i)->IsSelected() ) 
            if ( Object = dynamic_cast < Type *>( Objects.Item(i) ) ) ReturnTable->Add( Object );
    // Przekazanie tej tablicy dzieciom     
    for ( unsigned int i = 0; i < ChildGroups.Count(); i++ ) ChildGroups.Item(i)->TemplateGetObjects< Type, ArrayType >( ReturnTable, false, OnlySelected );    
}

// Przeladowane funkcje exportu obiektow
void Group::GetObjects( PCBCoreArray         *ReturnTable, bool ClearTable, bool OnlySelected )  { TemplateGetObjects< PCBCore,   PCBCoreArray >       ( ReturnTable, ClearTable, OnlySelected ); }
void Group::GetObjects( PCBHole2Array        *ReturnTable, bool ClearTable, bool OnlySelected )  { TemplateGetObjects< PCBHole2,  PCBHole2Array >      ( ReturnTable, ClearTable, OnlySelected ); }
void Group::GetObjects( PCBHole2SortedArray  *ReturnTable, bool ClearTable, bool OnlySelected )  { TemplateGetObjects< PCBHole2,  PCBHole2SortedArray >( ReturnTable, ClearTable, OnlySelected ); }
void Group::GetObjects( PCBObjectArray       *ReturnTable, bool ClearTable, bool OnlySelected )  { TemplateGetObjects< PCBObject, PCBObjectArray >     ( ReturnTable, ClearTable, OnlySelected ); }
void Group::GetObjects( PCBPadArray          *ReturnTable, bool ClearTable, bool OnlySelected )  { TemplateGetObjects< PCBPad,    PCBPadArray >        ( ReturnTable, ClearTable, OnlySelected ); }
void Group::GetObjects( PCBsPadArray         *ReturnTable, bool ClearTable, bool OnlySelected )  { TemplateGetObjects< PCBsPad,   PCBsPadArray >       ( ReturnTable, ClearTable, OnlySelected ); }
void Group::GetObjects( PCBrPadArray         *ReturnTable, bool ClearTable, bool OnlySelected )  { TemplateGetObjects< PCBrPad,   PCBrPadArray >       ( ReturnTable, ClearTable, OnlySelected ); }
void Group::GetObjects( PCBoPadArray         *ReturnTable, bool ClearTable, bool OnlySelected )  { TemplateGetObjects< PCBoPad,   PCBoPadArray >       ( ReturnTable, ClearTable, OnlySelected ); }
void Group::GetObjects( PCBsPathArray        *ReturnTable, bool ClearTable, bool OnlySelected )  { TemplateGetObjects< PCBsPath,  PCBsPathArray >      ( ReturnTable, ClearTable, OnlySelected ); }


