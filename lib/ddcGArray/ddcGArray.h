#include <ddcDef.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include <ddcLine.h>
#include <stdio.h>

#define ddGArray_get(h, i, t) (*((t*)__ddGArray_get(h, i)))
#define ddGArray_get_pointer(h, i, t) ((t*)__ddGArray_get(h, i))
#define ddGArray_get_p(h, i, t) ((t*)__ddGArray_get(h, i))
#define ddGArray_set(h, v, i) __ddGArray_set(h, (void*)(&v), i)
#define ddGArray_push(h, v) __ddGArray_push(h, (void*)(&v))

typedef struct ddGArray ddGArray;

ddGArray make_ddGArray(ddsize _len);
void raze_ddGArray(ddGArray* _h);

bool __ddGArray_set(ddGArray* _h, void* _v, ddsize _i);
bool __ddGArray_push(ddGArray* _h, void* _v);
void* __ddGArray_get(ddGArray _h, ddsize _i);


struct ddGArray
{
	void** val;
	ddsize length;
	ddsize capacity;
};

ddGArray make_ddGArray(ddsize _len)
{
	ddGArray _o;
	_o.val = make(void, _len);
	_o.length = 0;
	_o.capacity = _len;
	return _o;
}
void raze_ddGArray(ddGArray* _h)
{
	raze(_h->val);
}
bool __ddGArray_set(ddGArray* _h, void* _v, ddsize _i)
{
	if (_i > _h->capacity)
		return false;
	_h->val[_i] = _v;
	return true;
}
bool __ddGArray_push(ddGArray* _h, void* _v)
{
	if (_h->length + 1 > _h->capacity)
		return false;
	_h->val[_h->length] = _v;
	_h->length++;
	return true;
}
void* __ddGArray_get(ddGArray _h, ddsize _i)
{
	return _h.val[_i];
}
