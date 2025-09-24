#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stack_overflow()
{
	printf("stack overflow running!\r\n");
	char name[1024];
	snprintf(name, sizeof(name), "I'm Dao Chau Nghia");
	stack_overflow();
}

void memory_leak()
{
	printf("memory leak running!\r\n");
	char *ptr = (char *)malloc(sizeof(char) * 200 * 1024);
	printf("malloc using without free\r\n");
}

void out_of_memory()
{
	printf("out of memory running!\r\n");
	memory_leak();
	out_of_memory();
}

void main(int arg_count, char *arg[])
{
	if (2 != arg_count)
	{
		printf("using format: %s [stack_overflow|memory_leak|out_of_memory]\r\n", arg[0]);
		return;
	}

	if (0 == strcmp(arg[1], "stack_overflow"))
	{
		stack_overflow();
	}
	else if (0 == strcmp(arg[1], "memory_leak"))
	{
		memory_leak();
	}
	else if (0 == strcmp(arg[1], "out_of_memory"))
	{
		out_of_memory();
	}
}
