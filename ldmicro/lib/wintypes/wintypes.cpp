#include "wintypes.h"

size_t max(size_t A, size_t B)
{
    if(A>B)
        return A;
    else
        return B;
}

HFONT CreateFont(int nHeight, int nWidth, int nOrientation, int fnWeight,
    DWORD fdwItalic, LPCTSTR lpszFace)
{
    HFONT font = (HFONT)malloc(strlen(lpszFace) + 1 + sizeof(FONT));
    font->nHeight = nHeight;
    font->nWidth = nWidth;
    font->nOrientation = nOrientation;
    font->fnWeight = fnWeight;
    font->fdwItalic = fdwItalic;
    font->lpszFace = (char*)malloc(strlen(lpszFace)+1);
    strcpy(font->lpszFace, lpszFace);
    
    return font;
}