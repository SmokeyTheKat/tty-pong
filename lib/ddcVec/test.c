#include "ddcVec.h"
#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcDef.h>

int main(void)
{
	ddVec3 v = make_ddVec3(37, 22, 95);
	ddPrint_double_nl(ddVec3_magnitude(v));
	return 0;
}
