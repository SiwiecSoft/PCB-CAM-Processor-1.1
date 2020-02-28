///-----------------------------------------------------------------
///
/// @file      rx.h
/// @author    Rado4ever
/// Created:   2015-07-08 14:17:53
///
///------------------------------------------------------------------

#ifndef RXLIBRARY
#define RXLIBRARY

#include "wx.h"

// rxRandom.cpp
int RandomValue( int min, int max );
wxString RandomElement( wxString FileName );                                    // losuje jedna z lini pliku
wxString RandomElement( wxTextFile* File );                                     // losuje jedna z lini pliku
wxString RandomElement( wxString SeparatedString, wxChar Separator );           // losuje element z separowanego tekstu
wxString RandomPassword( int PasswordLen );                                     // losuje haslo o okreslonej dlugosci

//rxString.cpp
wxString ConvertToLatin( wxString Str );
wxString MakeLowerCase( wxString Str );
wxString MakeUpperCase( wxString Str );
wxString ElementOfString(int ElementNumber, wxString SeparatedString, wxChar Separator); // funkcja ma pobrac ze stringa fragment oddzielony sepatarorami
wxString FixedLenString( wxString Str, unsigned int Len );                      // zwraca stringa o dl Len ze stringa Str reszte uzupelnia zpacjami
wxArrayString StringToArray( wxString InStr, char Sep );                         // Pobiera separowany Sep'em tekst InStr i wpisuje skladniki do zwracanego wxArrayString, ignoruje separator na koncu

// rxRegEx.cpp
wxString GetExpression( wxString TextToFind, wxString RegularExpression, unsigned int Index = 0 );
bool GetExpression( wxString TextToFind, wxString RegularExpression, unsigned int* Start, unsigned int* Len, unsigned int Index = 0 );
int Replace( wxString* TextToReplace, wxString RegularExpression, wxString Replacement, bool All = false );
int GetExpressionsArray( wxArrayString* ExpressionsArray, wxString TextToFind, wxString RegularExpression, unsigned int Index = 0 );
int GetExpressionsArrays( wxArrayString* ExpressionsArrays, wxString TextToFind, wxString RegularExpression );

#endif



