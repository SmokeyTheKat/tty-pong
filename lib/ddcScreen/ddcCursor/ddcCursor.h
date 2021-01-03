#ifndef __ddcCursor__
#define __ddcCursor__

#include "../../ddcVec/ddcVec.h"
#include "../../ddcPrint/ddcPrint.h"
#include "../../ddcMath/ddcMath.h"
#include "../../ddcString/ddcString.h"
#include "../ddcColors/ddcColors.h"

#define __CURSOR_STACK_LENGTH 10

const ddsize g_consoleWidth = 170;
const ddsize g_consoleHeight = 47;

ddVec2 g_cursorPosition;
ddColor g_cursorFGColor;
ddColor g_cursorBGColor;

static ddVec2 __v2empty;
static ddVec2 __cursorPositionStack[__CURSOR_STACK_LENGTH];
static ddColor __cursorFGStack[__CURSOR_STACK_LENGTH];
static ddColor __cursorBGStack[__CURSOR_STACK_LENGTH];

void init_cursor(void);
void cursor_move_to(int x, int y);
void cursor_move_to_vec(ddVec2 v);
void cursor_move(int x, int y);
void cursor_move_vec(ddVec2 v);
void cursor_move_up(void);
void cursor_move_down(void);
void cursor_move_left(void);
void cursor_move_right(void);
void cursor_return(void);
void cursor_home(void);
void cursor_delete_line(void);
bool cursor_pop(void);
bool cursor_push(void);
void cursor_write_char(char c);
void cursor_write_cstring(const char* ch);
void cursor_write_ddString(const ddString ds);
void cursor_write_nl(char c);
void cursor_write_char_nl(char c);
void cursor_write_cstring_nl(const char* ch);
void cursor_write_ddString_nl(const ddString ds);
void cursor_clear(void);
void cursor_set_fg_color(ddColor dc);
void cursor_set_fg_color_rgb(int r, int g, int b);
void cursor_set_bg_color(ddColor dc);
void cursor_set_bg_color_rgb(int r, int g, int b);
bool cursor_color_push(void);
bool cursor_color_pop(void);

void init_cursor(void)
{
	__v2empty = make_ddVec2(-1, -1);
	g_cursorBGColor = make_ddColor(0, 0, 0);
	g_cursorFGColor = make_ddColor(255, 255, 255);
	g_cursorPosition = make_ddVec2(0, 0);
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
		__cursorPositionStack[i] = make_ddVec2(-1, -1);
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
		__cursorFGStack[i] = make_ddColor(0,420,0);
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
		__cursorBGStack[i] = make_ddColor(0,420,0);
}


void cursor_move_to(int x, int y)
{
	x++;
	y++;
	g_cursorPosition.x = x;
	g_cursorPosition.y = y;
	ddPrintf("\x1b[%d;%dH", y, x);
}
void cursor_move_to_vec(ddVec2 v)
{
	cursor_move_to(v.x, v.y);
}
void cursor_move(int x, int y)
{
	g_cursorPosition.x += x;
	g_cursorPosition.y += y;
	int dx = (x >= 0) ? 1 : -1;
	int dy = (y >= 0) ? 1 : -1;
	if (x != 0)
	{
		if (dx == -1)
			ddPrintf("\x1b[%dD", ddMath_abs(x));
		else
			ddPrintf("\x1b[%dC", x);
	}
	if (y != 0)
	{
		if (dy == -1)
			ddPrintf("\x1b[%dA", ddMath_abs(y));
		else
			ddPrintf("\x1b[%dB", y);
	}
}
void cursor_move_vec(ddVec2 v)
{
	cursor_move(v.x, v.y);
}
void cursor_move_up(void)
{
	ddPrint_cstring("\x1b[A");
	g_cursorPosition.y++;
}
void cursor_move_down(void)
{
	ddPrint_cstring("\x1b[B");
	g_cursorPosition.y--;
}
void cursor_move_left(void)
{
	ddPrint_cstring("\x1b[D");
	g_cursorPosition.x--;
}
void cursor_move_right(void)
{
	ddPrint_cstring("\x1b[C");
	g_cursorPosition.x++;
}
void cursor_return(void)
{
	ddPrint_cstring("\r");
	g_cursorPosition.x = 0;
}
void cursor_home(void)
{
	cursor_move_to(0, 0);
}
void cursor_delete_line(void)
{
	ddPrint_cstring("\x1b[2K");
}
bool cursor_pop(void)
{
	for (int i = __CURSOR_STACK_LENGTH - 1; i >= 0; i--)
	{
		if (!ddVec2_compare(__v2empty, __cursorPositionStack[i]))
		{
			ddVec2_set(&g_cursorPosition, __cursorPositionStack[i]);
			ddVec2_set(&__cursorPositionStack[i], __v2empty);
			cursor_move_to(g_cursorPosition.x-1, g_cursorPosition.y-1);
			return true;
		}
	}
	return false;
}
bool cursor_push(void)
{
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
	{
		if (ddVec2_compare(__v2empty, __cursorPositionStack[i]))
		{
			ddVec2_set(&__cursorPositionStack[i], g_cursorPosition);
			return true;
		}
	}
	return false;
}
void cursor_write_char(char c)
{
	ddPrint_char(c);
	g_cursorPosition.x++;
}
void cursor_write_cstring(const char* ch)
{
	ddsize _len;
	cstring_get_length(ch, &_len);
	__ddPrint(ch, _len);
	g_cursorPosition.x += _len;
}
void cursor_write_ddString(const ddString ds)
{
	ddPrint_ddString(ds);
	g_cursorPosition.x += ds.length;
}
void cursor_write_char_nl(char c)
{
	ddPrint_char_nl(c);
	g_cursorPosition.x = 0;
	g_cursorPosition.y++;
}
void cursor_write_cstring_nl(const char* ch)
{
	ddsize _len;
	cstring_get_length(ch, &_len);
	__ddPrint(ch, _len);
	ddPrint_nl();
	g_cursorPosition.y++;
	g_cursorPosition.x = 0;
}
void cursor_write_ddString_nl(const ddString ds)
{
	ddPrint_ddString(ds);
	ddPrint_nl();
	g_cursorPosition.y++;
	g_cursorPosition.x = 0;
}
void cursor_clear(void)
{
	cursor_move_to(g_consoleWidth, g_consoleHeight);
	cursor_set_bg_color(g_cursorBGColor);
	ddPrint_cstring("\x1b[1J");
	ddPrint_cstring("\x1b[0;0H");
	g_cursorPosition.x = 0;
	g_cursorPosition.y = 0;
}


void cursor_set_fg_color_rgb(int r, int g, int b)
{
	if (r < 0 && g < 0 && b < 0)
		return;
	g_cursorFGColor = make_ddColor(r, g, b);
	ddFColor dfc = make_ddFColor(r, g, b);
	ddPrint_ddString(dfc.color);
	raze_ddFColor(&dfc);
}
void cursor_set_fg_color(ddColor dc)
{
	 cursor_set_fg_color_rgb(dc.r, dc.g, dc.b);
}

void cursor_set_bg_color_rgb(int r, int g, int b)
{
	if (r < 0 && g < 0 && b < 0)
		return;
	g_cursorBGColor = make_ddColor(r, g, b);
	ddBColor dbc = make_ddBColor(r, g, b);
	ddPrint_ddString(dbc.color);
	raze_ddBColor(&dbc);
}
void cursor_set_bg_color(ddColor dc)
{
	cursor_set_bg_color_rgb(dc.r, dc.g, dc.b);
}
bool cursor_color_pop(void)
{
	for (int i = __CURSOR_STACK_LENGTH - 1; i >= 0; i--)
	{
		if (__cursorFGStack[i].g != 420)
		{
			cursor_set_fg_color(__cursorFGStack[i]);
			cursor_set_bg_color(__cursorBGStack[i]);
			__cursorFGStack[i].g = 420;
			__cursorBGStack[i].g = 420;
			return true;
		}
	}
	return false;
}
bool cursor_color_push(void)
{
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
	{
		if (__cursorFGStack[i].g == 420)
		{
			__cursorFGStack[i] = g_cursorFGColor;
			__cursorBGStack[i] = g_cursorBGColor;
			return true;
		}
	}
	return false;
}


#endif
