#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include <ddcCharSets.h>
#include "ddcShapes.h"

MAINF__
{
	init_cursor();
	cursorBGColor = make_ddColor(200, 0, 200);
	cursor_clear();
	

	int gv = 255;
	cursor_setBColorRGB(0,0,0);
	ddSquare dsq = make_ddSquare(make_ddVec2(67, 11), make_ddVec2(40,20));
	draw_ddSquare(dsq, " ");


	cursor_setBColorRGB(255, 255, 0);
	dsq = make_ddSquare(make_ddVec2(1, 1), make_ddVec2(10,5));
	//draw_ddSquare(dsq, " ");


	cursor_setBColorRGB(gv,gv,gv);
	dsq = make_ddSquare(make_ddVec2(65, 10), make_ddVec2(40,20));
	draw_ddSquare(dsq, " ");



	cursor_setFColorRGB(0,0,0);
	cursor_setBColorRGB(255,255,255);

	dsq = make_ddSquare(make_ddVec2(65, 10), make_ddVec2(40,20));
	drawOutline_ddSquare(dsq, cset_verticalBar);

	dsq = make_ddSquare(make_ddVec2(65, 10), make_ddVec2(40,1));
	drawOutline_ddSquare(dsq, cset_horizontalBar);

	dsq = make_ddSquare(make_ddVec2(65, 29), make_ddVec2(40,1));
	drawOutline_ddSquare(dsq, cset_horizontalBar);

	cursor_moveTo(65, 10);
	cursor_chWrite(cset_upRightBar);
	cursor_moveTo(104, 10);
	cursor_chWrite(cset_upLeftBar);
	cursor_moveTo(65, 29);
	cursor_chWrite(cset_downRightBar);
	cursor_moveTo(104, 29);
	cursor_chWrite(cset_downLeftBar);


	cursor_moveTo(0,40);


	for(;;);

	cursor_moveTo(0, 47);
	
	return 0;
}
