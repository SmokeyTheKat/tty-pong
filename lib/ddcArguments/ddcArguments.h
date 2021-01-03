#include "../ddcDef/ddcDef.h"
#include "../ddcString/ddcString.h"

#ifndef __ddcArguments__
#define __ddcArguments__
typedef struct ddArgs ddArgs;

ddArgs init_ddArgs(char** _ags, ddsize _agsc);
bool ddArgs_has_cstring(ddArgs _da, const char* _ch);
bool ddArgs_has_ddString(ddArgs _da, ddString _ds);
void ddArgs_get_ddString(ddArgs _da, ddString* _ds, ddsize _i);

struct ddArgs
{
	ddsize agsc;
	char** ags;
};

ddArgs init_ddArgs(char** _ags, ddsize _agsc)
{
	ddArgs _o;
	_o.ags = _ags;
	_o.agsc = _agsc;
	return _o;
}

void ddArgs_get_ddString(ddArgs _da, ddString* _ds, ddsize _i)
{
	if (_ds->status == DOS_DELETED) return;
	if (_da.agsc <= _i) return;
	remake_ddString(_ds, _da.ags[_i]);
}

bool ddArgs_has_cstring(ddArgs _da, const char* _ch)
{
	for (ddsize i = 0; i < _da.agsc; i++)
	{
		if (cstring_compare(_ch, _da.ags[i]))  return true;
	}
	return false;
}
bool ddArgs_has_ddString(ddArgs _da, ddString _ds)
{
	for (ddsize i = 0; i < _da.agsc; i++)
	{
		bool _t = true;
		for (ddsize j = 0; j < _ds.length; j++)
		{
			if (_ds.cstr[i] != _da.ags[i][j]) _t = false; break;
		}
		if (_t)  return true;
	}
	return false;
}
#endif
