#include "draw_outputdev.h"
#include "draw.h"
#include "schematic.h"

#define X_RIGHT_PADDING 30

void (*DrawChars)(HCRDC Hcr, int, int, const char *);

SyntaxHighlightingColours HighlightColours;

// After an undo all the memory addresses change but make an effort to put
// the cursor roughly where it should be.
int SelectedGxAfterNextPaint = -1;
int SelectedGyAfterNextPaint = -1;

// After pushing a rung up or down the position of that rung in the table
// changes, but the cursor should stay where it was.
BOOL ScrollSelectedIntoViewAfterNextPaint;

// Buffer that we write to when exporting (drawing) diagram to a text file. 
// Dynamically allocated so that we're at least slightly efficient.
static char **ExportBuffer;

// The fonts that we will use to draw the ladder diagram: fixed width, one
// normal-weight, one bold.
HFONT       FixedWidthFont;
HFONT       FixedWidthFontBold;

// Different colour brushes for right and left buses in simulation, but same
// colour for both in edit mode; also for the backgrounds in simulation and
// edit modes.
static HBRUSH   BusRightBus;
static HBRUSH   BusLeftBrush;
static HBRUSH   BusBrush;
static HBRUSH   BgBrush;
static HBRUSH   SimBgBrush;

// Parameters that determine our offset if we are scrolled
// int ScrollXOffset;
// int ScrollYOffset;
// int ScrollXOffsetMax;
// int ScrollYOffsetMax;

// Is the cursor currently drawn? We XOR it so this gets toggled.
static BOOL CursorDrawn;


void PaintWidget::paintEvent(Wt::WPaintDevice *device)
{
    painter.begin(device);
    // painter.setClipping(true);
    // painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setBrush(Wt::WBrush(Wt::WColor(Wt::StandardColor::Blue)));
    painter.drawRect(0, 0, 100, 50);
    painter.end();
    /*HCRDC Hcr = &painter;

    // ok();

    Wt::WLength bw = width();// = r.right;
    Wt::WLength bh = height();

    /// now figure out how we should draw the ladder logic
    ColsAvailable = ProgCountWidestRow();
    if(ColsAvailable < ScreenColsAvailable()) {
        ColsAvailable = ScreenColsAvailable();
    }
    memset(DisplayMatrix, 0, sizeof(DisplayMatrix));
    SelectionActive = FALSE;
    // memset(&Cursor, 0, sizeof(Cursor));

    DrawChars = DrawCharsToScreen;

    int i;
    int cy = 0;
    int cx = 0;
    // int rowsAvailable = ScreenRowsAvailable();

    for(i = 0; i < Prog.numRungs; i++) {
        int thisHeight = POS_HEIGHT*CountHeightOfElement(ELEM_SERIES_SUBCKT,
            Prog.rungs[i]);

        // For speed, there is no need to draw everything all the time, but
        // we still must draw a bit above and below so that the DisplayMatrix
        // is filled in enough to make it possible to reselect using the
        // cursor keys.
        /*if(((cy + thisHeight) >= (ScrollYOffset - 8)*POS_HEIGHT) &&
            (cy < (ScrollYOffset + rowsAvailable + 8)*POS_HEIGHT))*/
      /*  {
            SetBkColor(DrawWindow, Hcr,
                InSimulationMode ? HighlightColours.simBg :
                HighlightColours.bg);
            SetTextColor(Hcr, InSimulationMode ? HighlightColours.simRungNum :
                HighlightColours.rungNum);
            SelectObject(Hcr, FixedWidthFont);
            int rung = i + 1;
            int y = Y_PADDING + FONT_HEIGHT*cy;
            int yp = y; /*+ FONT_HEIGHT*(POS_HEIGHT/2) - 
                POS_HEIGHT*FONT_HEIGHT*ScrollYOffset;*/
            
        /*    if(rung < 10) {
                char r[1] = { rung + '0' };
                TextOut(DrawWindow, Hcr, 8 + FONT_WIDTH, yp, r, 1);
            } else {
                char r[2] = { (rung / 10) + '0', (rung % 10) + '0' };
                TextOut(DrawWindow, Hcr, 8, yp, r, 2);
            }

            cx = 0;
            DrawElement(Hcr, ELEM_SERIES_SUBCKT, Prog.rungs[i], &cx, &cy, 
                Prog.rungPowered[i]);
        }

        cy += thisHeight;
        cy += POS_HEIGHT;
    }
    WSize DWSize = this->size();
    int newHeight = ((cy + (POS_HEIGHT/2)) * FONT_HEIGHT + Y_PADDING + 50);
    if((DWSize.height().value() + POS_HEIGHT) < newHeight)
    {
        DWSize.setHeight(newHeight);
    }
    int newWidth = ((cx + (POS_WIDTH/2)) * FONT_WIDTH + X_PADDING);
    if((DWSize.width().value() + POS_WIDTH) < newWidth)
    {
        DWSize.setWidth(newWidth);
    }
    DrawWindow->resize(DWSize);

    cy -= 2;
    DrawEndRung(Hcr, 0, cy);
    
    if(SelectedGxAfterNextPaint >= 0) {
        MoveCursorNear(SelectedGxAfterNextPaint, SelectedGyAfterNextPaint);
        // InvalidateRect(DrawWindow, NULL, FALSE);
        SelectedGxAfterNextPaint = -1;
        SelectedGyAfterNextPaint = -1;
    } else if(ScrollSelectedIntoViewAfterNextPaint && Selected) {
        SelectElement(-1, -1, Selected->selectedState);
        ScrollSelectedIntoViewAfterNextPaint = FALSE;
        // InvalidateRect(DrawWindow, NULL, FALSE);
    } else {
        if(!SelectionActive) {
            if(Prog.numRungs > 0) {
                if(MoveCursorTopLeft()) {
                    // InvalidateRect(DrawWindow, NULL, FALSE);
                }
            }
        }
    }

    /// draw the `buses' at either side of the screen
    Wt::WRectF r;
    /*r.setLeft(X_PADDING - FONT_WIDTH);
    r.setTop(0);
    r.setRight(r.left() + 4);
    r.setBottom(this->height());
    FillRect(Hcr, &r, InSimulationMode ? BusLeftBrush : BusBrush);
    r.setLeft(POS_WIDTH*FONT_WIDTH*ColsAvailable + 32);
    r.setRight(POS_WIDTH*FONT_WIDTH*ColsAvailable + 32);*/
    /*FillRect(Hcr, &r, InSimulationMode ? BusRightBus : BusBrush);
    // InvalidateRect(DrawWindow, NULL, FALSE);
 
    CursorDrawn = FALSE;*/

    // ok();
    
}

void PaintWidget::resize(WSize size)
{
    resize(size.width(),size.height());
}

void PaintWidget::resize(Wt::WLength width, Wt::WLength height)
{
    Wt::WPaintedWidget::resize(width,height);
}

WSize PaintWidget::size()
{
    WSize PWSize(this->width(), this->height());
    return PWSize;
}

PaintWidget::PaintWidget() : Wt::WPaintedWidget()
{
    // resize(Wt::WLength(200),Wt::WLength(60));
    setStyleClass("Wt-PaintWidget");
    setAttributeValue("style", "width:100%; height:100%;");
    repaint();
    /*resize(Wt::WLength(100, Wt::LengthUnit::Percentage),
        Wt::WLength(100, Wt::LengthUnit::Percentage));*/
}

//-----------------------------------------------------------------------------
// Total number of columns that we can display in the given amount of 
// window area. Need to leave some slop on the right for the scrollbar, of
// course.
//-----------------------------------------------------------------------------
double ScreenColsAvailable(void)
{
    double rw = DrawWindow->width().value();

    return (rw - (X_PADDING + X_RIGHT_PADDING)) / (POS_WIDTH*FONT_WIDTH);
}

//-----------------------------------------------------------------------------
// Output a string to the screen at a particular location, in character-
// sized units.
//-------------------------------SyntaxHighlightingColours HighlightColours;----------------------------------------------
static void DrawCharsToScreen(HCRDC Hcr, int cx, int cy, const char *str)
{
    /*if(cy < -2) return;

    COLORREF prev;
    BOOL firstTime = TRUE;
    BOOL inNumber = FALSE;
    BOOL inComment = FALSE;
    int inBrace = 0;
    for(; *str; str++, cx++) {
        int x = cx * FONT_WIDTH + X_PADDING;
        int y = cy * FONT_HEIGHT + Y_PADDING;

        BOOL hiOk = !(InSimulationMode || ThisHighlighted);

        if(strchr("{}[]", *str) && hiOk && !inComment)  {
            if(*str == '{' || *str == '[') inBrace++;
            if(inBrace == 1) {
                prev = GetTextColor(Hcr);
                SetTextColor(Hcr, HighlightColours.punct);
                TextOut(DrawWindow, Hcr, x, y, str, 1);
                SetTextColor(Hcr, prev);
            } else {
                TextOut(DrawWindow, Hcr, x, y, str, 1);
            }
            if(*str == ']' || *str == '}') inBrace--;
        } else if((
            (isdigit(*str) && (firstTime || isspace(str[-1]) 
                || str[-1] == ':' || str[-1] == '[')) ||
            (*str == '-' && isdigit(str[1]))) && hiOk && !inComment)
        {
            prev = GetTextColor(Hcr);
            SetTextColor(Hcr, HighlightColours.lit);
            TextOut(DrawWindow, Hcr, x, y, str, 1);
            SetTextColor(Hcr, prev);
            inNumber = TRUE;
        } else if(*str == '\x01') {
            cx--;
            if(hiOk) {
                prev = GetTextColor(Hcr);
                SetTextColor(Hcr, HighlightColours.op);
            }
        } else if(*str == '\x02') {
            cx--;
            if(hiOk) {
                SetTextColor(Hcr, prev);
                inComment = FALSE;
            }
        } else if(*str == '\x03') {
            cx--;
            if(hiOk) {
                prev = GetTextColor(Hcr);
                SetTextColor(Hcr, HighlightColours.comment);
                inComment = TRUE;
            }
        } else if(inNumber) {
            if(isdigit(*str) || *str == '.') {
                prev = GetTextColor(Hcr);
                SetTextColor(Hcr, HighlightColours.lit);
                TextOut(DrawWindow, Hcr, x, y, str, 1);
                SetTextColor(Hcr, prev);
            } else {
                TextOut(DrawWindow, Hcr, x, y, str, 1);
                inNumber = FALSE;
            }
        } else {
            TextOut(DrawWindow, Hcr, x, y, str, 1);
        }

        firstTime = FALSE;
    }*/
}