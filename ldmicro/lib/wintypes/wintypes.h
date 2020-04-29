#ifndef __WIN_TYPES_H
#define __WIN_TYPES_H
#include <sys/mman.h>
#include <Wt/WPainter.h>
#include <Wt/WWidget.h>

#define MAX_PATH PATH_MAX

/// CALLBACK or __stdcall os defined empty
#define CALLBACK
#define CONST const

/// Meamory flags
#define HEAP_ZERO_MEMORY 0x00000008

/// Image loading flags
#define IMAGE_ICON      1
#define LDMICRO_ICON    ":/ldmicro.ico"

/// Font flags
#define FW_REGULAR   0x00000001L
#define FW_BOLD      0x00000002L

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

#ifdef UNICODE
 typedef LPCWSTR LPCTSTR; 
#else
 typedef LPCSTR LPCTSTR;
#endif

typedef WCHAR *LPWSTR;
typedef CHAR *LPSTR;

#ifdef UNICODE
 typedef LPWSTR LPTSTR;
#else
 typedef LPSTR LPTSTR;
#endif

typedef void *PVOID;
typedef void *LPVOID;
typedef PVOID HMODULE;
typedef PVOID HHOOK;

typedef PVOID HANDLE;
typedef HANDLE HINSTANCE;
typedef HANDLE HGDIOBJ;

/*typedef QTreeWidget*    HLIST;
typedef QList<QTreeWidgetItem *>     ITLIST;
typedef QMenu*      HMENU;
typedef ITLIST      HITLIST;*/
typedef Wt::WPainter*   HCRDC;
typedef Wt::WWidget*    HWID;
//typedef Wt::WFont*      HFONT;
/*typedef QWidget*    HWND;
typedef QScrollArea* WM_SCROLL;
*/

/// Check if system is x64 or x86
    #if defined(__UNIX64)
    typedef uint64_t UINT_PTR;
    #else 
    typedef unsigned int UINT_PTR;
    #endif
 
typedef UINT_PTR WPARAM;

    #if defined(__UNIX64)
    typedef __int64_t LONG_PTR; 
    #else
    typedef long LONG_PTR;
    #endif

typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;

size_t max(size_t A, size_t B);

typedef struct FontTag {
    int     nHeight;
    int     nWidth;
    int     nOrientation;
    int     fnWeight;
    DWORD   fdwItalic;
    LPTSTR lpszFace;
} *HFONT, FONT;

HFONT CreateFont(
    int     nHeight,
    int     nWidth,
    int     nOrientation,
    int     fnWeight,
    DWORD   fdwItalic,
    LPCTSTR lpszFace);

#endif

