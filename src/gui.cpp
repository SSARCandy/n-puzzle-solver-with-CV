#include "../include/gui.h"
#include <iostream>


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(wxT("N-puzzle Solver"), wxPoint(50, 50), wxSize(800, 600));
    //frame->Maximize(true);
    frame->Show(true);

    return true;
}

#pragma region MyFrame
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    #pragma region MenuBar
    wxMenu *menuFile = new wxMenu();
    menuFile->Append(ID_ONOPENSRC, "&Open SrcImg\tCtrl-O", "Open source image");
    menuFile->Append(ID_ONSAVE, "&Save\tCtrl-E", "Save Result");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu();
    menuHelp->Append(wxID_ABOUT, "&About", "About the System");
    menuHelp->Append(new wxMenuItem(menuHelp, wxID_TOGGLE_LOG, wxString(wxT("&Debug Log\tCtrl-L")), "Show/Hide the Log", wxITEM_CHECK))->Check(false);

    wxMenuBar *menuBar = new wxMenuBar();
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


    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer(wxVERTICAL);

    solve = new wxButton(m_panel2, BUTTON_SolveIt, wxT("\nSolve It !!!\n"), wxDefaultPosition, wxDefaultSize, 0);
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
    debugMode = false;
}
void MyFrame::OnOpenSrc(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open image file"), "", "", "image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)  return;     // the user changed idea...

    // proceed loading the file chosen by the user, this can be done with e.g. wxWidgets input streams:
    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }
    //drawPane->mypuzzle.Init(drawPane->mypuzzle.Original_img.size());
    drawPane->mypuzzle.ReadSrc((const char*)openFileDialog.GetPath().mb_str());

    wxSize img(drawPane->mypuzzle.Original_img.cols, drawPane->mypuzzle.Original_img.rows);
    drawPane->SetSize(img);

    this->Layout();


    sS = drawPane->mypuzzle.Segmenting();
}
void MyFrame::OnSave(wxCommandEvent& event)
{
    wxFileDialog
    saveFileDialog(this, _("Save PNG file"), "", "",
                   "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    // save the current contents in the file;
    // this can be done with e.g. wxWidgets output streams:
    wxFileOutputStream output_stream(saveFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
        return;
    }

    cvtColor(drawPane->dis, drawPane->dis, CV_BGR2RGB);
    imwrite((const char*)saveFileDialog.GetPath().mb_str(), drawPane->dis);


    //  drawPane->element.SaveRD();
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Shu-Hsuan Hsu\n\nComputer Science - National Chengchi University",
                 "About N-puzzle Solver",
                 wxOK | wxICON_INFORMATION);
}
void MyFrame::OnToggleLog(wxCommandEvent& event)
{
    debugMode = !debugMode;
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnSolveIt(wxCommandEvent& event)
{
    m_textCtrl1->Clear();

    sS = drawPane->mypuzzle.Segmenting();
    drawPane->mypuzzle.solve();
    gS = drawPane->mypuzzle.generateGoalState();

    puzzle ans;
    puzzleSolver p(sS, gS);
    ans = p.graph_search();

    if (debugMode)
    {
        m_textCtrl1->AppendText(sS + "\n");
        m_textCtrl1->AppendText(gS + "\n\n==============\n");
    }
    for (int i = 0; i < ans.actCount; i++)
    {
        wxString s;
        s.Printf("%s" , ans.action[i]);
        //m_textCtrl1->SetDefaultStyle(wxTextAttr(color));
        m_textCtrl1->AppendText(s);
    }

    if (debugMode)
    {
        wxString s;
        s.Printf("%s", drawPane->mypuzzle.debug_printRelations());
        //s.Printf("%s", ans.printCurrentState());
        m_textCtrl1->AppendText("\n==============\n" + s);
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
    if (!mypuzzle.imgLoaded) return;

    Point MousePosition(min(max(event.m_x, 0), this->mypuzzle.Original_img.cols), min(max(event.m_y, 0), this->mypuzzle.Original_img.rows));

    if (activateDraw)
    {
    }

    LastMousePosition = MousePosition;// Point(min(max(event.m_x, 0), this->mypuzzle.Original_img.cols), min(max(event.m_y, 0), this->mypuzzle.Original_img.rows));

}
void BasicDrawPane::MouseLDown(wxMouseEvent &event)
{
    if (!mypuzzle.imgLoaded) return;

    StartMousePosition = Point(min(max(event.m_x, 0), this->mypuzzle.Original_img.cols), min(max(event.m_y, 0), this->mypuzzle.Original_img.rows));
    activateDraw = true;
}
void BasicDrawPane::MouseLUp(wxMouseEvent &event)
{
    if (!mypuzzle.imgLoaded) return;

    int sx, sy, ex, ey;
    sx = StartMousePosition.x / 150;/////////////////////
    sy = StartMousePosition.y / 150;/////////////////////
    ex = LastMousePosition.x / 150;/////////////////////
    ey = LastMousePosition.y / 150;/////////////////////

    switchTiles(sx, sy, ex, ey);


    StartMousePosition = Point(0, 0);
    activateDraw = false;

}
void BasicDrawPane::switchTiles(int sx, int sy, int ex, int ey)
{
    if (abs(sx - ex) + abs(sy - ey) == 1)
    {
        if (!(mypuzzle.my_tile[sy][sx].isBlank) && (mypuzzle.my_tile[ey][ex].isBlank))
        {
            //tile tmp;
            //tmp = mypuzzle.my_tile[sy][sx];
            //mypuzzle.my_tile[sy][sx] = mypuzzle.my_tile[ey][ex];
            //mypuzzle.my_tile[ey][ex] = tmp;

            int cx = mypuzzle.Original_img.cols / mypuzzle.puzzle_width;////////////////////////////////////
            int cy = mypuzzle.Original_img.rows / mypuzzle.puzzle_height;

            Mat t0(mypuzzle.Original_img, Rect(sx * cx, sy * cy, cx, cy));
            Mat t1(mypuzzle.Original_img, Rect(ex * cx, ey * cy, cx, cy));

            Mat tmpimg;                           // swap
            t0.copyTo(tmpimg);
            t1.copyTo(t0);
            tmpimg.copyTo(t1);


            mypuzzle.Segmenting();
        }
    }
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

    wxPoint s = wxPoint(StartMousePosition.x, StartMousePosition.y);
    wxPoint e = wxPoint(LastMousePosition.x, LastMousePosition.y);
    dc.SetPen(wxPen(wxColor(255, 0, 0), 2)); // 2-pixels-thick red outline
    if (s.y != 0 || s.x != 0)
    {
        dc.DrawCircle(s, wxCoord(5));
        dc.DrawLine(s, e);
    }

}
#pragma endregion
