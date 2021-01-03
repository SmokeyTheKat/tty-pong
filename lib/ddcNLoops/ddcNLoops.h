#ifndef __ddcNLoops__
#define __ddcNLoops__

#include <ddcDef.h>
#include <math.h>

typedef struct ddNLoop ddNLoop;

struct ddNLoop
{
	ddsize loops;
	ddsize totalLoops;
	ddsize* loopLengths;
	ddsize* itrs;
};



ddNLoop init_ddNLoop(ddsize* _ll, ddsize _loops);
void update_ddNLoop(ddNLoop _dnl, ddsize _i);
void raze_ddNLoop(ddNLoop _dnl);

ddsize _getPeak(ddsize* xx, ddsize i);
void _getItrs(ddsize v, ddsize* xx, ddsize b, ddsize y, ddsize i, ddsize* o);



ddNLoop init_ddNLoop(ddsize* _ll, ddsize _l)
{
	ddNLoop _o;
	_o.loops = _l;
	_o.loopLengths = _ll;
	_o.totalLoops = 1;
	for (ddsize i = 0; i < _l; i++)
		_o.totalLoops *= _ll[i];
	_o.itrs = make(ddsize, _l);
	for (ddsize i = 0; i < _l; i++)
		_o.itrs[i] = 0;
	return _o;
}
void raze_ddNLoop(ddNLoop _dnl)
{
	raze(_dnl.itrs);
	raze(_dnl.loopLengths);
}
void update_ddNLoop(ddNLoop _dnl, ddsize _i)
{
	_getItrs(_i, _dnl.loopLengths, 0, _i, _dnl.loops, _dnl.itrs);
}









ddsize _getPeak(ddsize* xx, ddsize i)
{
	if (i-1 <= 1)
		return xx[0];
	int _t = 1;
	for (ddsize j = 1; j < i; j++)
		_t *= xx[j];
	return _t;
}
void _getItrs(ddsize v, ddsize* xx, ddsize b, ddsize y, ddsize i, ddsize* o)
{
	if (i == 1)  b = y;
	else         b = floor(y/(_getPeak(xx, i)));

	o[i-1] = b;
	y = y - (b*(_getPeak(xx, i)));
	i -= 1;
	if (i < 1)  return;
	_getItrs(v, xx, b, y, i, o);
}



#endif
