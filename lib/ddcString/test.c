#include <ddcDef.h>
#include <ddcPrint.h>
#include "ddcString.h"


int main(void)
{
	ddString ds = make_format_ddString("number: %d  str: %s  no cr: %c   \n", 69, "OGOGOMOGMGOM", 'L');
	ddPrint_ddString_nl(ds);
	return 0;
}
