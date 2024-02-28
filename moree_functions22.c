#include "shell.h"

/**
 * _azeerratoi - converts a string to an integer
 * @cs: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _azeerratoi(char *cs)
{
	int i = 0;
	unsigned long int result = 0;

	if (*cs == '+')
		cs++;  /* TODO: why does this make main return 255? */
	for (i = 0;  cs[i] != '\0'; i++)
	{
		if (cs[i] >= '0' && cs[i] <= '9')
		{
			result *= 10;
			result += (cs[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * azeprint_d - function prints a decimal (integer) number (bass 10)
 * @inpuget: the inpuget
 * @ffd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int azeprint_d(int inpuget, int ffd)
{
	int (*__azeputchar)(char) = _azeputchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (ffd == STDERR_FILENO)
		__azeputchar = _azeeputchar;
	if (inpuget < 0)
	{
		_abs_ = -inpuget;
		__azeputchar('-');
		count++;
	}
	else
		_abs_ = inpuget;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__azeputchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__azeputchar('0' + current);
	count++;

	return (count);
}

/**
 * azeprint_error - prints an error message
 * @nfo: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void azeprint_error(info_t *nfo, char *estr)
{
	_azeeputs(nfo->fname);
	_azeeputs(": ");
	azeprint_d(nfo->line_count, STDERR_FILENO);
	_azeeputs(": ");
	_azeeputs(nfo->argv[0]);
	_azeeputs(": ");
	_azeeputs(estr);
}

/**
 * azeconvert_number - converter function, a clone of itoa
 * @numr: number
 * @bass: bass
 * @rayat: argument rayat
 *
 * Return: string
 */
char *azeconvert_number(long int numr, int bass, int rayat)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numr;

	if (!(rayat & CONVERT_UNSIGNED) && numr < 0)
	{
		n = -numr;
		sign = '-';

	}
	array = rayat & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % bass];
		n /= bass;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * azeremove_comments - function replaces first instance of '#' with '\0'
 * @bunf: address of the string to modify
 *
 * Return: Always 0;
 */
void azeremove_comments(char *bunf)
{
	int i;

	for (i = 0; bunf[i] != '\0'; i++)
		if (bunf[i] == '#' && (!i || bunf[i - 1] == ' '))
		{
			bunf[i] = '\0';
			break;
		}
}
