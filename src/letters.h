#ifndef __letters__
#define __letters__


void draw_letter_p(ddVec2 s)
{
	draw_thick_line_points(make_ddVec2(s.x,s.y),
				make_ddVec2(s.x,s.y+4),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x,s.y),
				make_ddVec2(s.x+2,s.y),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x+2,s.y),
				make_ddVec2(s.x+2,s.y+2),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x+2,s.y+2),
				make_ddVec2(s.x,s.y+2),
				cset_block);
}
void draw_letter_o(ddVec2 s)
{
	draw_thick_line_points(make_ddVec2(s.x,s.y+1),
				make_ddVec2(s.x,s.y+3+1),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x,s.y+1),
				make_ddVec2(s.x+5,s.y+1),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x+5,s.y+3+1),
				make_ddVec2(s.x,s.y+3+1),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x+5,s.y+3+1),
				make_ddVec2(s.x+5,s.y+1),
				cset_block);
}
void draw_letter_n(ddVec2 s)
{
	draw_thick_line_points(make_ddVec2(s.x,s.y+1),
				make_ddVec2(s.x,s.y+4),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x,s.y+1),
				make_ddVec2(s.x+4,s.y+4),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x+4,s.y+4),
				make_ddVec2(s.x+4,s.y+1),
				cset_block);
}
void draw_letter_g(ddVec2 s)
{
	draw_thick_line_points(make_ddVec2(s.x,s.y+2),
				make_ddVec2(s.x,s.y+2+2),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x,s.y+2),
				make_ddVec2(s.x+4,s.y+2),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x+4,s.y+2),
				make_ddVec2(s.x+4,s.y+2+2),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x+4,s.y+2+2),
				make_ddVec2(s.x,s.y+2+2),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x+4,s.y+2+2),
				make_ddVec2(s.x+4,s.y+4+2),
				cset_block);
	draw_thick_line_points(make_ddVec2(s.x+4,s.y+4+2),
				make_ddVec2(s.x,s.y+4+2),
				cset_block);
}



#endif
