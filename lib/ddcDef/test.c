#include <ddcArguments.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include <stdio.h>
#include "ddcDef.h"

int v = 0;

MAINF__
{
	SET_DDARGS__;
	int v;
	run
	oBLOCK
		if (ddArgs_has_cstring(da, "yo"))
		{
			leave(1);
		}
		if (ddArgs_has_cstring(da, "bro"))
		{
			leave(2);
		}
		leave(3);
	cBLOCK
	end(1)
	{
		ddPrint_cstring_nl("yoyoyoyoyoyoyoyoyoyoyo");
	}
	end(2)
	{
		ddPrint_cstring_nl("whats up brooo");
	}
	end(3)
	{
		ddPrint_cstring_nl("YOU GONNA SAY SOMETHING BRO!?!");
	}
	return 0;
}
