///-----------------------------------------------------------------
///
/// @file      xmlfunc.h
/// @author    rado4ever
/// Created:   2016-03-09 15:50:58
/// @section   DESCRIPTION
///            Obsluga plikow typu xml
///
///------------------------------------------------------------------

#include <wx/wx.h>

#ifndef XMLFUNC
#define XMLFUNC

/************************** Znaczenie paramertu Mode ***************************
*
* 0 - calosc z etykietami
* 1 - srodek bez etykiet
* 2 - sama etykieta 
*
*******************************************************************************/ 

wxString GetXLMBlock ( wxString InText, wxString BlockDesc, bool FirstUse = true, unsigned char Mode = 0 );
int      GetXLMBlocks( wxString InText, wxString BlockDesc, wxArrayString *Ans,   unsigned char Mode = 0 );

#endif
