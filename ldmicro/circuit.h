#ifndef __CIRCUIT_H_
#define __CIRCUIT_H_
#include "portable.h"
#include "ldmicro.h"
void AddTimer(int which);
void AddCoil(void);
void AddCoilNeg(void);
void AddCoilRes(void);
void AddCoilSet(void);
void AddContact(void);
void AddContactNeg(void);
void AddEmpty(int which);
void AddMove(void);
void AddMath(int which);
void AddCmp(int which);
void AddReset(void);
void AddCounter(int which);
void AddReadAdc(void);
void AddSetPwm(void);
void AddUart(int which);
void AddPersist(void);
void AddComment(char *text);
void AddShiftRegister(void);
void AddMasterRelay(void);
void AddLookUpTable(void);
void AddPiecewiseLinear(void);
void AddFormattedString(void);
void DeleteSelectedFromProgram(void);
void DeleteSelectedRung(void);
void InsertRung(BOOL afterCursor);
int  RungContainingSelected(void);
BOOL ItemIsLastInCircuit(ElemLeaf *item);
BOOL UartFunctionUsed(void);
BOOL PwmFunctionUsed(void);
void PushRungUp(void);
void PushRungDown(void);
void NewProgram(void);
ElemLeaf *AllocLeaf(void);
ElemSubcktSeries *AllocSubcktSeries(void);
ElemSubcktParallel *AllocSubcktParallel(void);
void FreeCircuit(int which, void *any);
void FreeEntireProgram(void);
void UndoUndo(void);
void UndoRedo(void);
void UndoRemember(void);
void UndoFlush(void);
BOOL CanUndo(void);

#endif