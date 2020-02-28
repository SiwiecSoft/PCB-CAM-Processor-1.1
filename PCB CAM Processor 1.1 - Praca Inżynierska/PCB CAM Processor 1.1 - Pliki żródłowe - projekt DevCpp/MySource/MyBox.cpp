///-----------------------------------------------------------------
///
/// @file      MyBox.cpp
/// @author    rado4ever
/// Created:   2015-08-06 12:55:25
/// @section   DESCRIPTION
///            Klasa sizera - definicje metod
///
///------------------------------------------------------------------

#include "inc/mybox.h"

MyBox::MyBox
( 
    unsigned int BoxSizingStyle, 
    unsigned int PixelOrPercentSize,
    unsigned int BoxOrderStyle, 
    unsigned int WindowSizingStyle, 
    unsigned int WindowAligmentStyle,
    Marg Margins,
    wxWindow *Window
)
{
    position               = wxPoint(0,0); 
    pixel_size             = PixelOrPercentSize;
    percent_size           = PixelOrPercentSize;
    box_order_style        = BoxOrderStyle;
    box_sizing_style       = BoxSizingStyle;
    window_sizing_style    = WindowSizingStyle;
    window_alignment_style = WindowAligmentStyle; 
    window                 = Window;
    priv_Hide              = false;
    
    SetWindowMargins( Margins );
    
    size = wxSize( PixelOrPercentSize, PixelOrPercentSize );
}

// Same as wxWindow methoods
void MyBox::SetSize( wxSize Size )
{
    size = Size;
    reconfig();
}

void MyBox::SetPosition( wxPoint Point ) 
{ 
    position = Point; 
    reconfig();
}

wxSize MyBox::GetSize() 
{ 
    if ( box_sizing_style == FROM_CONTROL && window != NULL ) size = wxSize( window->GetSize().x + left_margin + right_margin, window->GetSize().y + top_margin + bottom_margin );
    return size; 
}
wxPoint MyBox::GetPosition() 
{ 
    return position; 
}

void MyBox::Show( bool Show ) // ukrywa/pokazuje
{
    if ( my_box_array.GetCount() ) 
    {
        for ( unsigned int i = 0; i < my_box_array.GetCount(); i++ ) // ustawienie rozmiaru stalych
        {
            my_box_array[i]->Show(Show);
        }
    }
    if ( window != NULL )
    {
        window->Show(Show);
    }
}

void MyBox::Hide( bool Hide ) // ukrywa/pokazuje tak jakby element nie istnial
{
    Show(!Hide);
    priv_Hide = Hide;
}

void MyBox::Enable( bool Enable )
{
    if ( my_box_array.GetCount() ) 
    {
        for ( unsigned int i = 0; i < my_box_array.GetCount(); i++ ) // ustawienie rozmiaru stalych
        {
            my_box_array[i]->Enable(Enable);
        }
    }
    if ( window != NULL )
    {
        window->Enable(Enable);
    }
}

// margin setters
void MyBox::SetWindowMargins( Marg WindowMargins )
{
    top_margin     = WindowMargins.Top;
    bottom_margin  = WindowMargins.Bottom;
    left_margin    = WindowMargins.Left;
    right_margin   = WindowMargins.Right;
}

void MyBox::SetWindowMargins( unsigned int Top, unsigned int Bottom, unsigned int Left, unsigned int Right )
{
    top_margin     = Top;
    bottom_margin  = Bottom;
    left_margin    = Left;
    right_margin   = Right;
}

// Child control
void MyBox::AddBox( MyBox *NewBox )
{
    my_box_array.Add( NewBox );
}
void MyBox::reconfig()
{
    unsigned int freespace = 0;
    unsigned int templinesize = 0;
    unsigned int floatcout = 0;
    bool horiz = ( box_order_style == HORIZONTAL );
    
    MyBoxArray my_box_array_copy = my_box_array;
    
    if ( my_box_array.GetCount() ) 
    {
        for ( unsigned int i = 0; i < my_box_array.GetCount(); i++ ) // ustawienie rozmiaru stalych
        {
            if ( my_box_array[i]->priv_Hide )
            {
                my_box_array.RemoveAt(i);
                i--;
            }
        }
    }
    
    if ( my_box_array.GetCount() ) 
    {
        freespace = (horiz)? size.x : size.y;
        
        for ( int i = 0; i < my_box_array.GetCount(); i++ ) // ustawienie rozmiaru stalych
        {
            //if ( my_box_array[i]->priv_Hide ) continue;
            
            if ( my_box_array[i]->box_sizing_style == FIX_SIZE || my_box_array[i]->box_sizing_style == FROM_CONTROL ) 
            {
                freespace -= (horiz)? my_box_array[i]->GetSize().x: 
                                      my_box_array[i]->GetSize().y; 
                if ( horiz ) my_box_array[i]->size.y = size.y;
                else         my_box_array[i]->size.x = size.x;
            } 
            else if ( my_box_array[i]->box_sizing_style == FLOAT_SIZE_PERCENT ) 
            {
                templinesize = ( (horiz)? size.x : size.y ) * my_box_array[i]->percent_size / 100;
                freespace -= templinesize;
                my_box_array[i]->size = (horiz)? wxSize( templinesize, size.y ):
                                                 wxSize( size.x, templinesize );
            }
            else floatcout++;
        }
        
        for ( int i = 0; i < my_box_array.GetCount(); i++ ) // ustawienie rozmiaru zmiennych
        {
            //if ( my_box_array[i]->priv_Hide ) continue;
            
            if ( my_box_array[i]->box_sizing_style == FLOAT_SIZE )
            {
                my_box_array[i]->size = (horiz)? wxSize( freespace / floatcout, size.y ):
                                                 wxSize( size.x, freespace / floatcout );
                                                 
                freespace -= freespace / floatcout--;
            }
        }
        
        //if ( !my_box_array[0]->priv_Hide )
        {
            my_box_array[0]->position = position;
            my_box_array[0]->reconfig();
        }
        
        int PrevItem = 1;
        
        for ( int i = 1; i < my_box_array.GetCount(); i++ ) // ustawienie pozycji
        {
            /*if ( my_box_array[i]->priv_Hide ) 
            {
                PrevItem++;
                continue;
            }*/
            
            wxPoint temppos  = my_box_array[i-PrevItem]->position;
            wxSize  tempsize = my_box_array[i-PrevItem]->size;
            my_box_array[i]->position = (horiz)? wxPoint( temppos.x + tempsize.x , temppos.y ): 
                                                 wxPoint( temppos.x , temppos.y + tempsize.y );
            my_box_array[i]->reconfig();
            
            //PrevItem = 1;
        }
    }
    
    my_box_array = my_box_array_copy;
    
    if ( /*!priv_Hide && */window != NULL )
    {
        window->SetSize( wxSize( size.x - left_margin - right_margin, size.y - top_margin - bottom_margin ) );
        window->SetPosition( wxPoint( position.x + left_margin, position.y + top_margin ) );
        
        window->Refresh();
    }
}


