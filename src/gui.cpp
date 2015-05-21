#include "gui.h"
#include <iostream>


bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame("N-puzzle Solver", wxPoint(50, 50), wxSize(800, 600));
	//frame->Maximize(true);
	frame->Show(true);

	return true;
}

#pragma region MyFrame
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

#pragma region MenuBar
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_ONOPENSRC, "&Open SrcImg\tCtrl-O", "Open source image");
	//menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT, "&About", "About the System");

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	CreateStatusBar(1);
#pragma endregion

	wxBoxSizer* bSizer1;
	wxBoxSizer* bSizer2;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
	drawPane = new BasicDrawPane(m_panel1, Size(256, 256));
	bSizer2->Add(drawPane, 1, wxEXPAND);

	bSizer1->Add(m_panel1, 3, wxEXPAND | wxALL);

	m_panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel2->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
	m_panel2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
	//dps->Add(drawPane, 1, wxEXPAND);


	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	solve = new wxButton(m_panel2, BUTTON_SolveIt, wxT("Solve It !!!"), wxDefaultPosition, wxDefaultSize, 0);
	m_textCtrl1 = new wxTextCtrl(m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RICH2 | wxTE_MULTILINE | wxTE_READONLY, wxDefaultValidator, wxT("WxEdit1"));
	bSizer3->Add(solve, 1, wxALL | wxEXPAND);
	bSizer3->Add(m_textCtrl1, 10, wxALL | wxEXPAND);

	m_panel1->SetSizer(bSizer2);
	m_panel2->SetSizer(bSizer3);
	m_panel2->Layout();
	bSizer3->Fit(m_panel2);
	bSizer1->Add(m_panel2, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	activateRenderLoop(true);
}
void MyFrame::OnOpenSrc(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open image file"), "", "", "image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)	return;     // the user changed idea...
	
	// proceed loading the file chosen by the user, this can be done with e.g. wxWidgets input streams:
	wxFileInputStream input_stream(openFileDialog.GetPath());
	if (!input_stream.IsOk())
	{
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
		return;
	}
	drawPane->mypuzzle.ReadSrc((const char*)openFileDialog.GetPath().mb_str());

	wxSize img(drawPane->mypuzzle.Original_img.cols, drawPane->mypuzzle.Original_img.rows);
	drawPane->SetSize(img);

	this->Layout();


}
void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Shu-Hsuan Hsu\n\nComputer Science - National Chengchi University",
		"About N-puzzle Solver",
		wxOK | wxICON_INFORMATION);
}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MyFrame::OnSolveIt(wxCommandEvent& event)
{
	drawPane->mypuzzle.Segmenting();
	drawPane->mypuzzle.solve();

	float aaa=drawPane->mypuzzle.solve();
	for (int i = 0; i < drawPane->mypuzzle.ans.actCount; i++)
	{
		wxString s;
		s.Printf("%.4f-%s", aaa, drawPane->mypuzzle.ans.action[i]);
		//m_textCtrl1->SetDefaultStyle(wxTextAttr(color));
		m_textCtrl1->AppendText(s);


	}
}


void MyFrame::activateRenderLoop(bool on)
{
	if (on)
	{
		Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyFrame::onIdle));
		render_loop_on = true;
	}
	else
	{
		Disconnect(wxEVT_IDLE, wxIdleEventHandler(MyFrame::onIdle));
		//Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyFrame::onIdle));
		render_loop_on = false;
	}
}
void MyFrame::onIdle(wxIdleEvent& evt)
{
	drawPane->paintNow(render_loop_on);
	evt.RequestMore(); // render continuously, not only once on idle
}

#pragma endregion 

#pragma region BasicDrawPane
BasicDrawPane::BasicDrawPane(wxPanel* parent, Size s) :
wxPanel(parent),
mypuzzle(s)
{
	activateDraw = false;
}

void BasicDrawPane::MouseMove(wxMouseEvent &event)
{

	//Point MousePosition(min(max(event.m_x, 0), element.c_B->cols), min(max(event.m_y, 0), element.c_B->rows));

	if (activateDraw)
	{
	}

	//LastMousePosition = Point(min(max(event.m_x, 0), element.c_B->cols), min(max(event.m_y, 0), element.c_B->rows));
}
void BasicDrawPane::MouseLDown(wxMouseEvent &event)
{
	activateDraw = true;
}
void BasicDrawPane::MouseLUp(wxMouseEvent &event)
{
	activateDraw = false;
}

//first frame
void BasicDrawPane::paintEvent(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	//render(dc);
	dis = mypuzzle.Original_img.clone();
	//dis.convertTo(dis, CV_32FC3, 255);
	//cvtColor(dis, dis, CV_GRAY2RGB);
	wxImage img(dis.cols, dis.rows, dis.data, true);
	wxBitmap bmp(img);
	dc.DrawBitmap(bmp, 0, 0);
}

//render loop
void BasicDrawPane::paintNow(bool render_loop_on)
{
	wxClientDC dc(this);
	render(dc, render_loop_on);
}

//Main Render(iteration) Section
void BasicDrawPane::render(wxDC& dc, bool render_loop_on)
{
	dis = mypuzzle.Original_img.clone();
	//dis.convertTo(dis, CV_8UC3, 255);
	cvtColor(dis, dis, CV_RGB2BGR);


	wxImage img(dis.cols, dis.rows, dis.data, true);
	wxBitmap bmp(img);
	dc.DrawBitmap(bmp, 0, 0);

}
#pragma endregion 