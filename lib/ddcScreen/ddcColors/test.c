#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include "ddcColors.h"

MAINF__
{
	SET_DDARGS__;
	if (ddArgs_has_cstring(da, "yo"))
	{
		ddPrint_cstring("yo yo yo");
	}

	ddFColor dfc = make_ddFColor(255, 255 ,0);
	ddBColor dbc = make_ddBColor(0, 0, 255);
	ddPrint_ddString(dfc.color);
	ddPrint_ddString(dbc.color);
	ddPrint_cstring_nl("YOYO");

	return 0;
}
