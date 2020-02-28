///-----------------------------------------------------------------
///
/// @file      rxRegEx.cpp
/// @author    rado4ever
/// Created:   2014-12-01 20:26:43
///
///------------------------------------------------------------------

#include "inc/rx.h"

wxString GetExpression( wxString TextToFind, wxString RegularExpression, unsigned int Index )
{
    wxString Result;
    wxRegEx Expression( RegularExpression , wxRE_ADVANCED + wxRE_ICASE );//wxRE_ICASE | wxRE_DEFAULT

    if( Expression.IsValid() )
    {        
        if( Expression.Matches( TextToFind ) )
        {
            Result = Expression.GetMatch( TextToFind, Index );
        }
    }
    return Result;
}

bool GetExpression( wxString TextToFind, wxString RegularExpression, unsigned int* Start, unsigned int* Len, unsigned int Index )  //GetMatch(size_t* start, size_t* len, size_t index = 0)
{
    wxRegEx Expression( RegularExpression , wxRE_ADVANCED + wxRE_ICASE );

    if( Expression.IsValid() )
    {        
        if( Expression.Matches( TextToFind ) )
        {
            Expression.GetMatch( Start, Len, Index );
        }
        return true;
    }
    return false;
}

int Replace( wxString* TextToReplace, wxString RegularExpression, wxString Replacement, bool All )
{
    int Result = -1;
    wxRegEx Expression( RegularExpression, wxRE_ADVANCED + wxRE_ICASE );

    if( Expression.IsValid() )
    {        
        if( All ) Result = Expression.Replace( TextToReplace, Replacement );
        else      Result = Expression.Replace( TextToReplace, Replacement, 1 );
    }
    return Result;
}

int GetExpressionsArray( wxArrayString* ExpressionsArray, wxString TextToFind, wxString RegularExpression, unsigned int Index )
{
    int Result = -1;
    wxString Expression;
    ExpressionsArray->Clear();
    
    Expression = GetExpression( TextToFind, RegularExpression, Index );
    
    while ( !Expression.IsEmpty() )
    {
        ExpressionsArray->Add( Expression );
        Replace( &TextToFind, RegularExpression, "" );
        Result++;
        Expression = GetExpression( TextToFind, RegularExpression, Index );
    }
    
    return Result;
}

int GetExpressionsArrays( wxArrayString* ExpressionsArrays, wxString TextToFind, wxString RegularExpression )
{
    int Result = -1;
    int Index = 1;
    wxString Expression;
    
    while ( Index )
    {
        Index = 0;
        Expression = GetExpression( TextToFind, RegularExpression, Index );
        
        if ( !Expression.IsEmpty() )
        {
            while ( !Expression.IsEmpty() )
            {
                if ( Result == -1 ) ExpressionsArrays[Index].Clear();
                ExpressionsArrays[Index].Add( Expression );
                Index++;
                Expression = GetExpression( TextToFind, RegularExpression, Index );
            }
        
            Replace( &TextToFind, RegularExpression, "" );
            Result++;
        }
    }
    return Result;
}



