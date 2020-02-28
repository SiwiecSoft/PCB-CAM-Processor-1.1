///-----------------------------------------------------------------
///
/// @file      Group.h
/// @author    rado4ever
/// Created:   2016-09-26 22:33:23
/// @section   DESCRIPTION
///            Group class declaration
///
///------------------------------------------------------------------

#include "Geometry.h"
#include "../MySource/inc/myconfigfile.h"
#include "../xmlfunc.h"

#ifndef GROUP
#define GROUP

class Group;
WX_DEFINE_ARRAY_PTR( Group *,  ArrayGroup );

class Group
{
    public:
        ~Group();
        
        Group( PCBCore *Obj1 = NULL, PCBCore *Obj2 = NULL, PCBCore *Obj3 = NULL, PCBCore *Obj4 = NULL, PCBCore *Obj5 = NULL );
        
        void AddChildGroup( Group *Pointer ) { ChildGroups.Add( Pointer ); };
        
        bool IsInside( Cpoint Point );
        bool IsInside( PCBNode *NodeToTest );
        bool IsInside( PCBNodeArray *NodeArrayToTest );
        
        bool Select                  ( bool Sel = true );
        bool SelectChildren          ( bool Sel = true );
        bool SelectWithNodes         ( bool Sel = true );
        bool SelectChildrenWithNodes ( bool Sel = true );
        
        bool MakeSelection( Cpoint Point,                                        bool Shift );
        void MakeSelection( Cpoint P1, Cpoint P2, bool Shift );
        
        void Draw        ( Cpoint Shift = Cpoint( 0.0, 0.0 ), bool OnlySelected = false );
        void DrawSelected( Cpoint Shift = Cpoint( 0.0, 0.0 ) );
        
        bool IsChange()   { return Change; };
        bool IsSelected() { return Selected; };
        
        unsigned int GetChildCount() { return ChildGroups.GetCount(); };
        
        bool IsAnyChildSelected();
        
        // Przeladowane funkcje exportu obiektow
        void GetObjects( PCBCoreArray         *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        void GetObjects( PCBHole2Array        *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        void GetObjects( PCBHole2SortedArray  *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        void GetObjects( PCBObjectArray       *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        void GetObjects( PCBPadArray          *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        void GetObjects( PCBsPadArray         *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        void GetObjects( PCBrPadArray         *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        void GetObjects( PCBoPadArray         *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        void GetObjects( PCBsPathArray        *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        
        void DeleteSelected();  
        void Clear();
        
        void SaveToFile( MyConfigFile *FileObj, wxString Spacing = "" ); // Dodaje zawartosc do otwartego pliku
        void MakeSaveString( wxString *StringToWrite, wxString Spacing = "" );   // Zwraca string z zapisem
        
        void LoadContent( wxString XMLData );
        
        static PCBCore *CreateObjectFromString( wxString Params );
        
        Group *Duplicate();                        // Tworzy wierne kopie dzieci na ktore ma wskazniki zapominajac o poprzednich dzieciach - funkcja drzewkowa
        void   DuplicateSelected( Cpoint Shift );  // Wykonuje Duplicate dla swoich zaznaczonych dzieci
        
        void JoinSelected();
        void SplitSelected();
        
    protected:
        PCBCoreArray  Objects;
        ArrayGroup    ChildGroups;    
        bool          Change;
        bool          Selected;
        unsigned int  ID;
        
        //Szablonowa funkcja exportu obiektow
        template < class Type, class ArrayType >
        void TemplateGetObjects( ArrayType *ReturnTable, bool ClearTable = true, bool OnlySelected = false );
        
};



#endif
