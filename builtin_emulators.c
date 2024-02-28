#include "shell.h"

/**
 * _azemycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _azemycd(info_t *innfo)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_azeputs("TODO: >>getcwd failure emsg here<<\n");
	if (!innfo->argv[1])
	{
		dir = _azegetenv(innfo, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _azegetenv(innfo, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_azestrcmp(innfo->argv[1], "-") == 0)
	{
		if (!_azegetenv(innfo, "OLDPWD="))
		{
			_azeputs(s);
			_azeputchar('\n');
			return (1);
		}
		_azeputs(_azegetenv(innfo, "OLDPWD=")), _azeputchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _azegetenv(innfo, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(innfo->argv[1]);
	if (chdir_ret == -1)
	{
		azeprint_error(innfo, "can't cd to ");
		_azeeputs(innfo->argv[1]), _azeeputchar('\n');
	}
	else
	{
		_azesetenv(innfo, "OLDPWD", _azegetenv(innfo, "PWD="));
		_azesetenv(innfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _azemyhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _azemyhelp(info_t *inffo)
{
	char **arg_array;

	arg_array = inffo->argv;
	_azeputs("help call works. Function not yet implemented \n");
	if (0)
		_azeputs(*arg_array); /* temp att_unused workaround */
	return (0);
}

/**
 * _azemyexit - exits the shell
 * @info: Structure ccontaining potential arguments. Used to maintain
 *          constant function pprototype.
 *  Return: exits wiith a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _azemyexit(info_t *innfo)
{
	int exitcheck;

	if (innfo->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _azeerratoi(innfo->argv[1]);
		if (exitcheck == -1)
		{
			innfo->status = 2;
			azeprint_error(innfo, "Illegal number: ");
			_azeeputs(innfo->argv[1]);
			_azeeputchar('\n');
			return (1);
		}
		innfo->err_num = _azeerratoi(innfo->argv[1]);
		return (-2);
	}
	innfo->err_num = -1;
	return (-2);
}
