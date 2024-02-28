#include "shell.h"

/**
 * azeget_history_file - gets the history file
 * @iznfo: parameter struct
 *
 * Return: allocated string containg history file
 */

char *azeget_history_file(info_t *iznfo)
{
	char *buf, *dir;

	dir = _azegetenv(iznfo, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_azestrlen(dir) + _azestrlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_azestrcpy(buf, dir);
	_azestrcat(buf, "/");
	_azestrcat(buf, HIST_FILE);
	return (buf);
}

/**
 * azewrite_history - creates a file, or appends to an existing file
 * @iznfo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int azewrite_history(info_t *iznfo)
{
	ssize_t fd;
	char *filename = azeget_history_file(iznfo);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = iznfo->history; node; node = node->next)
	{
		_azeputsfd(node->str, fd);
		_azeputfd('\n', fd);
	}
	_azeputfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * azeread_history - reads history from file
 * @iznfo: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int azeread_history(info_t *iznfo)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = azeget_history_file(iznfo);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			azebuild_history_list(iznfo, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		azebuild_history_list(iznfo, buf + last, linecount++);
	free(buf);
	iznfo->histcount = linecount;
	while (iznfo->histcount-- >= HIST_MAX)
		azedelete_node_at_index(&(iznfo->history), 0);
	azerenumber_history(iznfo);
	return (iznfo->histcount);
}

/**
 * azebuild_history_list - adds entry to a history linked list
 * @iznfo: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int azebuild_history_list(info_t *iznfo, char *buf, int linecount)
{
	list_t *node = NULL;

	if (iznfo->history)
		node = iznfo->history;
	azeadd_node_end(&node, buf, linecount);

	if (!iznfo->history)
		iznfo->history = node;
	return (0);
}

/**
 * azerenumber_history - renumbers the history linked list after changes
 * @iznfo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int azerenumber_history(info_t *iznfo)
{
	list_t *node = iznfo->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (iznfo->histcount = i);
}
