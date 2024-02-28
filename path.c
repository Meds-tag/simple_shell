#include "shell.h"

/**
 * azeis_cmd - determines if a file is an executable command
 * @zinfo: the info struct
 * @apath: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int azeis_cmd(info_t *zinfo, char *apath)
{
	struct stat st;

	(void)zinfo;
	if (!apath || stat(apath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * azefind_path - finds this cmd in the PATH string
 * @winfo: the info struct
 * @patstring: the PATH string
 * @acmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *azefind_path(info_t *winfo, char *patstring, char *acmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!patstring)
		return (NULL);
	if ((_azestrlen(acmd) > 2) && azestarts_with(acmd, "./"))
	{
		if (azeis_cmd(winfo, acmd))
			return (acmd);
	}
	while (1)
	{
		if (!patstring[i] || patstring[i] == ':')
		{
			path = azedup_chars(patstring, curr_pos, i);
			if (!*path)
				_azestrcat(path, acmd);
			else
			{
				_azestrcat(path, "/");
				_azestrcat(path, acmd);
			}
			if (azeis_cmd(winfo, path))
				return (path);
			if (!patstring[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * azedup_chars - duplicates characters
 * @patstring: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *azedup_chars(char *patstring, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (patstring[i] != ':')
			buf[k++] = patstring[i];
	buf[k] = 0;
	return (buf);
}
