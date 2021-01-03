#ifndef __ddcPrint__
#define __ddcPrint__


#include "../ddcDef/ddcDef.h"
#include <stdarg.h>

#include "../ddcString/ddcString.h"


void __ddPrint(const void* _v, const ddsize _len);
void ddPrintf(const char* _ch, ...);
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


void __ddPrint(const void* _v, const ddsize _len)
{
#if __x86_64__
	__asm__		(".intel_syntax;"
			 "mov %%rsi, %0;"
			 "mov %%rdx, %1;"
			 "mov %%rax, 1;"
			 "mov %%rdi, 0;"
			 "syscall;"
			 ".att_syntax;"
			 :
			 :"r"(_v), "r"(_len)
			 :"rsi", "rdx");
#else
	__asm__		(".intel_syntax;"
			 "mov %%esi, %0;"
			 "mov %%edx, %1;"
			 "mov %%eax, 1;"
			 "mov %%edi, 0;"
			 "syscall;"
			 ".att_syntax;"
			 :
			 :"r"(_v), "r"(_len)
			 :"esi", "edx");
#endif

}

#include <stdarg.h>
void ddPrintf(const char* _ch, ...)
{
	va_list ap;
	va_start(ap, _ch);
	ddsize _len;
	cstring_get_length(_ch, &_len);
	for (int i = 0; i < _len; i++)
	{
		switch (_ch[i])
		{
			case '%':
			{
				switch (_ch[i+1])
				{
					case 'd':
						ddPrint_int(va_arg(ap, int));
						i++;
						break;
					case 'c':
						ddPrint_char(va_arg(ap, int));
						i++;
						break;
					case 's':
						ddPrint_cstring(va_arg(ap, char*));
						i++;
						break;
				}
				break;
			}
			default: ddPrint_char(_ch[i]); break;
				
		}
	}
	va_end(ap);
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
