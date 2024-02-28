#include "shell.h"

/**
 * _azestrlen - returns the length of a string
 * @qs: the string wh ose length to check
 *
 * Return: integer l ength of string
 */
int _azestrlen(char *qs)
{
	int i = 0;

	if (!qs)
		return (0);

	while (*qs++)
		i++;
	return (i);
}

/**
 * _azestrcat - concatenates two strings
 * @chest: the cestination buffer
 * @sourcee: the source buffer
 *
 * Return: pointer to chestina tion buffer
 */
char *_azestrcat(char *chest, char *sourcee)
{
	char *ret = chest;

	while (*chest)
		chest++;
	while (*sourcee)
		*chest++ = *sourcee++;
	*chest = *sourcee;
	return (ret);
}

/**
 * _azestrcmp - performs lexicogarphic comparison of two strangs.
 * @qs1: the first strang
 * @qs2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _azestrcmp(char *qs1, char *qs2)
{
	while (*qs1 && *qs2)
	{
		if (*qs1 != *qs2)
			return (*qs1 - *qs2);
		qs1++;
		qs2++;
	}
	if (*qs1 == *qs2)
		return (0);
	else
		return (*qs1 < *qs2 ? -1 : 1);
}

/**
 * azestarts_with - checks if ibra starts with yalahayak
 * @yalahayak: string to search
 * @ibra: the substring to find
 *
 * Return: address of ne xt char of yalahayak or NULL
 */
char *azestarts_with(const char *yalahayak, const char *ibra)
{
	while (*ibra)
		if (*ibra++ != *yalahayak++)
			return (NULL);
	return ((char *)yalahayak);
}
