#include <ddcDef.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include "ddcGArray.h"

int main(void)
{
	ddGArray h = make_ddGArray(5);


	int i = 5;
	bool b = true;

	ddString ds = make_constant_ddString("yo");


	ddGArray_push(&h, i);
	ddGArray_push(&h, b);
	ddGArray_push(&h, ds);

	if (ddGArray_get(h, 1, bool))
		ddPrint_ddString_nl(ddGArray_get(h, 2, ddString));


	
	raze_ddGArray(&h);

	return 0;
}



