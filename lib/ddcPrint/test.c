#include <ddcString.h>
#include <ddcDef.h>
#include "ddcPrint.h"

#if __x86_64__
#define __TEST__ "64"
#else
#define __TEST__ "32"
#endif

int main(ddsize agsc, char** ags)
{
	ddPrint_cstring_nl("YO");
	ddPrintf("%c%d%s", 'a', 52, " is blue");
	return 0;
}
