#include "gui.h"

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
	EVT_PAINT(BasicDrawPane::paintEvent)
	EVT_MOTION(BasicDrawPane::MouseMove)
	EVT_LEFT_DOWN(BasicDrawPane::MouseLDown)
	EVT_LEFT_UP(BasicDrawPane::MouseLUp)
END_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	// Menu - File
	EVT_MENU(ID_ONOPENSRC, MyFrame::OnOpenSrc)	
	EVT_MENU(ID_ONSAVE, MyFrame::OnSave)
	EVT_MENU(wxID_EXIT, MyFrame::OnExit)
	EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
	EVT_BUTTON(BUTTON_SolveIt, MyFrame::OnSolveIt)

wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
