#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/filedlg.h>
#include <wx/wfstream.h>

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

protected:
	void OnExit(wxCommandEvent& event);
	void OnOpenSrc(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_ONOPENSRC = 1,
	ID_ONOPENVFB,
	ID_ONOPENETF,
	ID_ONOPENTEX,
	ID_ONOPENCONTOLIMG,
	ID_ONOPENSIZEIMG,
	ID_ONSAVE,
	ID_ONSAVERD,
	ID_ONREADRD,
	wxID_TOGGLE_LOG,

	ID_ONEdge2AddA,
	ID_ONEdge2AddB,
	ID_ONMask2AddA,
	ID_ONMask2AddB,
	ID_ONETF2GVF,
	ID_ONCLAHE,
	ID_ONHISTOGRAM,
	ID_ONSIZEMASK,
	ID_ONOPEN_MASK,
	ID_ONOPEN_MASK_S,
	ID_ONOPEN_PATTERN_PICKER,

	ID_WXEDIT1,
	BUTTON_Start,
	BUTTON_Fill,
	BUTTON_Clean,
	BUTTON_UNDO,
	BUTTON_REDO,
	COMBOBOX_Processing,
	COMBOBOX_Controlling,
	BUTTON_subDegree,
	BUTTON_addDegree,

	SLIDER_S_PICKER,
	SLIDER_S,
	SLIDER_S_T,
	SLIDER_sd,
	SLIDER_sd_T,
	COMBOBOX_GRADIENT_S_TYPE,
	COMBOBOX_GRADIENT_k_TYPE,
	SLIDER_F,
	SLIDER_F_T,
	SLIDER_K,
	SLIDER_K_T,
	SLIDER_L,
	SLIDER_L_T,
	SLIDER_Theta0,
	SLIDER_Theta0_T,
	SLIDER_BRUSH_SIZE,
	SLIDER_BRUSH_SIZE_T,
	SLIDER_AddA,
	SLIDER_AddA_T,
	SLIDER_AddB,
	SLIDER_AddB_T,
	CHECKBOX_MODIFY_FUNCTION,
	SLIDER_MINDEGREE,
	SLIDER_MINDEGREE_T,
	SLIDER_MAXDEGREE,
	SLIDER_MAXDEGREE_T,
	CHECKBOX_SEGMENTATION,
	COMBOBOX_Region,
	CHECKBOX_DISPLAY_REGION,

	CHECKBOX_Colormapping_isAda,
	COMBOBOX_ColormappingMode,
	SLIDER_Alpha,
	SLIDER_Alpha_T,
	SLIDER_Beta,
	SLIDER_Beta_T,

	BUTTON_Select //pattern picker
};