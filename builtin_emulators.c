#include "shell.h"

/**
 * _azemycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _azemycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_azeputs("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _azegetenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _azegetenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_azestrcmp(info->argv[1], "-") == 0)
	{
		if (!_azegetenv(info, "OLDPWD="))
		{
			_azeputs(s);
			_azeputchar('\n');
			return (1);
		}
		_azeputs(_azegetenv(info, "OLDPWD=")), _azeputchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _azegetenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		azeprint_error(info, "can't cd to ");
		_azeeputs(info->argv[1]), _azeeputchar('\n');
	}
	else
	{
		_azesetenv(info, "OLDPWD", _azegetenv(info, "PWD="));
		_azesetenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _azemyexit - exits the shell
 * @info: Structure ccontaining potential arguments. Used to maintain
 *          constant function pprototype.
 *  Return: exits wiith a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _azemyexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _azeerratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			azeprint_error(info, "Illegal number: ");
			_azeeputs(info->argv[1]);
			_azeeputchar('\n');
			return (1);
		}
		info->err_num = _azeerratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _azemyhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _azemyhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_azeputs("help call works. Function not yet implemented \n");
	if (0)
		_azeputs(*arg_array); /* temp att_unused workaround */
	return (0);
}
