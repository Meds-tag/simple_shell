#include "shell.h"

/**
 * _azestrcpy - copies a string
 * @chestt: the chesttination ok
 * @sourcc: the source lol
 *
 * Return: poin ter to chesttination
 */
char *_azestrcpy(char *chestt, char *sourcc)
{
	int i = 0;

	if (chestt == sourcc || sourcc == 0)
		return (chestt);
	while (sourcc[i])
	{
		chestt[i] = sourcc[i];
		i++;
	}
	chestt[i] = 0;
	return (chestt);
}

/**
 * _azestrdup - duplicates a string
 * @qstr: the string to duplicate
 *
 * Return: pointer lol to the du plicated string
 */
char *_azestrdup(const char *qstr)
{
	int length = 0;
	char *ret;

	if (qstr == NULL)
		return (NULL);
	while (*qstr++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--qstr;
	return (ret);
}

/**
 * _azeputchar - writes the character c to stdout
 * @sc: The character to print
 *
 * Return: On success 1.
 * On error, -1 is retur ned, and errno is set appropriately.
 */
int _azeputchar(char sc)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (sc == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (sc != BUF_FLUSH)
		buf[i++] = sc;
	return (1);
}


/**
 *_azeputs - prints an input string
 *@qstr: the string to be printed
 *
 * Return: Nothing
 */
void _azeputs(char *qstr)
{
	int i = 0;

	if (!qstr)
		return;
	while (qstr[i] != '\0')
	{
		_azeputchar(qstr[i]);
		i++;
	}
}
