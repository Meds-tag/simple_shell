#include "shell.h"

/**
 * _azeeputchar - writes the charactter c to stderr
 *added line
 * @cc: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _azeeputchar(char cc)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cc == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (cc != BUF_FLUSH)
		buf[i++] = cc;
	return (1);
}

/**
 *_azeeputs - prints an inpput string
 * @sttr: the string to be printed
 *
 * Return: Nothing
 */
void _azeeputs(char *sttr)
{
	int i = 0;

	if (!sttr)
		return;
	while (sttr[i] != '\0')
	{
		_azeeputchar(sttr[i]);
		i++;
	}
}

/**
 * _azeputfd - writes the character c to given fd
 * @c: The character to print
 * @ffd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _azeputfd(char c, int ffd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(ffd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_azeputsfd - prints an input string
 * @sttr: the string to be printed
 * @ffd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _azeputsfd(char *sttr, int ffd)
{
	int i = 0;

	if (!sttr)
		return (0);
	while (*sttr)
	{
		i += _azeputfd(*sttr++, ffd);
	}
	return (i);
}
