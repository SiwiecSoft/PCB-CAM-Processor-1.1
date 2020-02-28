///-----------------------------------------------------------------
///
/// @file      PCBsPath.h
/// @author    rado4ever
/// Created:   2016-04-18 20:56:47
/// @section   DESCRIPTION
///            PCBsPath class declaration
///
///------------------------------------------------------------------

#ifndef PCBSPATH
#define PCBSPATH

#include "PCBObject.h"

class PCBsPath : public PCBObject
{
    public:
        // Konstruktory
        PCBsPath( double Widht, PCBNode *Node1, PCBNode *Node2 );
        // Destruktory
        virtual ~PCBsPath();
        
        // Wirtualne metody od PCBCore
        virtual bool SelectWithNodes ( bool Sel = true );   // Zaznacza wraz z nodami przestaje byc wirtualna
        virtual void Draw( Cpoint Shift = Cpoint( 0.0, 0.0 ), wxString Col = "" );
        virtual bool IsPointInside( Cpoint Point, double CutterRadius = 0.0 );
        virtual bool IsNodeInside ( PCBNode *NodeToTest ) { return ( NodeToTest == Node[0] || NodeToTest == Node[1] ); };
        virtual wxString GetSaveString();
        virtual PCBCore *Duplicate(); 
                 
        // Wirtualne metody od PCBCore::PCBObject
        virtual void ReCalculate( double CutterRadius = 0.0 );
        virtual void GetPrimitives( PrimitiveArray *ReplyArray, double CutterRadius = 0.0 );
        virtual void GetCommonPoints( Primitive *Prim );
        
        // Wlasne nie wirtualne
        double GetWidht()               { return Widht; };
        void   SetWidht( double Value ) { if ( Value > 0.0 ) Widht = Value; };
        
        // Statyczny pseudo-konstruktor 
        static PCBsPath* New( wxString Params );
        
        // Statyczna funkcja Draw
        static void Draw( double Widht, Cpoint P1, Cpoint P2, wxString Col = "" );

    private:
        double Widht;
        PCBNode *Node[2];
        Cpoint ContourPoints[4];
};

WX_DEFINE_ARRAY_PTR( PCBsPath *, PCBsPathArray );

#endif
