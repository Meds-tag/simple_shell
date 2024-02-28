#include "shell.h"

/**
 * _azerealloc - reallocates a block of memory
 * @dttr: pointer to previous malloc'ated block
 * @gold_size: byte size of previous block
 * @bold_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_azerealloc(void *dttr, unsigned int gold_size, unsigned int bold_size)
{
	char *p;

	if (!dttr)
		return (malloc(bold_size));
	if (!bold_size)
		return (free(dttr), NULL);
	if (bold_size == gold_size)
		return (dttr);

	p = malloc(bold_size);
	if (!p)
		return (NULL);

	gold_size = gold_size < bold_size ? gold_size : bold_size;
	while (gold_size--)
		p[gold_size] = ((char *)dttr)[gold_size];
	free(dttr);
	return (p);
}

/**
 **_azememset - fills memory with a constant byte
 *@ss: the pointer to the memory area
 *@bb: the byte to fill *s with
 *@nn: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_azememset(char *ss, char bb, unsigned int nn)
{
	unsigned int i;

	for (i = 0; i < nn; i++)
		ss[i] = bb;
	return (ss);
}

/**
 * azeffree - frees a string of strings
 * @pop: string of strings
 */
void azeffree(char **pop)
{
	char **a = pop;

	if (!pop)
		return;
	while (*pop)
		free(*pop++);
	free(a);
}
