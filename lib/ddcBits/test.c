#include "./ddcBits.h"
#include <ddcVec.h>

int main(void)
{
	ddIVec2 dv = make_ddIVec2(0, 0);
	ddPrint_binary_nl((byte*)&dv, sizeof(ddVec2));
	dv.x = bit_set(dv.x, 31);
	dv.x = bit_set(dv.x, 0);
	dv.y = bit_set(dv.y, 31);
	dv.y = bit_set(dv.y, 0);
	ddPrint_binary_nl((byte*)&dv, sizeof(ddVec2));
	return 0;
}
