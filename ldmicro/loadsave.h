#ifndef __LOADSAVE_H
#define __LOADSAVE_H

// loadsave.cpp
BOOL LoadProjectFromFile(char *filename);
BOOL SaveProjectToFile(char *filename);
void ManageLineEnding(char* line);

#endif