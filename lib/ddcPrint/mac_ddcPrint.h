#ifndef __ddcPrint__
#define __ddcPrint__


#include <ddcDef.h>
#include <stdarg.h>

#include <ddcString.h>


void __ddPrint(const char* _v, const ddsize _len);
void ddPrint_cstring(const char* _ch);
void ddPrint_cstring_nl(const char* _ch);

void ddPrint_char(const char _c);
void ddPrint_char_nl(const char _c);

void ddPrint_ddString(const ddString _ds);
void ddPrint_ddString_nl(const ddString _ds);

void ddPrint_int(const int _v);
void ddPrint_int_nl(const int _v);

void ddPrint_float(const float _v);
void ddPrint_float_nl(const float _v);

void ddPrint_double(const double _v);
void ddPrint_double_nl(const double _v);

void ddPrint_nl(void);


void __ddPrint(const char* _v, const ddsize _len)
{
	long write = 0x2000004;
	long stdout = 1;
	char* str = (char*)_v;
	unsigned long len = (unsigned long)_len;
	unsigned long ret = 0;
	__asm__		(
			 "movq %1, %%rax;\n"
			 "movq %2, %%rdi;\n"
			 "movq %3, %%rsi;\n"
			 "movq %4, %%rdx;\n"
			 "syscall;\n"
			 "movq %%rax, %0;\n"
			 : "=g"(ret)
			 :"g"(write), "g"(stdout), "g"(str), "g"(len)
			 :);

}



void ddPrint_char(const char _c)
{
	__ddPrint(&_c, 1);
}

void ddPrint_char_nl(const char _c)
{
	ddPrint_char(_c);
	ddPrint_char(DNL);
}


void ddPrint_nl(void)
{
	ddPrint_char(DNL);
}

void ddPrint_int(const int _v)
{
	ddString _ds = make_ddString_from_int(_v);
	ddPrint_ddString(_ds);
	raze_ddString(&_ds);
}
void ddPrint_int_nl(const int _v)
{
	ddPrint_int(_v);
	ddPrint_nl();
}

void ddPrint_float(const float _v)
{
	ddString _ds = make_ddString_from_float(_v);
	ddPrint_ddString(_ds);
	raze_ddString(&_ds);
}
void ddPrint_float_nl(const float _v)
{
	ddPrint_float(_v);
	ddPrint_nl();
}

void ddPrint_double(const double _v)
{
	ddString _ds = make_ddString_from_float(_v);
	ddPrint_ddString(_ds);
	raze_ddString(&_ds);
}
void ddPrint_double_nl(const double _v)
{
	ddPrint_double(_v);
	ddPrint_nl();
}


void ddPrint_cstring(const char* _ch)
{
	ddsize _len;
	cstring_get_length(_ch, &_len);
	__ddPrint(_ch, _len);
}
void ddPrint_cstring_nl(const char* _ch)
{
	ddPrint_cstring(_ch);
	ddPrint_nl();
}


/*
void chPrintC(ddsize _l, ...)
{
	va_list arg;
	va_start(arg, _l);
	chPrint(va_arg(arg, const char*));
	for (ddsize i = 2; i < _l+1; i++)
		chPrint(va_arg(arg, const char*));
	va_end(arg);
}
*/

void ddPrint_ddString(const ddString _ds)
{
	__ddPrint(_ds.cstr, _ds.length);
}

/*
void dsPrintC(ddsize _l, ...)
{
	va_list arg;
	va_start(arg, _l);
	dsPrint(va_arg(arg, ddString));
	for (ddsize i = 2; i < _l+1; i++)
		dsPrint(va_arg(arg, ddString));
	va_end(arg);
}
*/

void ddPrint_ddString_nl(const ddString _ds)
{
	ddPrint_ddString(_ds);
	ddPrint_nl();
}



#endif
