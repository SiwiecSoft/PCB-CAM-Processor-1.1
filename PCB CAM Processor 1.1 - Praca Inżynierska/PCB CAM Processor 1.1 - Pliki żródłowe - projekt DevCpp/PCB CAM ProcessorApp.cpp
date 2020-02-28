//---------------------------------------------------------------------------
//
// Name:        PCB CAM ProcessorApp.cpp
// Author:      rado4ever
// Created:     2016-02-08 19:43:24
// Description: 
//
//---------------------------------------------------------------------------

#include "PCB CAM ProcessorApp.h"
#include "PCB CAM ProcessorFrm.h"

PCB_CAM_ProcessorFrm* MainFrame;

IMPLEMENT_APP(PCB_CAM_ProcessorFrmApp)

bool PCB_CAM_ProcessorFrmApp::OnInit()
{
    MainFrame = new PCB_CAM_ProcessorFrm(NULL);
    SetTopWindow(MainFrame);
    MainFrame->Show();
    return true;
}
 
int PCB_CAM_ProcessorFrmApp::OnExit()
{
	return 0;
}
