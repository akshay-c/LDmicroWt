#ifndef __WT_TYPES_H
#define __WT_TYPES_H

#include <Wt/WColor.h>
#include <Wt/WPainter.h>
#include <Wt/WFont.h>
#include <Wt/WRectF.h>
#include <Wt/WLength.h>
#include "wintypes.h"

typedef class tagColorReferance: public Wt::WColor{
    public:
    tagColorReferance()
    {
        this->setRgb(0,0,0);
    }

    tagColorReferance(int r, int g, int b)
    {
        this->setRgb(r,g,b);
    }

    bool operator== (tagColorReferance& arg1)
    {
        if( (arg1.red() == this->red()) &&
            (arg1.green() == this->green()) &&
            (arg1.blue() == this->blue()) )
            return true;
        else
            return false;
    }

} COLORREF, *HBRUSH;

void TextOut(
    HWID    hWid,
    HCRDC   hcr,
    int     nXStart,
    int     nYStart,
    LPCTSTR lpString,
    int     cchString);

COLORREF RGB(int red, int green, int blue);
void SetTextColor(HCRDC hcr, COLORREF color);
void SetBkColor(HWID widget, HCRDC hcr, COLORREF bkCol);
void SelectObject(HCRDC hcr, HFONT hfont);
COLORREF GetTextColor(HCRDC Hdc);
int FillRect(HCRDC hDC, const Wt::WRectF *lprc, HBRUSH hbr);

class WSize
{
public:
    WSize();
    WSize(Wt::WLength width,Wt::WLength height);
    void setWidth(Wt::WLength width);
    void setHeight(Wt::WLength height);
    Wt::WLength width();
    Wt::WLength height();
private:
    Wt::WLength _width;
    Wt::WLength _height;
};

#endif