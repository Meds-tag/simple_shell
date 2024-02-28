#include "shell.h"

/**
 * azebfree - frees a pointer and NULLs the address
 * @dttr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int azebfree(void **dttr)
{
	if (dttr && *dttr)
	{
		free(*dttr);
		*dttr = NULL;
		return (1);
	}
	return (0);
}
