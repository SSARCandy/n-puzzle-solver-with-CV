#include "gui.h"


bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame("CRD", wxPoint(50, 50), wxSize(800, 730));
	frame->Maximize(true);
	frame->Show(true);

	return true;
}

#pragma region MyFrame
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{

}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MyFrame::OnOpenSrc(wxCommandEvent& event)
{

}
#pragma endregion 
