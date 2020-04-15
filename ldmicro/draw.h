#ifndef __DRAW_H_
#define __DRAW_H_

#include "wintypes.h"
#include "ldmicro.h"

extern int ColsAvailable;
extern BOOL SelectionActive;
extern BOOL ThisHighlighted;

int ProgCountWidestRow(void);
int CountHeightOfElement(int which, void *elem);
static int CountWidthOfElement(int which, void *elem, int soFar);
static BOOL CheckBoundsUndoIfFails(int gx, int gy);
static void VerticalWire(HCRDC Hcr, int cx, int cy);
static void NormText(HCRDC Hcr);
static void EmphText(HCRDC Hcr);
static void NameText(HCRDC Hcr);
static void BodyText(HCRDC Hcr);
static void PoweredText(HCRDC Hcr, BOOL powered);
static int FormattedStrlen(const char *str);
static void CenterWithSpaces(HCRDC Hcr, int cx, int cy, char *str, BOOL powered,
    BOOL isName);
static void CenterWithWiresWidth(HCRDC Hcr, int cx, int cy,const char *str,
    BOOL before, BOOL after, int totalWidth);
static void CenterWithWires(HCRDC Hcr, int cx, int cy, const char *str,
    BOOL before, BOOL after);
static BOOL DrawEndOfLine(HCRDC Hcr, int which, ElemLeaf *leaf,
    int *cx, int *cy, BOOL poweredBefore);
static BOOL DrawLeaf(HCRDC Hcr, int which, ElemLeaf *leaf, int *cx, int *cy,
    BOOL poweredBefore);
BOOL DrawElement(HCRDC Hcr, int which, void *elem,
    int *cx, int *cy, BOOL poweredBefore);
void DrawEndRung(HCRDC Hcr, int cx, int cy);

#endif