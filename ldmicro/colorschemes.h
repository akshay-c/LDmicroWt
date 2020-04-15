#ifndef __COLORSCHEMES_H
#define __COLORSCHEMES_H

#include "ldmicro.h"

class ColorSchemes
{
private:
    SyntaxHighlightingColours myColor;
public:
    void SetSyntaxHighlightingColours(int index);
};
extern SyntaxHighlightingColours schemes[];

#endif