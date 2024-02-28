#include "shell.h"

/**
 * **azestrtow - splits a string into words. Repeat delimiters are ignored
 * @dr: the input string
 * @qd: the delimeter string
 * Return: a pointer to an arr ay of strings, or NULL on failure
 */

char **azestrtow(char *dr, char *qd)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (dr == NULL || dr[0] == 0)
		return (NULL);
	if (!qd)
		qd = " ";
	for (i = 0; dr[i] != '\0'; i++)
		if (!azeis_delim(dr[i], qd) && (azeis_delim(dr[i + 1], qd) || !dr[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (azeis_delim(dr[i], qd))
			i++;
		k = 0;
		while (!azeis_delim(dr[i + k], qd) && dr[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = dr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **azestrtow2 - splits a string into words
 * @dstr: the input string
 * @qd: the delimeter
 * Return: a  pointer to an arra y of strings, or NULL on failure
 */
char **azestrtow2(char *dstr, char qd)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (dstr == NULL || dstr[0] == 0)
		return (NULL);
	for (i = 0; dstr[i] != '\0'; i++)
		if ((dstr[i] != qd && dstr[i + 1] == qd) ||
		    (dstr[i] != qd && !dstr[i + 1]) || dstr[i + 1] == qd)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (dstr[i] == qd && dstr[i] != qd)
			i++;
		k = 0;
		while (dstr[i + k] != qd && dstr[i + k] && dstr[i + k] != qd)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = dstr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
