#include "shell.h"

/**
 * azeinteractive - returns true if shell is interactive mode
 * @nfo: struct address
 *olo
 * Return: 1 if interactive mode, 0 otherwise
 */
int azeinteractive(info_t *nfo)
{
	return (isatty(STDIN_FILENO) && nfo->readfd <= 2);
}

/**
 * azeis_delim - checks if character is a delimeter
 * @r: the char to check
 * @elim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int azeis_delim(char r, char *elim)
{
	while (*elim)
		if (*elim++ == r)
			return (1);
	return (0);
}

/**
 *_azeisalpha - checks for alphabetic character
 *@cc: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _azeisalpha(int cc)
{
	if ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_azeatoi - converts a string to an integer
 *@cs: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _azeatoi(char *cs)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (cs[i] == '-')
			sign *= -1;

		if (cs[i] >= '0' && cs[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (cs[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
