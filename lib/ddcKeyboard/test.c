#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include "ddcKeyboard.h"

MAINF__
{
	//ddPrint_int_nl(ddKey_getch());
	for (;;)
	{
		char key = ddKey_getch_noesc();
		if (key == DDK_BACKSPACE)
			ddPrint_cstring_nl("BACKSPACE");
		else
			ddPrint_int_nl(key);
	}

	return 0;
}
