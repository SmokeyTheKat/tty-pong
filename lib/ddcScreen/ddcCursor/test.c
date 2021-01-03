#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include <ddcVec.h>
#include "ddcCursor.h"
#include <ddcColors.h>
#include <ddcCharSets.h>

MAINF__
{

	init_cursor();
	cursor_clear();
	cursor_move_to(0, 0);
	ddPrint_cstring("0");
	cursor_move_to(1, 1);
	ddPrint_cstring("1");
	return 0;
}
