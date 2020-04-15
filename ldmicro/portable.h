#ifndef __PORTABLE_H
#define __PORTABLE_H

#include<limits.h>
#include<cstring>

#define MAX_PATH PATH_MAX
#define CONST const


/// Macro functions
// #define max(_A, _B) std::max(_A, _B)
#define TRUE true
#define FALSE false

/// Typedefs
//typedef int64_t __int64;
typedef bool BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned int UINT;
typedef size_t SIZE_T;
typedef long LONG;
typedef wchar_t WCHAR;
typedef char CHAR;

typedef CONST WCHAR *LPCWSTR;
typedef CONST CHAR *LPCSTR; /// should be __nullterminated
typedef WORD ATOM;

typedef bool BOOL;
typedef signed short SWORD;
typedef signed long SDWORD;


#endif