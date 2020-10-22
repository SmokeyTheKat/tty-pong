#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include <ddcApplication.h>
#include <ddcCursor.h>
#include <ddcKeyboard.h>
#include <ddcCharSets.h>
#include <time.h>
#include <pthread.h> 
#include <stdlib.h> 
#include "utils.h"

const int g_xpadding = 24;
const int g_ypadding = 10;
const int g_xsize    = 170-g_xpadding;
const int g_ysize    = 47-g_ypadding;

typedef struct bar bar;
struct bar
{
	ddVec2 pos;
	ddsize len;
	ddColor color;
};
bar make_bar(ddVec2 _pos, ddsize _len, ddColor _col)
{
	bar _o;
	_o.pos = _pos;
	_o.len = _len;
	_o.color = _col;
	return _o;
}
typedef struct ball ball;
struct ball
{
	ddVec2 pos;
	ddVec2 vel;
	ddColor color;
};
ball make_ball(ddVec2 _pos, ddVec2 _vel, ddColor _col)
{
	ball _o;
	_o.pos = _pos;
	_o.vel = _vel;
	_o.color = _col;
	return _o;
}
void draw_ball(ball _b)
{
	cursor_colorPush();
	cursor_setFGColor(_b.color);
	cursor_moveTo(g_xpadding + (_b.pos.x*2),
			g_ypadding + _b.pos.y);
	cursor_chWrite(cset_block);
	cursor_chWrite(cset_block);
	cursor_colorPop();
}
void clear_ball(ball _b)
{
	cursor_colorPush();
	cursor_moveTo(g_xpadding + (_b.pos.x*2),
			g_ypadding + _b.pos.y);
	cursor_chWrite(" ");
	cursor_chWrite(" ");
	cursor_colorPop();
}
void draw_bar(bar _b)
{
	cursor_colorPush();
	cursor_setFGColor(_b.color);
	cursor_moveTo(g_xpadding + (_b.pos.x*2),
			g_ypadding + _b.pos.y);
	for (int i = 0; i < _b.len; i++)
	{
		cursor_chWrite(cset_block);
		cursor_chWrite(cset_block);
		cursor_move(-2, 1);
	}
	cursor_colorPop();
}
void clear_bar(bar _b)
{
	cursor_colorPush();
	cursor_moveTo(g_xpadding + (_b.pos.x*2),
			g_ypadding + _b.pos.y);
	for (int i = 0; i < _b.len; i++)
	{
		cursor_chWrite(" ");
		cursor_chWrite(" ");
		cursor_move(-2, 1);
	}
	cursor_colorPop();
}

bool g_gameRunning;
ddKeyInfo g_cinput;

void* game_getinput(void* _v)
{
	for(;;)
	{
		g_cinput = ddKey_getch();
		if (g_cinput == DDK_p) g_cinput = !g_cinput;
	}
}

ddVec2 ball_next(ball _b)
{
	return make_ddVec2(_b.pos.x+_b.vel.x, _b.pos.y+_b.vel.y);
}
void draw_cline(void)
{
	cursor_moveTo((g_xsize+20)/2, g_ypadding);
	for (int i = 0; i < g_ysize-2; i++)
	{
		cursor_chWrite(cset_block);
		cursor_move(-1,1);
	}
}
void ball_move(ball* _b, bar _br1, bar _br2)
{
	ddVec2 bn = ball_next(*_b);
	if (bn.x > 0 && bn.x*2 < g_xsize-g_xpadding-2)
		_b->pos.x += _b->vel.x;
	else
	{
		if (bn.x <= 0)
		{
			_b->pos.x = 0;
		}
		else if (bn.x*2 >= g_xsize-g_xpadding-2)
		{
			_b->pos.x = (int)((g_xsize-g_xpadding)/2)-1;

		}
		_b->vel.x *= -1;
	}
	if (bn.y > 0 && bn.y <  g_ysize-4)
		_b->pos.y += _b->vel.y;
	else
	{
		if (bn.y <= 0)
		{
			_b->pos.y = 0;
		}
		else if (bn.y >= g_ysize-4)
		{
			_b->pos.y = g_ysize-4;

		}
		_b->vel.y *= -1;
	}
	if (_b->pos.y >= _br1.pos.y && _b->pos.y <= _br1.pos.y+_br1.len &&
		_b->pos.x == _br1.pos.x)
	{
		_b->vel.x *= -1;
		_b->pos.x += _b->vel.x;
		_b->pos.x += _b->vel.x;
	}
}
void ball_collide(ball* _b)
{
}

void main_game(int _c)
{
	pthread_t getkeys;
	pthread_create(&getkeys, null, game_getinput, null);

	cursor_clear();
	draw_title(2);
	draw_borders();

	bar player = make_bar(make_ddVec2(2,2), 6, make_ddColor(255,255,255));
	ball pong = make_ball(make_ddVec2(30,15), make_ddVec2(1,1), make_ddColor(255,255,255));
	draw_ball(pong);
	draw_bar(player);
	cursor_home();
	for(;;)
	{
		clear_ball(pong);
		ball_move(&pong, player, player);
		draw_ball(pong);
		draw_cline();
		if (g_cinput == DDK_UP && player.pos.y-2 >= 0)
		{
			clear_bar(player);
			player.pos.y--;
			player.pos.y--;
			draw_bar(player);
			g_cinput = null;
			cursor_home();
		}
		else if (g_cinput == DDK_DOWN && player.pos.y+player.len+4 <= g_ysize)
		{
			clear_bar(player);
			player.pos.y++;
			player.pos.y++;
			draw_bar(player);
			g_cinput = null;
			cursor_home();
		}
		usleep(50000);
	}
}


int main(void)
{
	init_cursor();
	cursor_clear();

	ddApplication v_da = init_ddApplication(make_constant_ddString("Pong"), make_ddColor(255,255,255), make_ddColor(0,0,0));

	ddSelect ds = make_ddSelect(make_ddVec2(70,12),
				      make_ddVec2(30,20),
				      make_dft_ddText(make_constant_ddString("PONG")),
				      make_ddColor(0,0,255), 5, make_ddColor(0,100,55));

	ddSelect_addOption(&ds, make_dft_ddText(make_ddString("Play")), main_game);
	ddSelect_addOption(&ds, make_dft_ddText(make_ddString("Exit")), exit_game);

	ddGArray_push(&(v_da.drawStack), ds);
	v_da.drawStackElems[0] = DDAE_DDSELECT;
	ddGArray_push(&(v_da.drawStack), draw_title);
	v_da.drawStackElems[1] = DDAE_GRAPHICSFUNCTION;

	run_ddApplication(&v_da);

	exit_ddApplication(&v_da);
	
	return 0;
}
