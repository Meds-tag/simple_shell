#include "shell.h"

/**
 * azeinput_buf - buffers chained commands
 * @iznfo: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t azeinput_buf(info_t *iznfo, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)iznfo->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, azesigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _azegetline(iznfo, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			iznfo->linecount_flag = 1;
			azeremove_comments(*buf);
			azebuild_history_list(iznfo, *buf, iznfo->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				iznfo->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * azeget_input - gets a line minus the newline
 * @nfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t azeget_input(info_t *nfo)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(nfo->arg), *p;

	_azeputchar(BUF_FLUSH);
	r = azeinput_buf(nfo, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		azecheck_chain(nfo, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (azeis_chain(nfo, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			nfo->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_azestrlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * azeread_buf - reads a buffer
 * @ionfo: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t azeread_buf(info_t *ionfo, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(ionfo->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _azegetline - gets the next line of input from STDIN
 * @nfo: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _azegetline(info_t *nfo, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = azeread_buf(nfo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _azestrchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _azerealloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_azestrncat(new_p, buf + i, k - i);
	else
		_azestrncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * azesigintHandler - blocks ctrl-C
 * @jig_num: the signal number
 *
 * Return: void
 */
void azesigintHandler(__attribute__((unused))int jig_num)
{
	_azeputs("\n");
	_azeputs("$ ");
	_azeputchar(BUF_FLUSH);
}
