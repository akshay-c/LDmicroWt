#include "wttypes.h"

WSize::WSize()
    :_width(),
    _height()
{ }

WSize::WSize(Wt::WLength width, Wt::WLength height)
    :_width(width),
    _height(height)
{ }

void WSize::setWidth(Wt::WLength width)
{
    _width = width;
}

void WSize::setHeight(Wt::WLength height)
{
    _height = height;
}

Wt::WLength WSize::width()
{
    return _width;
}

Wt::WLength WSize::height()
{
    return _height;
}

COLORREF RGB(int red, int green, int blue)
{
    COLORREF col(red, green, blue);

    return col;
}

void TextOut(HWID hWid, HCRDC hcr, int nXStart, int nYStart, LPCTSTR lpString, int cchString)
{

}

void SetTextColor(HCRDC hcr, COLORREF color)
{
}

void SetBkColor(HWID widget, HCRDC hcr, COLORREF bkCol)
{
}
void SelectObject(HCRDC hcr, HFONT hfont)
{}

COLORREF GetTextColor(HCRDC Hdc)
{
}

int FillRect(HCRDC hDC, const Wt::WRectF *lprc, HBRUSH hbr)
{
}