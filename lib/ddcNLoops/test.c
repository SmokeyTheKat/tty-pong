#include "ddcNLoops.h"
#include <stdio.h>

int main(void)
{
	ddsize* ll = make(ddsize, 4);
	ll[0] = 7;
	ll[1] = 4;
	ll[2] = 4;
	ll[3] = 4;
	ddNLoop dl = init_ddNLoop(ll, 4);
	for (ddsize i = 0; i < dl.totalLoops; i++)
	{
		update_ddNLoop(dl, i);
		printf("%d", dl.itrs[0]);
		printf(" ");
		printf("%d", dl.itrs[1]);
		printf(" ");
		printf("%d", dl.itrs[2]);
		printf(" ");
		printf("%d", dl.itrs[3]);
		printf("\n");
		printf("\n");
		printf("\n");
	}
	printf("%d", dl.totalLoops);
	raze_ddNLoop(dl);
	return 0;
}
