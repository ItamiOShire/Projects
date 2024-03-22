#include "GUIMyFrame1.h"
#include <fstream>
#include <stdlib.h>
#include "vecmat.h"

#if defined(__WXMSW__)
#ifdef wxHAVE_RAW_BITMAP
#include "wx/rawbmp.h"
#endif
#endif

#include "wx/image.h"
#include "wx/graphics.h"

#include <iostream>
//#include <stdio.h>
#include <string>
#include <stdlib.h>

#define PI 3.14159265

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
    wxImage original = wxImage(m_panel1->GetSize());
    wxImage shifted = wxImage(m_panel1->GetSize());
    wxImage copy = wxImage(m_panel1->GetSize());
    wxImage mask = wxImage(m_panel1->GetSize());

    curr_x = 0;
    curr_y = 0;
    interpol = 1;

    count_scrollBar->SetScrollbar(0, 0, 20, 1, true);
    angle_scrollBar->SetScrollbar(0, 1, 360, 1, true);
    x_scrollBar->SetScrollbar(100, 1, 201, 1, true);
    y_scrollBar->SetScrollbar(100, 1, 201, 1, true);
}

void GUIMyFrame1::OpenFile( wxCommandEvent& event )
{

    /*if (...current content has not been saved...)
    {
        if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"),
            wxICON_QUESTION | wxYES_NO, this) == wxNO)
            return;
        //else: proceed asking to the user the new file to open
    }*/

    wxFileDialog openFileDialog(this, _("Open XYZ file"), "", "", "JPEG files (*.jpg)|*.jpg|PNG files (*.png)|*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) return;

    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    // Load the image
    wxImage newImage;
    newImage.LoadFile(openFileDialog.GetPath());

    // Load/Create a circular mask
    //this->mask.LoadFile("mask.png");=

    // Resizing the image to square (initial image does not have to be square, but it will be cropped)
    int size = newImage.GetSize().x > newImage.GetSize().y ? newImage.GetSize().y : newImage.GetSize().x;
    newImage.Resize(wxSize(size, size), wxPoint(0, 0));
    newImage.Rescale(this->m_panel1->GetSize().x, this->m_panel1->GetSize().x);
    this->mask.Rescale(this->m_panel1->GetSize().x, this->m_panel1->GetSize().x);

    // Connecting images to the class
     
    //newImage.SetMaskFromImage(newMask, 0, 0, 0);

    this->original = newImage;
    this->shifted = this->original.Copy();
    this->copy = this->shifted.Copy();

    CreateMask(this->copy.GetWidth(), this->copy.GetHeight());

    Extend();

    Repaint();
}

void GUIMyFrame1::Revert( wxCommandEvent& event )
{
    // This is a complete reset of labels, scrollbar values , and xy coordinates of a shifted image

    this->countval_staticText->SetLabel("0");
    this->angleval_staticText->SetLabel("0");
    this->xval_staticText->SetLabel("0%");
    this->yval_staticText->SetLabel("0%");

    curr_x = 0;
    curr_y = 0;

    count_scrollBar->SetScrollbar(0, 0, 20, 1, true);
    angle_scrollBar->SetScrollbar(0, 1, 360, 1, true);
    x_scrollBar->SetScrollbar(100, 1, 201, 1, true);
    y_scrollBar->SetScrollbar(100, 1, 201, 1, true);

    this->copy = this->original.Copy();
    Repaint();
}

void GUIMyFrame1::Recount_Axes( wxScrollEvent& event )
{
    // Function for changing axes count

    this->copy = this->shifted.Copy();

    int new_val = this->count_scrollBar->GetThumbPosition();
    this->countval_staticText->SetLabel(std::to_string(new_val));

    this->axes_angle = new_val == 0 ? 0 : 180 / new_val;
    this->axes_count = new_val;

    for (int i = 0; i < axes_count; i++) {
        Reflect(angle + this->axes_angle * i);
    }

    Repaint();
}

void GUIMyFrame1::Change_Angle( wxScrollEvent& event )
{
    // Function for changing angle

    int new_val = this->angle_scrollBar->GetThumbPosition();
    this->angleval_staticText->SetLabel(std::to_string(new_val));

    this->angle = new_val;
    this->copy = this->shifted.Copy();

    for (int i = 0; i < axes_count; i++) {
        Reflect(angle + this->axes_angle*i);
    }

    Repaint();
}

void GUIMyFrame1::Move_X(wxScrollEvent& event)
{
    // Function for moving/shifting along the x axis

    int new_val = this->x_scrollBar->GetThumbPosition() - 100;
    std::string new_string = std::to_string(new_val) + "%";
    this->xval_staticText->SetLabel(new_string);

    curr_x = (this->shifted.GetHeight() / 100) * new_val;

    wxBitmap tmpbmp = wxBitmap(this->shifted);
    wxBitmap bmpext = wxBitmap(this->extended);
    wxMemoryDC mem2(bmpext);
    wxMemoryDC mem1(tmpbmp);
    mem1.Blit(0, 0, this->shifted.GetWidth(), this->shifted.GetHeight(), &mem2, this->shifted.GetWidth() + curr_x, this->shifted.GetHeight() + curr_y);
    mem1.SelectObject(wxNullBitmap);

    this->shifted = tmpbmp.ConvertToImage();
    this->copy = this->shifted.Copy();

    for (int i = 0; i < axes_count; i++) {
        Reflect(angle + this->axes_angle * i);
    }

    Repaint();
}

void GUIMyFrame1::Move_Y(wxScrollEvent& event)
{
    // Function for moving/shifting along the y axis

    int new_val = this->y_scrollBar->GetThumbPosition() - 100;
    std::string new_string = std::to_string(new_val) + "%";
    this->yval_staticText->SetLabel(new_string);

    curr_y = (this->shifted.GetHeight() / 100) * new_val;

    wxBitmap tmpbmp = wxBitmap(this->shifted);
    wxBitmap bmpext = wxBitmap(this->extended);
    wxMemoryDC mem2(bmpext);
    wxMemoryDC mem1(tmpbmp);
    mem1.Blit(0, 0, this->shifted.GetWidth(), this->shifted.GetHeight(), &mem2, this->shifted.GetWidth() + curr_x, this->shifted.GetHeight() + curr_y);
    mem1.SelectObject(wxNullBitmap);

    this->shifted = tmpbmp.ConvertToImage();
    this->copy = this->shifted.Copy();

    for (int i = 0; i < axes_count; i++) {
        Reflect(angle + this->axes_angle * i);
    }

    Repaint();
}

void GUIMyFrame1::Interpolate( wxCommandEvent& event )
{
// TODO: Implement Interpolate
    this->interpol = interpolator_choice->GetSelection();
    this->test_var = this->interpol;
    Repaint();
}

void GUIMyFrame1::SaveFile( wxCommandEvent& event )
{
    // Function for saving the current image on the screen

    wxFileDialog saveFileDialog(this, _("Save file"), "", "", "PNG files (*.png)|*.png | BITMAP files (*. bmp)|*.bmp", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) return;
    int tmp = saveFileDialog.GetFilterIndex();
    wxString name = saveFileDialog.GetFilename();
    switch (tmp) {
    case 0:
        this->copy.SaveFile(name, wxBITMAP_TYPE_PNG);
        break;
    case 1:
        this->copy.SaveFile(name, wxBITMAP_TYPE_BMP);
        break;
    }
}

void GUIMyFrame1::Animate( wxCommandEvent& event )
{
    // Function for animation
    this->angle = 0;

    for (int i = 0; i < 721; i++) {
        this->copy = this->shifted.Copy();

        for (int i = 0; i < axes_count; i++) {
            Reflect(angle + this->axes_angle*i);
        }
        Repaint();

        this->angle += 1;

        // Animation speed regulation
        Sleep(20);
    }
}

void GUIMyFrame1::Repaint() {
    // Function for graphic output

    wxClientDC dc1(this->m_panel1);
    wxBufferedDC dc(&dc1);

    int width = this->copy.GetWidth(),
        height = this->copy.GetHeight();
    
    this->copy.SetMaskFromImage(this->mask, 0, 0, 0);
    if (this->interpol != 0) this->copy = this-> interpol == 1 ? NearestNeighborInterpolation(this->copy, width, height) : BilinearInterpolation(this->copy, width, height);
    dc.DrawBitmap(wxBitmap(this->copy), wxPoint(0, 0));

    // FOR TESTING. NO RELATION TO THE FINAL VERSION

    //dc.DrawLine(width / 2, 0, width / 2, height);
    //dc.DrawLine(width, height / 2, 0, height / 2);
    //dc.DrawLine(testing_variable1.GetX(), testing_variable1.GetY(), testing_variable2.GetX(), testing_variable2.GetY());
    //dc.DrawLine(testing_variable2.GetX(), testing_variable2.GetY(), testing_variable3.GetX(), testing_variable3.GetY());
    //dc.DrawLine(testing_variable3.GetX(), testing_variable3.GetY(), testing_variable4.GetX(), testing_variable4.GetY());
    //dc.DrawLine(testing_variable4.GetX(), testing_variable4.GetY(), testing_variable1.GetX(), testing_variable1.GetY());

    //dc.SetBrush(*wxWHITE_BRUSH);
    //dc.SetPen(*wxWHITE_PEN);
    //dc.DrawText(std::to_string(this->test_var), width, height);
}

void GUIMyFrame1::Reflect(int angle) {
    // Function for finding the reflection of an image along the axis that goes through the center of an image under certain angle 
    
    angle %= 360;
    wxImage tmp_cpy = this->copy.Copy();

    unsigned char* to = this->copy.GetData();
    unsigned char* from = tmp_cpy.GetData();

    int size_x = this->copy.GetWidth(),
        size_y = this->copy.GetHeight();

    int bytes_per_pixel = this->copy.HasAlpha() ? 4 : 3;

    //if (sizeof(to) / sizeof(to[0]) < size_x * size_y * bytes_per_pixel) return;

    double a = tan((-angle + 90) * PI / 180);
    double counter_a = tan((-angle) * PI / 180);

    Matrix reflect;

    reflect.data[0][0] = (1 - a*a)/(1 + a*a);
    reflect.data[0][1] = 2*a / (1 + a * a);
    reflect.data[1][0] = 2*a / (1 + a * a);
    reflect.data[1][1] = (a*a - 1) / (1 + a * a);

    Matrix matrix = get_translation_matrix(+size_x / 2, +size_y / 2) * reflect * get_translation_matrix(-size_x / 2, -size_y / 2);
    Vector vector;

    // I have no idea why or how this works. PLEASE DO NOT TOUCH
    for (int y = 0; y < size_y; y+=1) {
        for (int x = 0; x < size_x; x++) {

            vector.Set(x, y);
            vector = matrix * vector;

            int new_x = vector.GetX();
            int new_y = vector.GetY();

            if (angle % 180 == 0 ? angle  == 0 ? x < size_x / 2 : x > size_x / 2 : angle < 180 ? (a * (x - size_x / 2) + size_y / 2 - y) < 0 : (a * (x - size_x / 2) + size_y / 2 - y) > 0) {
                if ((new_y * size_x * 3 + bytes_per_pixel * new_x > 0) && (new_y * size_x * 3 + bytes_per_pixel * new_x + 2 < size_x * size_y * 3)) {
                    //tmp_cpy.Paste(copy, x, y);
                    to[y * size_x * 3 + bytes_per_pixel * x + 0] = from[new_y * size_x * 3 + bytes_per_pixel * new_x + 0];
                    to[y * size_x * 3 + bytes_per_pixel * x + 1] = from[new_y * size_x * 3 + bytes_per_pixel * new_x + 1];
                    to[y * size_x * 3 + bytes_per_pixel * x + 2] = from[new_y * size_x * 3 + bytes_per_pixel * new_x + 2];
                }
                //else {
                //    to[y * size_x * 3 + bytes_per_pixel * x + 0] = 0;
                //    to[y * size_x * 3 + bytes_per_pixel * x + 1] = 0;
                //    to[y * size_x * 3 + bytes_per_pixel * x + 2] = 0;
                //}
            }
        }
    }
}

void GUIMyFrame1::Extend() {
    // Function for finding the extended version of the image. Needed for moving/shifting the original image along the xy axes

    int size_x = this->copy.GetWidth(),
        size_y = this->copy.GetHeight();

    wxBitmap* TempBMP = new wxBitmap(size_x*3, size_y*3);

    {
        wxMemoryDC extender(*TempBMP);
        extender.SetBackground(*wxWHITE_BRUSH);
        extender.Clear();

        extender.DrawBitmap(copy, size_x, size_y);
        extender.DrawBitmap(copy.Mirror(false), size_x, 0);
        extender.DrawBitmap(copy.Mirror(false), size_x, size_x*2);
        extender.DrawBitmap(copy.Mirror(), 0, size_y);
        extender.DrawBitmap(copy.Mirror(), size_x*2, size_y);

        extender.DrawBitmap(copy.Rotate180(), 0, 0);
        extender.DrawBitmap(copy.Rotate180(), size_x*2, 0);
        extender.DrawBitmap(copy.Rotate180(), 0, size_y*2);
        extender.DrawBitmap(copy.Rotate180(), size_x*2, size_y*2);
    }

    extended = (*TempBMP).ConvertToImage();
    delete TempBMP;
}

void GUIMyFrame1::CreateMask(int width, int height) {
    // Image for creating a circular mask

    double x0 = width / 2;
    double y0 = height / 2;
    double r = x0 < y0 ? y0 : x0;

    this->mask = wxImage(width, height);

    unsigned char* mask_ = this->mask.GetData();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (pow((x - x0), 2) + pow((y - y0), 2) >= pow(r, 2)) {
                mask_[y * width * 3 + 3*x + 0] = 0;
                mask_[y * width * 3 + 3*x + 1] = 0;
                mask_[y * width * 3 + 3*x + 2] = 0;
            }
            else {
                mask_[y * width * 3 + 3*x + 0] = 255;
                mask_[y * width * 3 + 3*x + 1] = 255;
                mask_[y * width * 3 + 3*x + 2] = 255;
            }
        }
    }
}

wxImage GUIMyFrame1::NearestNeighborInterpolation(const wxImage& inputImage, int newWidth, int newHeight)
{
    int oldWidth = inputImage.GetWidth();
    int oldHeight = inputImage.GetHeight();

    wxImage outputImage(newWidth, newHeight);

    double widthRatio = static_cast<double>(oldWidth) / newWidth;
    double heightRatio = static_cast<double>(oldHeight) / newHeight;

    for (int y = 0; y < newHeight; ++y)
    {
        for (int x = 0; x < newWidth; ++x)
        {
            int oldX = static_cast<int>(x * widthRatio);
            int oldY = static_cast<int>(y * heightRatio);

            wxColor pixelColor(inputImage.GetRed(oldX, oldY),
                inputImage.GetGreen(oldX, oldY),
                inputImage.GetBlue(oldX, oldY));

            outputImage.SetRGB(x, y, pixelColor.Red(), pixelColor.Green(), pixelColor.Blue());
        }
    }

    return outputImage;
}

wxImage GUIMyFrame1::BilinearInterpolation(const wxImage& image, float newWidth, float newHeight) {
    wxImage newImage(newWidth, newHeight);

    for (int y = 0; y < newHeight; y++)
    {
        for (int x = 0; x < newWidth; x++)
        {
            // Wspó³rzêdne piksela w oryginalnym obrazie
            double srcX = (double)x / newWidth * (image.GetWidth() - 1);
            double srcY = (double)y / newHeight * (image.GetHeight() - 1);

            // Indeksy czterech s¹siaduj¹cych pikseli
            int x1 = (int)srcX;
            int y1 = (int)srcY;
            int x2 = x1 + 1;
            int y2 = y1 + 1;

            // Wspó³czynniki interpolacji
            double dx = srcX - x1;
            double dy = srcY - y1;

            // Wartoœci pikseli s¹siaduj¹cych
           /* wxColour c11[3] = {image.GetRed(x1,y1),image.GetGreen(x1,y1),image.GetBlue(x1,y1)};
            wxColour c12[3] = { image.GetRed(x1,y2),image.GetGreen(x1,y2),image.GetBlue(x1,y2) };
            wxColour c21[3] = { image.GetRed(x2,y1),image.GetGreen(x2,y1),image.GetBlue(x2,y1) };
            wxColour c22[3] = { image.GetRed(x2,y2),image.GetGreen(x2,y2),image.GetBlue(x2,y2) };

            // Interpolacja dla ka¿dego kana³u koloru
            unsigned char red = (1 - dx) * (1 - dy) * c11[0].Red() + dx * (1 - dy) * c21[0].Red() +
                (1 - dx) * dy * c12[0].Red() + dx * dy * c22[0].Red();
            unsigned char green = (1 - dx) * (1 - dy) * c11[1].Green() + dx * (1 - dy) * c21[1].Green() +
                (1 - dx) * dy * c12[1].Green() + dx * dy * c22[1].Green();
            unsigned char blue = (1 - dx) * (1 - dy) * c11[2].Blue() + dx * (1 - dy) * c21[2].Blue() +
                (1 - dx) * dy * c12[2].Blue() + dx * dy * c22[2].Blue();
                */


            const unsigned char* data = image.GetData();
            int bytesPerPixel = image.HasAlpha() ? 4 : 3;

            int offset11 = (y1 * image.GetWidth() + x1) * bytesPerPixel;
            int offset12 = (y2 * image.GetWidth() + x1) * bytesPerPixel;
            int offset21 = (y1 * image.GetWidth() + x2) * bytesPerPixel;
            int offset22 = (y2 * image.GetWidth() + x2) * bytesPerPixel;

            unsigned char red11 = data[offset11];
            unsigned char green11 = data[offset11 + 1];
            unsigned char blue11 = data[offset11 + 2];

            unsigned char red12 = data[offset12];
            unsigned char green12 = data[offset12 + 1];
            unsigned char blue12 = data[offset12 + 2];

            unsigned char red21 = data[offset21];
            unsigned char green21 = data[offset21 + 1];
            unsigned char blue21 = data[offset21 + 2];

            unsigned char red22 = data[offset22];
            unsigned char green22 = data[offset22 + 1];
            unsigned char blue22 = data[offset22 + 2];

            // Interpolacja dla ka¿dego kana³u koloru
            unsigned char red = (1 - dx) * (1 - dy) * red11 + dx * (1 - dy) * red21 +
                (1 - dx) * dy * red12 + dx * dy * red22;
            unsigned char green = (1 - dx) * (1 - dy) * green11 + dx * (1 - dy) * green21 +
                (1 - dx) * dy * green12 + dx * dy * green22;
            unsigned char blue = (1 - dx) * (1 - dy) * blue11 + dx * (1 - dy) * blue21 +
                (1 - dx) * dy * blue12 + dx * dy * blue22;

            // Ustawienie koloru piksela w nowym obrazie
            newImage.SetRGB(x, y, red, green, blue);
        }
    }

    return newImage;
}

void GUIMyFrame1::Resize(wxSizeEvent& event) {
    wxSize sizerSize = this->GetSizer()->GetSize();
    if (sizerSize.GetWidth() > sizerSize.GetHeight() + 260)
        m_panel1->SetSize(sizerSize.GetHeight(), sizerSize.GetHeight());
    else {
        m_panel1->SetSize(sizerSize.GetWidth() - 260, sizerSize.GetWidth() - 260);
    }
}