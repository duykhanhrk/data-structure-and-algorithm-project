// draw two lines and a circle on your console screen
// original BCX basic code by Sir Joe Caverly
// translated to C code and modified to work with Dev-C++
// link with GDI32.lib or with Dev-C++ link libgdi32.a via
// Project>>Project Options>>Parameters>>Add Lib>>libgdi32.a
// this is a Windows Console Application


#include <windows.h>    // Win32API Header File
#include <cstring>
#include <cstdio>

using namespace std;

#define Red  RGB (255,0,0)
#define Lime RGB (206,255,0)
#define Blue RGB (0,0,255)

static HWND    hConWnd;

int     BCX_Line (HWND,int,int,int,int,int=0,HDC=0);
int     BCX_Circle (HWND,int,int,int,int=0,int=0,HDC=0);

HWND    GetConsoleWndHandle (void);

int main()
{
  hConWnd = GetConsoleWndHandle();
  if (hConWnd)
  {
    // be creative here, draw your own circles or lines

    //   hwin, centerX, centerY, radius, pencolor
    BCX_Circle(hConWnd, 150, 130, 0, Blue);
    //   hwin, ulcX, ulcY, lrcX, lrcY, pencolor
    BCX_Line(hConWnd, 5, 5, 250, 5, Red);
    BCX_Line(hConWnd, 295, 5, 5, 250, Lime);

    getchar();  // wait
  }
  return 0;
}


int BCX_Line (HWND Wnd,int x1,int y1,int x2,int y2,int Pen,HDC DrawHDC)
{
  int a,b=0;
  HPEN hOPen;
  // penstyle, width, color
  HPEN hNPen = CreatePen(PS_SOLID, 250, Pen);
  if (!DrawHDC) DrawHDC = GetDC(Wnd), b = 1;
  hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
  // starting point of line
  MoveToEx(DrawHDC, x1, y1, NULL);
  // ending point of line
  a = LineTo(DrawHDC, x2, y2);
  DeleteObject(SelectObject(DrawHDC, hOPen));
  if (b) ReleaseDC(Wnd, DrawHDC);
  return a;
}


// converts circle(centerX,centerY,radius,pen) to WinApi function
// ellipse inside box with upper left and lower right coordinates
int BCX_Circle(HWND Wnd,int X,int Y,int R,int Pen,int Fill,HDC DrawHDC)
{
  int a, b = 0;
  if (!DrawHDC) DrawHDC = GetDC(Wnd), b = 1;
  // penstyle, width, color
  HPEN   hNPen = CreatePen(PS_SOLID, 2, Pen);
  HPEN   hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
  HBRUSH hOldBrush;
  HBRUSH hNewBrush;
  // if true will fill circle with pencolor
  if (Fill)
  {
    hNewBrush = CreateSolidBrush(Pen);
    hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
  }
  else
  {
    hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
  }
  a = Ellipse(DrawHDC, X-R, Y+R, X+R, Y-R);
  DeleteObject(SelectObject(DrawHDC, hOPen));
  DeleteObject(SelectObject(DrawHDC, hOldBrush));
  if (b) ReleaseDC(Wnd, DrawHDC);
  return a;
}


// the hoop ...
HWND GetConsoleWndHandle(void)
{
  HWND hConWnd;
  OSVERSIONINFO os;
  char szTempTitle[64], szClassName[128], szOriginalTitle[1024];

  os.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
  GetVersionEx( &os );
  // may not work on WIN9x
  if ( os.dwPlatformId == VER_PLATFORM_WIN32s ) return 0;

  GetConsoleTitle( szOriginalTitle, sizeof( szOriginalTitle ) );
  sprintf( szTempTitle,"%u - %u", GetTickCount(), GetCurrentProcessId() );
  SetConsoleTitle( szTempTitle );
  Sleep( 40 );
  // handle for NT
  hConWnd = FindWindow( NULL, szTempTitle );
  SetConsoleTitle( szOriginalTitle );

  // may not work on WIN9x
  if ( os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
  {
    hConWnd = GetWindow( hConWnd, GW_CHILD );
    if ( hConWnd == NULL )  return 0;
    GetClassName( hConWnd, szClassName, sizeof ( szClassName ) );
    while ( strcmp( szClassName, "ttyGrab" ) != 0 )
    {
      hConWnd = GetNextWindow( hConWnd, GW_HWNDNEXT );
      if ( hConWnd == NULL )  return 0;
      GetClassName( hConWnd, szClassName, sizeof( szClassName ) );
    }
  }
  return hConWnd;
}
