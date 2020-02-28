//---------------------------------------------------------------------------
//
// Name:        PCB CAM ProcessorApp.h
// Author:      rado4ever
// Created:     2016-02-08 19:43:24
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __PCB_CAM_PROCESSORFRMApp_h__
#define __PCB_CAM_PROCESSORFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class PCB_CAM_ProcessorFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
