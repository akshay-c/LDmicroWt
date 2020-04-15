#ifndef __UNDOREDO_H
#define __UNDOREDO_H

void FreeCircuit(int which, void *any);
void FreeEntireProgram(void);
void UndoUndo(void);
void UndoRedo(void);
void UndoRemember(void);
void UndoFlush(void);
BOOL CanUndo(void);
#endif