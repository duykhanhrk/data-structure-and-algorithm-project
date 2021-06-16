#include "color.h"

/* Logic */

// Clear screen
void ClearScreen() {
	system(CLEAR_SCREEN_COMMAND);
}

// Clear screen with background color
void ClearScreenWithBackground(color_tp b_color) {
	SetBackground(b_color);
	system(CLEAR_SCREEN_COMMAND);
}

// Set foreground color
void SetForeground(color_tp f_color) {
	CURRENT_FOREGROUND = f_color;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, CURRENT_FOREGROUND | CURRENT_BACKGROUND);
}

// Set background color
void SetBackground(color_tp b_color) {
	CURRENT_BACKGROUND = b_color;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, CURRENT_FOREGROUND | CURRENT_BACKGROUND);
}

// Set foreground and background color
void SetColor(color_tp f_color, color_tp b_color) {
	CURRENT_BACKGROUND = b_color;
	CURRENT_FOREGROUND = f_color;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, CURRENT_FOREGROUND | CURRENT_BACKGROUND);
}
