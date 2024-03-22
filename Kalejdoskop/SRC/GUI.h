///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/stattext.h>
#include <wx/scrolbar.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel1;
		wxButton* open_button;
		wxButton* revert_button;
		wxStaticText* count_staticText;
		wxStaticText* countval_staticText;
		wxStaticText* angle_staticText;
		wxStaticText* angleval_staticText;
		wxStaticText* x_staticText;
		wxStaticText* xval_staticText;
		wxStaticText* y_staticText;
		wxStaticText* yval_staticText;
		wxScrollBar* count_scrollBar;
		wxScrollBar* angle_scrollBar;
		wxScrollBar* x_scrollBar;
		wxScrollBar* y_scrollBar;
		wxChoice* interpolator_choice;
		wxButton* save_button;
		wxButton* animate_button;

		// Virtual event handlers, override them in your derived class
		virtual void Resize(wxSizeEvent& event) { event.Skip(); }
		virtual void OpenFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void Revert( wxCommandEvent& event ) { event.Skip(); }
		virtual void Recount_Axes( wxScrollEvent& event ) { event.Skip(); }
		virtual void Change_Angle( wxScrollEvent& event ) { event.Skip(); }
		virtual void Move_X( wxScrollEvent& event ) { event.Skip(); }
		virtual void Move_Y( wxScrollEvent& event ) { event.Skip(); }
		virtual void Interpolate( wxCommandEvent& event ) { event.Skip(); }
		virtual void SaveFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void Animate( wxCommandEvent& event ) { event.Skip(); }


	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame1();

};

