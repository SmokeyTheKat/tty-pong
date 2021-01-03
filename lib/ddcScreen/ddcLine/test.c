#include <stdio.h>
#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include "ddcLine.h"
#include <ddcVec.h>
#include <stdio.h>
#include <ddcCharSets.h>

MAINF__
{
	init_cursor();
	cursor_clear();

	ddsize len = 1000;

	ddVec2 p1 = make_ddVec2(0,0);
	ddVec2 p2 = make_ddVec2(82,32);


	double* timea = make(double, len);


	for (ddsize i = 0; i < len; i++)
	{
		ddTimer_start();
		draw_thin_line(make_ddLine(p1,p2), cset_block);
		timea[i] = ddTimer_stop();
	}

	double time = 0;
	for (ddsize i = 0; i < len; i++)
		time += timea[i];
	time /= len;
	cursor_move_to(0,37);
	ddPrint_double(time);

	
	sleep(2);


	p1.x+=15;
	p2.x+=15;
	time = 0;

	for (ddsize i = 0; i < len; i++)
	{
		ddTimer_start();
		dl2(make_ddLine(p1,p2), cset_block);
		timea[i] = ddTimer_stop();
	}
	for (ddsize i = 0; i < len; i++)
		time += timea[i];
	time /= len;
	cursor_move_to(0,38);
	ddPrint_double(time);


	raze(timea);


	cursor_move_to(0, 40);


	return 0;
}
