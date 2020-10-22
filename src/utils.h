#ifndef __utils__
#define __utils__

#include "letters.h"




void exit_game(int _c)
{
	cursor_clear();
	exit(0);
}


void draw_borders(void)
{
	cursor_colorPush();
	cursor_setFGColorRGB(255,255,255);
	ddVec2 p1 = make_ddVec2(23,9);
	ddVec2 p2 = make_ddVec2(170-24,47-3);

	draw_thick_line_points(make_ddVec2(p1.x,p1.y),
				make_ddVec2(p2.x,p1.y),
				cset_block);

	draw_thick_line_points(make_ddVec2(p1.x,p1.y),
				make_ddVec2(p1.x,p2.y),
				cset_block);
	draw_thick_line_points(make_ddVec2(p1.x-1,p1.y),
				make_ddVec2(p1.x-1,p2.y),
				cset_block);

	draw_thick_line_points(make_ddVec2(p2.x,p2.y),
				make_ddVec2(p1.x,p2.y),
				cset_block);

	draw_thick_line_points(make_ddVec2(p2.x,p2.y),
				make_ddVec2(p2.x,p1.y),
				cset_block);
	draw_thick_line_points(make_ddVec2(p2.x+1,p2.y),
				make_ddVec2(p2.x+1,p1.y),
				cset_block);


	cursor_colorPop();

}

void draw_title(int _c)
{
	cursor_colorPush();
	ddVec2 s = make_ddVec2(73,1);
	cursor_setFGColorRGB(0,0,255);
	draw_letter_p(s);
	s.x+=5;
	cursor_setFGColorRGB(0,255,255);
	draw_letter_o(s);
	s.x+=8;
	cursor_setFGColorRGB(0,255,0);
	draw_letter_n(s);
	s.x+=7;
	cursor_setFGColorRGB(255,255,0);
	draw_letter_g(s);
	s.x+=5;
	cursor_setFGColorRGB(255,0,0);
	cursor_colorPop();
}




#endif
