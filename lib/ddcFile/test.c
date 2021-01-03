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
		"mov %%rsi, %0;"
		"mov %%rdx, %2;"
		"syscall;"
		"mov %%rax, 3;"
		"pop %%rdi;"
		"syscall;"
		".att_syntax;"
		:"=r"(v)
		:"r"("/home/bxtw/Documents/Projects/ddmoCLib/ddcFile/file.txt"), "r"(len)
		:"rax", "rdx", "rsi", "rdi");
	ddPrint_cstring(v);
	//free(v);
}


extern int my_fn(int in);

__asm__(
	"my_fn:;"
	"	mov %rdi, %rax;"
	"	add $100, %rax;"
	"	ret;");

int main(void)
{
	readf("file.txt");
	//ddPrint_int_nl(my_fn(10));
	return 0;
}
