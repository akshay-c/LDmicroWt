#ifndef __MISCUTIL_H
#define __MISCUTIL_H
#include "portable.h"
#include "wintypes.h"
#include "ldmicro.h"
#define oops() { \
        dbp("bad at %d %s\n", __LINE__, __FILE__); \
        Error("Internal error at line %d file '%s'\n", __LINE__, __FILE__); \
        exit(1); \
    }

void dbp(char *str, ...);
void Error(char *str, ...);
void *CheckMalloc(size_t n);
void CheckFree(void *p);
extern HANDLE MainHeap;
void StartIhex(FILE *f);
void WriteIhex(FILE *f, BYTE b);
void FinishIhex(FILE *f);
char *IoTypeToString(int ioType);
void PinNumberForIo(char *dest, PlcProgramSingleIo *io);
// QDialog* CreateWindowClient(char *windowName,
//     int x, int y, int width, int height, HWND parent);

void MakeComponentListClass(void);
void MakeNamingListClass(void);
void MakeDialogBoxClass(void);
// void NiceFont(HWID h);
// void FixedFont(HWID h);
// void SetFont(HWID h, HFONT f);
void CompileSuccessfulMessage(char *str);
extern BOOL RunningInBatchMode;
// extern HFONT MyNiceFont;
// extern HFONT MyFixedFont;
// extern HWID OkButton;
// extern HWID CancelButton;
// extern BOOL DialogDone;
// extern BOOL DialogCancel;

#endif __MISCUTIL_H