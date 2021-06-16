/* Cursor */

#ifndef __SUPPORT_CURSOR__
#define __SUPPORT_CURSOR__

/* Define */

// Cursor postion
#define CURSOR_POSITION_X CursorPositionX()
#define CURSOR_POSITION_Y CursorPositionY()

// Window rows, columns
#define WINDOW_ROWS WindowRows()
#define WINDOW_COLUMNS WindowColumns()

#define CURSOR_VISIBLE CursorVisible()
#define HideCursor CursorVisible(false)
#define ShowCursor CursorVisible(true)

#ifdef __cplusplus
extern "C" {
#endif

/* Prototype */

// Cursor
void GotoXY(int x, int y);
int CursorPositionX();
int CursorPositionY();

bool IsCursorVisible();
void CursorVisible(bool);

// Window
int WindowRows();
int WindowColumns();

#include "cursor.cpp"

#ifdef __cplusplus
}
#endif

#endif
