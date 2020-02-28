///-----------------------------------------------------------------
///
/// @file      MyBox.h
/// @author    rado4ever
/// Created:   2015-08-06 11:44:25
/// @section   DESCRIPTION
///            Klasa sizera
///
///------------------------------------------------------------------

#ifndef MYBOX
#define MYBOX

#include <wx/wx.h>

class MyBox;
WX_DEFINE_ARRAY( MyBox*, MyBoxArray ); 

enum
{
    // box_order_style
    HORIZONTAL, 
    VERTICAL,
    
    //box_sizing_style
    FIX_SIZE,          
    FLOAT_SIZE,
    FLOAT_SIZE_PERCENT,
    FROM_CONTROL,  
    
    //window_sizing_style
    OWN_SIZE,
    AUTO_WIDTH,
    AUTO_HEIGHT,
    AUTO_SIZE,
    
    // window_alignment_style
    ALIGN_TOP_LEFT,
    ALIGN_TOP_CENTER,
    ALIGN_TOP_RIGHT,
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT,
    ALIGN_BOTTOM_LEFT,
    ALIGN_BOTTOM_CENTER,
    ALIGN_BOTTOM_RIGHT,
    
    // margins
    MARGIN_TOP,
    MARGIN_BOTTOM,
    MARGIN_LEFT, 
    MARGIN_RIGHT
};

typedef struct Marg
{
    Marg( unsigned int Value = 10 ) { Top = Bottom = Left = Right = Value; };
    Marg( unsigned int Top, unsigned int Bottom, unsigned int Left , unsigned int Right ) 
    {  
        this->Top    = Top;
        this->Bottom = Bottom;
        this->Left   = Left;
        this->Right  = Right;
    };
      
    unsigned int Top;
    unsigned int Bottom;
    unsigned int Left;
    unsigned int Right; 
};

class MyBox
{
    public:
        MyBox
        ( 
            unsigned int BoxSizingStyle = FLOAT_SIZE, 
            unsigned int PixelOrPercentSize = 0,
            unsigned int BoxOrderStyle = HORIZONTAL, 
            unsigned int WindowSizingStyle = AUTO_SIZE, 
            unsigned int WindowAligmentStyle = ALIGN_CENTER,
            Marg Margins = Marg(10),
            wxWindow *Window = NULL
        );
        
        //static wxStaticLine* NewStaticLine()                {  }; // brakuje jakiegos includa
        static wxStaticText* NewStaticText( wxWindow *Parent, wxString Label ){ return new wxStaticText( Parent, 1, Label ); };
        static wxStaticBox*  NewStaticBox( wxWindow *Parent, wxString Label ) { return new wxStaticBox( Parent, 1, Label ); };


        // Same as wxWindow methoods
        void SetSize( wxSize Size );
        void SetPosition( wxPoint Point );
        
        wxSize GetSize();
        wxPoint GetPosition();
        
        void Show( bool Show = true ); // ukrywa/pokazuje
        void Hide( bool Hide = true ); // ukrywa/pokazuje tak jakby element nie istnial
        void Enable( bool Enable = true ); // Enable
        
        bool IsHide() { return priv_Hide; };
        
        // wlasne
        //void SetWidht( unsigned int Widht );
        //void SetHeight( unsigned int Height );
        
        void SetPixelSize( unsigned int Size )   { pixel_size = Size; };
        void SetPercentSize( unsigned int Size ) { percent_size = Size; };
        //void FitToWindow( wxWindow *Window );
        
        unsigned int GetPixelSize()   { return pixel_size; };
        unsigned int GetPercentSize() { return percent_size; }; 
        
        // Child control
        void AddBox( MyBox *NewBox );
        void SetWindow( wxWindow *Window ) { window = Window; };
        void ClearBoxes();
        void ClearControl(); 
        void ClearAll() { ClearBoxes(); ClearControl(); };
        
        // style setters
        void SetBoxOrderStyle( unsigned int Style )       { box_order_style = Style; };
        void SetBoxSizingStyle( unsigned int Style )      { box_sizing_style = Style; };
        void SetWindowSizingStyle( unsigned int Style )   { window_sizing_style = Style; };
        void SetWindowAligmentStyle( unsigned int Style ) { window_alignment_style = Style; };
        // margin setters
        void SetWindowMargins( Marg WindowMargins );
        void SetWindowMargins( unsigned int Top, unsigned int Bottom, unsigned int Left, unsigned int Right );
        void SetWindowMargins( unsigned int All ) { SetWindowMargins( All, All, All, All ); };
        void SetWindowMargin( unsigned int Value, unsigned int Margin = MARGIN_TOP ){};
        
        // style getters
        unsigned int GetBoxOrderStyle()       { return box_order_style; };
        unsigned int GetBoxSizingStyle()      { return box_sizing_style; };
        unsigned int GetWindowSizingStyle()   { return window_sizing_style; };
        unsigned int GetWindowAligmentStyle() { return window_alignment_style; };
        // margin getters
        Marg GetWindowMargins();
        unsigned int GetWindowMargin( unsigned int Margin = MARGIN_TOP );
        
    private:
        wxSize size;
        wxPoint position; 
        MyBoxArray my_box_array;
        wxWindow *window;
        unsigned int pixel_size;
        unsigned int percent_size;
        unsigned int box_order_style;
        unsigned int box_sizing_style;
        unsigned int window_sizing_style;
        unsigned int window_alignment_style;
        unsigned int top_margin;
        unsigned int bottom_margin;
        unsigned int left_margin;
        unsigned int right_margin;
        bool priv_Hide;
        
        //void set_size( 
        
        void reconfig(); // reconfiguje dzieci bez zmiany swojego rozmiaru np po funkcji show
        
        
};

#endif
