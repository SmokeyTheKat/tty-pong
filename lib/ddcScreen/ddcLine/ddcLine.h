#ifndef __ddcLine__
#define __ddcLine__

#include <ddcCursor.h>
#include <ddcString.h>
#include <ddcMath.h>
#include <ddcVec.h>
#include <ddcPrint.h>
#include <ddcCharSets.h>

#include <stdio.h>

#include <time.h>

typedef struct ddLine ddLine;

void draw_linePoints(ddVec2 p1, ddVec2 p2, const char* ch);
void draw_thin_line_points(ddVec2 p1, ddVec2 p2, const char* ch);
void draw_thick_line_points(ddVec2 p1, ddVec2 p2, const char* ch);
void draw_thick_line(ddLine dl, const char* ch);
void draw_thin_line(ddLine dl, const char* ch);
ddLine make_ddLine(ddVec2 _p1, ddVec2 _p2);


struct ddLine
{
	ddVec2 p1;
	ddVec2 p2;
};




ddLine make_ddLine(ddVec2 _p1, ddVec2 _p2)
{
	ddLine dl;
	dl.p1 = _p1;
	dl.p2 = _p2;
	return dl;
}



void draw_thick_line_points(ddVec2 p1, ddVec2 p2, const char* ch)
{
	draw_thick_line(make_ddLine(p1, p2), ch);
}
void draw_thin_line_points(ddVec2 p1, ddVec2 p2, const char* ch)
{
	draw_thin_line(make_ddLine(p1, p2), ch);
}

void draw_thick_line(ddLine dl, const char* ch)
{
	const int ci[2]     = { ddMath_abs(dl.p2.y-dl.p1.y), ddMath_abs(dl.p2.x-dl.p1.x) };
	const int td        = ci[0]+ci[1];
	const int d[2]      = {(dl.p1.x <= dl.p2.x) ? 1 : -1, (dl.p1.y <= dl.p2.y) ? 1 : -1 };
	int c[2]            = { ci[0], ci[1] };
	int po[2]           = { dl.p1.x, dl.p1.y };
	int i               = 0;
	cursor_move_to(po[0], po[1]);
	cursor_write_cstring(ch);
	switch (i < td)
	{
		case 1:
		{
			do
			{
				int v = (c[0]>c[1])+(c[0]==c[1]);
				c[v] += ci[v];
				po[v] += d[v];
				cursor_move_to(po[0], po[1]);
				cursor_write_cstring(ch);
				i++;
			} while (i < td);
		}
		case 0:	return;
	}
}

void draw_thin_line(ddLine dl, const char* ch)
{
	const int ci[2]     = { ddMath_abs(dl.p2.y-dl.p1.y), ddMath_abs(dl.p2.x-dl.p1.x) };
	const int td        = (ci[0] >= ci[1]) ? ci[0] : ci[1];
	const int d[2]      = {(dl.p1.x <= dl.p2.x) ? 1 : -1, (dl.p1.y <= dl.p2.y) ? 1 : -1 };
	int c[2]            = { ci[0], ci[1] };
	int po[2]           = { dl.p1.x, dl.p1.y };
	int i               = 0;
	cursor_move_to(po[0], po[1]);
	cursor_write_cstring(ch);
	switch (i < td)
	{
		case 1:
		{
			do
			{
				int v = (c[0]>c[1])+(c[0]==c[1]);
				c[v] += ci[v];
				po[v] += d[v];

				int z = (c[v]>c[!v]);
				c[!v] += z*ci[!v];
				po[!v] += z*d[!v];

				cursor_move_to(po[0], po[1]);
				cursor_write_cstring(ch);
				i++;
			} while (i < td);
		}
		case 0:	return;
	}
}
void dl2h(ddLine dl, const char* ch)
{
	int dx = dl.p2.x-dl.p1.x;
	int dy = dl.p2.y-dl.p1.y;
	int xi = 1;
	int i = 0;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	int D = (2*dx)-dy;
	int x = dl.p1.x;
	for (int y = dl.p1.y; y < dl.p2.y; x++)
	{
		i++;
		cursor_move_to(x, y);
		cursor_write_cstring(ch);
		if (D > 0)
		{
			x += xi;
			D += 2*(dx-dy);
		}
		else
			D += 2*dx;
	}
}
void dl2l(ddLine dl, const char* ch)
{
	int dx = dl.p2.x-dl.p1.x;
	int dy = dl.p2.y-dl.p1.y;
	int yi = 1;
	int i = 0;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	int D = (2*dy)-dx;
	int y = dl.p1.y;
	for (int x = dl.p1.x; x < dl.p2.x; x++)
	{
		i++;
		cursor_move_to(x, y);
		cursor_write_cstring(ch);
		if (D > 0)
		{
			y += yi;
			D += 2*(dy-dx);
		}
		else
			D += 2*dy;
	}
}
void dl2(ddLine dl, const char* ch)
{
	if (ddMath_abs(dl.p2.y-dl.p1.y) < ddMath_abs(dl.p2.x-dl.p1.x))
	{
		if (dl.p1.x > dl.p2.x)
		{
			float t = dl.p1.x;
			dl.p1.x = dl.p2.x;
			dl.p2.x = dl.p1.x;

			t = dl.p1.y;
			dl.p1.y = dl.p2.y;
			dl.p2.y = dl.p1.y;

			dl2l(dl, ch);
		}
		else
			dl2l(dl, ch);
	}
	else
	{
		if (dl.p1.y > dl.p2.y)
		{
			float t = dl.p1.x;
			dl.p1.x = dl.p2.x;
			dl.p2.x = dl.p1.x;

			t = dl.p1.y;
			dl.p1.y = dl.p2.y;
			dl.p2.y = dl.p1.y;

			dl2l(dl, ch);
		}
		else
			dl2l(dl, ch);
	}
}
      

#endif
