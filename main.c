#include "shell.h"

/**
 * main - entry point
 *addline
 * @bc: arg count
 * @uur: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int bc, char **uur)
{
	info_t info[] = { INFO_INIT };
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
		info->readfd = fd;
	}
	azepopulate_env_list(info);
	azeread_history(info);
	hsh(info, uur);
	return (EXIT_SUCCESS);
}
