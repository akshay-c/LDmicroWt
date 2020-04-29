#ifndef __DRAW_OUTPUT_H
#define __DRAW_OUTPUT_H
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include "wttypes.h"
#include "ldmicro.h"

// extern HFONT FixedWidthFont;
// extern HFONT FixedWidthFontBold;
extern int SelectedGxAfterNextPaint;
extern int SelectedGyAfterNextPaint;
extern BOOL ScrollSelectedIntoViewAfterNextPaint;


class PaintWidget : public Wt::WPaintedWidget
{
public:
    // MyWidget();
    // PaintWidget(QWidget* parent): QWidget(parent)
    // {}
    // void keyPressEvent(QKeyEvent* event);
    // void mouseReleaseEvent(QMouseEvent* event);
    // void mouseDoubleClickEvent(QMouseEvent* event);
    PaintWidget();
    WSize size();
    void resize(WSize size);
    void resize(Wt::WLength width, Wt::WLength height);
 
protected:
    void paintEvent(Wt::WPaintDevice *device);
    // void timerEvent(QTimerEvent *event);
private:
    Wt::WPainter    painter;
    HBRUSH          BusRightBus;
    HBRUSH          BusLeftBrush;
    HBRUSH          BusBrush;
    HBRUSH          BgBrush;
    HBRUSH          SimBgBrush;
};

extern PaintWidget*     DrawWindow;

static void DrawCharsToScreen(HCRDC Hcr, int cx, int cy, const char *str);
double ScreenColsAvailable(void);

#endif

void SetSyntaxHighlightingColours(void)