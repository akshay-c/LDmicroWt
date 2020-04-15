#ifndef __SCHEMATIC_H_
#define __SCHEMATIC_H_
#include "portable.h"
#include "ldmicro.h"

void SelectElement(int gx, int gy, int state);
void MoveCursorKeyboard(int keyCode);
void MoveCursorMouseClick(int x, int y);
BOOL MoveCursorTopLeft(void);
void EditElementMouseDoubleclick(int x, int y);
void EditSelectedElement(void);
void MakeResetOnlySelected(void);
void MakeSetOnlySelected(void);
void MakeNormalSelected(void);
void NegateSelected(void);
void ForgetFromGrid(void *p);
void ForgetEverything(void);
void WhatCanWeDoFromCursorAndTopology(void);
BOOL FindSelected(int *gx, int *gy);
void MoveCursorNear(int gx, int gy);

#define DISPLAY_MATRIX_X_SIZE 16
#define DISPLAY_MATRIX_Y_SIZE 512
extern ElemLeaf *DisplayMatrix[DISPLAY_MATRIX_X_SIZE][DISPLAY_MATRIX_Y_SIZE];
extern int DisplayMatrixWhich[DISPLAY_MATRIX_X_SIZE][DISPLAY_MATRIX_Y_SIZE];
extern ElemLeaf DisplayMatrixFiller;
#define PADDING_IN_DISPLAY_MATRIX (&DisplayMatrixFiller)
#define VALID_LEAF(x) ((x) != NULL && (x) != PADDING_IN_DISPLAY_MATRIX)
extern ElemLeaf *Selected;
extern int SelectedWhich;

// extern QRect Cursor;
extern BOOL CanInsertEnd;
extern BOOL CanInsertOther;
extern BOOL CanInsertComment;


#endif
