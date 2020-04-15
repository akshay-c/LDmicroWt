#ifndef __COMPILECOMM_H_
#define __COMPILECOMM_H_

#include <setjmp.h>

void AllocStart(void);
DWORD AllocOctetRam(void);
void AllocBitRam(DWORD *addr, int *bit);
void MemForVariable(char *name, DWORD *addrl, DWORD *addrh);
BYTE MuxForAdcVariable(char *name);
void MemForSingleBit(char *name, BOOL forRead, DWORD *addr, int *bit);
void MemCheckForErrorsPostCompile(void);
void BuildDirectionRegisters(BYTE *isInput, BYTE *isOutput);
void ComplainAboutBaudRateError(int divisor, double actual, double err);
void ComplainAboutBaudRateOverflow(void);
#define CompileError() longjmp(CompileErrorBuf, 1)
extern jmp_buf CompileErrorBuf;

#endif