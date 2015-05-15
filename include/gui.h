#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "analyzePuzzle.h"

using namespace cv;
using namespace std;

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};

class BasicDrawPane : public wxPanel
{

public:
	BasicDrawPane(wxPanel* parent, Size);
	void paintEvent(wxPaintEvent& evt);
	void paintNow(bool);
	void render(wxDC& dc, bool);
	void MouseMove(wxMouseEvent &event);
	void MouseLDown(wxMouseEvent &event);
	void MouseLUp(wxMouseEvent &event);
	analyzePuzzle mypuzzle;
	DECLARE_EVENT_TABLE()
private:
	bool activateDraw;
	Mat dis;
	Point LastMousePosition;
	Point StartMousePosition;
};


class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnSolveIt(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnOpenSrc(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void activateRenderLoop(bool on);

private:
	bool render_loop_on;
	BasicDrawPane* drawPane;
	wxPanel* m_panel1;
	wxPanel* m_panel2;
	wxButton* solve;
	wxTextCtrl* m_textCtrl1;

	void onIdle(wxIdleEvent& evt);


	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_ONOPENSRC = 1,
	BUTTON_SolveIt
};