#ifndef __ddclib_ddcBits_h__
#define __ddclib_ddcBits_h__

#include <ddcDef.h>
#include <ddcPrint.h>

typedef unsigned char byte;

#define bit_get(x, p) ((x >> p) & 1)
#define bit_set(x, p) (x | (1 << p))
#define bit_unset(x, p) (x & (1 << p))
#define bit_tog(x, p) (x ^ (1 << p))
#define bit_setv(x, v, p) ((v == 1) ? bit_set(x, p) : bit_unset(x, p))

void ddPrint_binary_byte(byte b);
void ddPrint_binary(byte* b, int length);
void ddPrint_binary_byte_nl(byte b);
void ddPrint_binary_nl(byte* b, int length);

void ddPrint_binary_byte(byte b)
{
	for (int i = 7; i >= 0; i--)
		ddPrint_int(bit_get(b, i));
}
void ddPrint_binary(byte* b, int length)
{
	for (int j = length-1; j >= 0; j--)
	{
		ddPrint_binary_byte(b[j]);
		if (j != 0) ddPrint_char('-');
	}
}
void ddPrint_binary_byte_nl(byte b)
{
	ddPrint_binary_byte(b);
	ddPrint_nl();
}
void ddPrint_binary_nl(byte* b, int length)
{
	ddPrint_binary(b, length);
	ddPrint_nl();
}

#endif
