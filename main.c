#include "shell.h"

/**
 * main - entry point ok ok
 *addline
 * @bc: arg count unders
 * @uur: arg vector unders
 *
 * Return: 0 on success, 1 on error under
 *add
 */
int main(int bc, char **uur)
{
	info_t infoo[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (bc == 2)
	{
		fd = open(uur[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_azeeputs(uur[0]);
				_azeeputs(": 0: Can't open ");
				_azeeputs(uur[1]);
				_azeeputchar('\n');
				_azeeputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infoo->readfd = fd;
	}
	azepopulate_env_list(infoo);
	azeread_history(infoo);
	hsh(infoo, uur);
	return (EXIT_SUCCESS);
}
