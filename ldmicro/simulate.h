#ifndef __SIMULATE_H
#define __SIMULATE_H
#include "portable.h"

void SimulateOneCycle(BOOL forceRefresh);
BOOL PlcCycleTimer(BOOL kill);
void StartSimulationTimer(void);
void ClearSimulationData(void);
void DescribeForIoList(char *name, char *out);
void SimulationToggleContact(char *name);
void SimulationSetContact(char* name);
void SimulationResetContact(char* name);
void SetAdcShadow(char *name, SWORD val);
SWORD GetAdcShadow(char *name);
void DestroyUartSimulationWindow(void);
void ShowUartSimulationWindow(void);
extern BOOL InSimulationMode;

extern BOOL SimulateRedrawAfterNextCycle;

#endif