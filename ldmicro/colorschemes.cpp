#include "colorschemes.h"
#include "wttypes.h"

SyntaxHighlightingColours schemes[] = {
    {                           // 0
            RGB(0, 0, 0),           // bg
            RGB(255, 255, 225),     // def
            RGB(255, 110, 90),      // selected
            RGB(255, 150, 90),      // op
            RGB(255, 255, 100),     // punct
            RGB(255, 160, 160),     // lit
            RGB(120, 255, 130),     // name
            RGB(130, 130, 130),     // rungNum
            RGB(130, 130, 245),     // comment

            RGB(255, 255, 255),     // bus

            RGB(0, 0, 0),           // simBg
            RGB(130, 130, 130),     // simRungNum
            RGB(170, 200, 200),     // simOff
            RGB(255, 150, 150),     // simOn

            RGB(255, 150, 150),     // simBusLeft
            RGB(150, 150, 255),     // simBusRight
        },
};

void ColorSchemes::SetSyntaxHighlightingColours(int index)
{
    myColor = schemes[index];
}