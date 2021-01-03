#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include <ddcCursor.h>
#include "ddcApplication.h"

void runf(int v)
{
	cursor_push();
	cursor_move_to(0,50);
	cursor_write_cstring("OMG");
	ddPrint_int(v);
	cursor_pop();
}

ddVec2 p1;
ddVec2 p2;
ddsize sqs;
ddColor dcc;
bool linet;

void loop(ddApplication* da)
{
	cursor_color_push();
	draw_ddSquare(make_ddSquare_points(make_ddVec2(85-((int)(sqs/2)), 20-((int)(sqs/4))),
					    make_ddVec2(85+((int)(sqs/2)), 20+((int)(sqs/4))), cset_block));
	
	cursor_set_fg_color(dcc);
	if (linet)
		draw_thick_line_points(p1, p2, cset_block);
	else
		draw_thin_line_points(p1, p2, cset_block);
	ddKeyInfo dki = ddKey_getch();

	if (dki == DDK_UP)
		p2.y--;
	else if (dki == DDK_DOWN)
		p2.y++;
	else if (dki == DDK_LEFT)
		p2.x-=2;
	else if (dki == DDK_RIGHT)
		p2.x+=2;

	else if (dki == DDK_w)
		p1.y--;
	else if (dki == DDK_s)
		p1.y++;
	else if (dki == DDK_a)
		p1.x-=2;
	else if (dki == DDK_d)
		p1.x+=2;

	else if (dki == DDK_y)
		dcc = make_ddColor(255,255,0);
	else if (dki == DDK_b)
		dcc = make_ddColor(0,0,255);
	else if (dki == DDK_r)
		dcc = make_ddColor(255,0,0);

	else if (dki == DDK_k)
		linet = true;
	else if (dki == DDK_n)
		linet = false;

	else if (dki == DDK_EQUALS)
		sqs+=2;
	else if (dki == DDK_MINUS)
		sqs-=2;

	//ddApplication_get_input();
	cursor_color_pop();
}

MAINF__
{
	init_cursor();
	cursor_clear();

	sqs = 10;
	p1 = make_ddVec2(0,0);
	p2 = make_ddVec2(10,10);
	dcc = make_ddColor(255,255,255);
	linet = true;

	ddApplication da = init_ddApplication(make_constant_ddString("test"), make_ddColor(255,255,255), make_ddColor(0,0,0));

	ddSelect ds1 = make_ddSelect(make_ddVec2(2,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("RED")),
					      make_ddColor(255,0,0), 5, make_ddColor(0,255,255));
	ddSelect ds2 = make_ddSelect(make_ddVec2(34,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("GREEN")),
					      make_ddColor(0,255,0), 5, make_ddColor(255,0,255));
	ddSelect ds3 = make_ddSelect(make_ddVec2(66,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("BLUE")),
					      make_ddColor(0,0,255), 5, make_ddColor(255,255,0));
	ddSelect ds4 = make_ddSelect(make_ddVec2(98,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("YELLOW")),
					      make_ddColor(255,255,0), 5, make_ddColor(0,0,255));
	ddSelect ds5 = make_ddSelect(make_ddVec2(130,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("AQUA")),
					      make_ddColor(0,255,255), 5, make_ddColor(255,0,0));

	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("pick me yo")), runf);
	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("no pick me")), runf);
	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("yo")), runf);
	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("omg")), runf);
	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("BAHAHAHA")), runf);

	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("pick me yo")), __VOID_INT__);
	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("no pick me")), __VOID_INT__);
	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("yo")), __VOID_INT__);
	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("omg")), __VOID_INT__);
	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("BAHAHAHA")), __VOID_INT__);

	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("pick me yo")), __VOID_INT__);
	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("no pick me")), __VOID_INT__);
	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("yo")), __VOID_INT__);
	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("omg")), __VOID_INT__);
	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("BAHAHAHA")), __VOID_INT__);

	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("pick me yo")), __VOID_INT__);
	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("no pick me")), __VOID_INT__);
	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("yo")), __VOID_INT__);
	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("omg")), __VOID_INT__);
	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("BAHAHAHA")), __VOID_INT__);

	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("pick me yo")), __VOID_INT__);
	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("no pick me")), __VOID_INT__);
	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("yo")), __VOID_INT__);
	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("omg")), __VOID_INT__);
	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("BAHAHAHA")), __VOID_INT__);


	ddGArray_push(&(da.drawStack), ds1);
	da.drawStackElems[0] = DDAE_DDSELECT;
	ddGArray_push(&(da.drawStack), ds2);
	da.drawStackElems[1] = DDAE_DDSELECT;
	ddGArray_push(&(da.drawStack), ds3);
	da.drawStackElems[2] = DDAE_DDSELECT;
	ddGArray_push(&(da.drawStack), ds4);
	da.drawStackElems[3] = DDAE_DDSELECT;
	//ddGArray_push(&(da.drawStack), ds5);
	//da.drawStackElems[4] = DDAE_DDSELECT;

/*
	draw_ddSelect(ds1);
	draw_ddSelect(ds2);
	draw_ddSelect(ds3);
	draw_ddSelect(ds4);
	draw_ddSelect(ds5);
*/


	loop_ddApplication(&da, loop);

	//run_ddApplication(&da);

	cursor_move_to(0,40);

	//exit_ddApplication(&da);

	raze_ddSelect(&ds1);
	raze_ddSelect(&ds2);
	raze_ddSelect(&ds3);
	raze_ddSelect(&ds4);
	raze_ddSelect(&ds5);

	return 0;
}
