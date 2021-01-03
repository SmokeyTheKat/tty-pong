#ifndef __ddcFile__
#define __ddcFile__

#include <ddcString.h>
#include <ddcPrint.h>

void readf(const char* name)
{
/*
	int o;
	int i = 2;
	__asm__(".intel_syntax;"
		"mov %%eax, %1;"
		"add %%eax, 2;"
		"mov %0, %%eax;"
		".att_syntax;"
		:"=r"(o)
		:"r"(i)
		:"eax");
	ddPrint_int_nl(o);
*/
	unsigned long long int len = 8;
	char* v = malloc(len*sizeof(char));
	__asm__(".intel_syntax;"
		"mov %%rax, 2;"
		"mov %%rdi, %1;"
		"mov %%rsi, 0;"
		"mov %%rdx, 0;"
		"syscall;"
		"push %%rax;"
		"mov %%rdi, %%rax;"
		"mov %%rax, 0;"
		//"mov %%rsi, %0;"
		"mov %%rdx, %2;"
		"syscall;"
		"mov %%rax, 3;"
		"pop %%rdi;"
		"syscall;"
		".att_syntax;"
		:"=r"(v)
		:"r"("file.txt\0"), "r"(len)
		:"rax", "rdx", "rsi", "rdi");
	ddPrint_cstring(v);
	//free(v);
}



#endif
