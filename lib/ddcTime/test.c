#include "ddcTime.h"
#include <ddcString.h>
#include <ddcPrint.h>
#include <string.h>

int main(void)
{
	ddTimerStart();
	for (int i = 0; i < 1000000; i++)
	{
		ddString v = make_ddString("OMGOGMMGOG");
		raze_ddString(&v);
	}
	dblPrint(ddTimerStop());
	chPrintL("");
	return 0;
}
