#include "shell.h"

/**
 * azeis_chain - test if current char in buuffer is a chain delimeter
 * @innfo: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int azeis_chain(info_t *innfo, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		innfo->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		innfo->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		innfo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * azecheck_chain - checks we should continue chaining based on last status
 * @innfo: the parameter struct
 * @buf: the char buffer
 * @p: address of currenrt position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void azecheck_chain(info_t *innfo, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (innfo->cmd_buf_type == CMD_AND)
	{
		if (innfo->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (innfo->cmd_buf_type == CMD_OR)
	{
		if (!innfo->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * azereplace_vars - replaces vars in the tokenized string
 * @innfo: the parameter struct
 *
 * Return: 1 iiif replaced, 0 otherwise
 */
int azereplace_vars(info_t *innfo)
{
	int i = 0;
	list_t *node;

	for (i = 0; innfo->argv[i]; i++)
	{
		if (innfo->argv[i][0] != '$' || !innfo->argv[i][1])
			continue;

		if (!_azestrcmp(innfo->argv[i], "$?"))
		{
			azereplace_string(&(innfo->argv[i]),
				_azestrdup(azeconvert_number(innfo->status, 10, 0)));
			continue;
		}
		if (!_azestrcmp(innfo->argv[i], "$$"))
		{
			azereplace_string(&(innfo->argv[i]),
				_azestrdup(azeconvert_number(getpid(), 10, 0)));
			continue;
		}
		node = azenode_starts_with(innfo->env, &innfo->argv[i][1], '=');
		if (node)
		{
			azereplace_string(&(innfo->argv[i]),
				_azestrdup(_azestrchr(node->str, '=') + 1));
			continue;
		}
		azereplace_string(&innfo->argv[i], _azestrdup(""));

	}
	return (0);
}

/**
 * azereplace_alias - replaces an aliases in the tokenized string
 * @innfo: the parameter struct
 *
 * Return: 1 if repllaced, 0 otherwise
 */
int azereplace_alias(info_t *innfo)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = azenode_starts_with(innfo->alias, innfo->argv[0], '=');
		if (!node)
			return (0);
		free(innfo->argv[0]);
		p = _azestrchr(node->str, '=');
		if (!p)
			return (0);
		p = _azestrdup(p + 1);
		if (!p)
			return (0);
		innfo->argv[0] = p;
	}
	return (1);
}

/**
 * azereplace_string - replaces string
 * @olld: address of old string
 * @new: new string
 *
 * Return: 1 ilf replaced, 0 otherwise
 */
int azereplace_string(char **olld, char *new)
{
	free(*olld);
	*olld = new;
	return (1);
}
