#include "gui.h"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	// Menu - File
    EVT_MENU(ID_ONOPENSRC, MyFrame::OnOpenSrc)

wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
