///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* all_sizer;
	all_sizer = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* panel_sizer;
	panel_sizer = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 600,600 ), wxTAB_TRAVERSAL );
	m_panel1->SetMinSize( wxSize( 600,600 ) );
	m_panel1->SetMaxSize( wxSize( 1000,1000 ) );

	panel_sizer->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );


	all_sizer->Add( panel_sizer, 3, wxEXPAND, 5 );

	wxBoxSizer* controls_sizer;
	controls_sizer = new wxBoxSizer( wxVERTICAL );

	open_button = new wxButton( this, wxID_ANY, wxT("Open File"), wxDefaultPosition, wxDefaultSize, 0 );
	controls_sizer->Add( open_button, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 10 );

	revert_button = new wxButton( this, wxID_ANY, wxT("Back to original"), wxDefaultPosition, wxDefaultSize, 0 );
	controls_sizer->Add( revert_button, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 10 );

	count_staticText = new wxStaticText( this, wxID_ANY, wxT("Axes count"), wxDefaultPosition, wxDefaultSize, 0 );
	count_staticText->Wrap( -1 );
	controls_sizer->Add( count_staticText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 7 );

	wxBoxSizer* count_sizer;
	count_sizer = new wxBoxSizer( wxHORIZONTAL );

	count_scrollBar = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	count_sizer->Add( count_scrollBar, 5, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	countval_staticText = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	countval_staticText->Wrap( -1 );
	count_sizer->Add( countval_staticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	controls_sizer->Add( count_sizer, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );

	angle_staticText = new wxStaticText( this, wxID_ANY, wxT("Axes angle"), wxDefaultPosition, wxDefaultSize, 0 );
	angle_staticText->Wrap( -1 );
	controls_sizer->Add( angle_staticText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 7 );

	wxBoxSizer* angle_sizer;
	angle_sizer = new wxBoxSizer( wxHORIZONTAL );

	angle_scrollBar = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	angle_sizer->Add( angle_scrollBar, 5, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	angleval_staticText = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	angleval_staticText->Wrap( -1 );
	angle_sizer->Add( angleval_staticText, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	controls_sizer->Add( angle_sizer, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );

	x_staticText = new wxStaticText( this, wxID_ANY, wxT("Displacement along X"), wxDefaultPosition, wxDefaultSize, 0 );
	x_staticText->Wrap( -1 );
	controls_sizer->Add( x_staticText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 7 );

	wxBoxSizer* x_sizer;
	x_sizer = new wxBoxSizer( wxHORIZONTAL );

	x_scrollBar = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	x_sizer->Add( x_scrollBar, 4, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	xval_staticText = new wxStaticText( this, wxID_ANY, wxT("0%"), wxDefaultPosition, wxDefaultSize, 0 );
	xval_staticText->Wrap( -1 );
	x_sizer->Add( xval_staticText, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	controls_sizer->Add( x_sizer, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );

	y_staticText = new wxStaticText( this, wxID_ANY, wxT("Displacement along Y"), wxDefaultPosition, wxDefaultSize, 0 );
	y_staticText->Wrap( -1 );
	controls_sizer->Add( y_staticText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 7 );

	wxBoxSizer* y_sizer;
	y_sizer = new wxBoxSizer( wxHORIZONTAL );

	y_scrollBar = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	y_sizer->Add( y_scrollBar, 4, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	yval_staticText = new wxStaticText( this, wxID_ANY, wxT("0%"), wxDefaultPosition, wxDefaultSize, 0 );
	yval_staticText->Wrap( -1 );
	y_sizer->Add( yval_staticText, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	controls_sizer->Add( y_sizer, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxString interpolator_choiceChoices[] = { wxT("Choose Interpolator"), wxT("Nearest Neighbor"), wxT("Bilinear")};
	int interpolator_choiceNChoices = sizeof( interpolator_choiceChoices ) / sizeof( wxString );
	interpolator_choice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, interpolator_choiceNChoices, interpolator_choiceChoices, 0 );
	interpolator_choice->SetSelection( 0 );
	controls_sizer->Add( interpolator_choice, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 15 );

	save_button = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	controls_sizer->Add( save_button, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	animate_button = new wxButton( this, wxID_ANY, wxT("Animation"), wxDefaultPosition, wxDefaultSize, 0 );
	controls_sizer->Add( animate_button, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 15 );


	all_sizer->Add( controls_sizer, 1, wxEXPAND, 5 );


	this->SetSizerAndFit( all_sizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_panel1->Connect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::Resize), NULL, this);
	open_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OpenFile ), NULL, this );
	revert_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::Revert ), NULL, this );
	count_scrollBar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	angle_scrollBar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );

	x_scrollBar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	y_scrollBar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );

	interpolator_choice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::Interpolate ), NULL, this );
	save_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::SaveFile ), NULL, this );
	animate_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::Animate ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_panel1->Disconnect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::Resize), NULL, this);
	open_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OpenFile ), NULL, this );
	revert_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::Revert ), NULL, this );
	count_scrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	count_scrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	angle_scrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	angle_scrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );

	x_scrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	x_scrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	y_scrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	y_scrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	interpolator_choice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::Interpolate ), NULL, this );
	save_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::SaveFile ), NULL, this );
	animate_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::Animate ), NULL, this );

}
