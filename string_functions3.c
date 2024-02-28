#include "shell.h"

/**
 **_azestrncpy - copies a string
 *@chestt: the chesttination string to be copied to
 *@sourcc: the source string
 *@qn: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_azestrncpy(char *chestt, char *sourcc, int qn)
{
	int i, j;
	char *s = chestt;

	i = 0;
	while (sourcc[i] != '\0' && i < qn - 1)
	{
		chestt[i] = sourcc[i];
		i++;
	}
	if (i < qn)
	{
		j = i;
		while (j < qn)
		{
			chestt[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_azestrchr - locates a character in a string
 *@qs: the string to be parsed
 *@qc: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_azestrchr(char *qs, char qc)
{
	do {
		if (*qs == qc)
			return (qs);
	} while (*qs++ != '\0');

	return (NULL);
}

/**
 **_azestrncat - concatenates two strings
 *@chestt: the first string
 *@sourcc: the second string
 *@qn: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_azestrncat(char *chestt, char *sourcc, int qn)
{
	int i, j;
	char *s = chestt;

	i = 0;
	j = 0;
	while (chestt[i] != '\0')
		i++;
	while (sourcc[j] != '\0' && j < qn)
	{
		chestt[i] = sourcc[j];
		i++;
		j++;
	}
	if (j < qn)
		chestt[i] = '\0';
	return (s);
}
