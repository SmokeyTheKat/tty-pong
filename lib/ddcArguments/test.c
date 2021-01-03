#include "ddcArguments.h"
#include <ddcPrint.h>

int main(ddsize agsc, char** ags)
{
	ddArgs da = init_ddArgs(ags, agsc);
	ddString ds = make_ddString("yo");
	if (ddArgs_has_cstring(da, "yo"))
	{
		ddPrint_cstring_nl("it has yo");
	}
	else
	{
		ddPrint_cstring_nl("itn't has yo");
	}
	raze_ddString(&ds);
	return 0;
}
