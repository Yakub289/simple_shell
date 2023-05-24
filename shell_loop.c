#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
 * hsh - Main shell.
 * @vars: struct variable.
 * @av: the argument vector.
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(var_s *vars, char **av)
{
	ssize_t p = 0;
	int builtin_ret = 0;

	while (p != -1 && builtin_ret != -2)
	{
		erase_var(vars);
		if (interactive(vars))
			_puts("$ ");
		_postchar(BUF_FLUSH);
		p = get_input(vars);
		if (p != -1)
		{
			fix_var(vars, av);
			builtin_ret = get_builtin(vars);
			if (builtin_ret == -1)
				get_cmd(vars);
		}
		else if (interactive(vars))
			_putchar('\n');
		free_var(vars, 0);
	}
	write_hist(vars);
	free_var(vars, 1);
	if (!interactive(vars) && vars->status)
		exit(vars->status);
	if (builtin_ret == -2)
	{
		if (vars->err_num == -1)
			exit(vars->status);
		exit(vars->err_num);
	}
	return (builtin_ret);
}

/**
 * get_builtin - Write a funtion to create the builtin command.
 * @vars: struct variable.
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit().
 */

int get_builtin(var_s *vars)
{
	int x, built_in_ret = -1;
	builtin_s builtintbl[] = {
		{"exit", _ssexit},
		{"env", _ssenv},
		{"help", _sshelp},
		{"history", _sshistory},
		{"setenv", _sssetenv},
		{"unsetenv", _ssunsetenv},
		{"cd", _sscd},
		{"alias", _ssalias},
		{NULL, NULL}
	};
	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(vars->argv[0], builtintbl[x].type) == 0)
		{
			vars->l_count++;
			built_in_ret = builtintbl[x].f(vars);
			break;
		}
	return (built_in_ret);
}
/**
 * get_cmd - Write a command that find its PATH(Gateway).
 * @vars: struct variable.
 *
 * Return: Void.
 */
void get_cmd(var_s *vars)
{
	char *path = NULL;
	int x, b;

	vars->path = vars->argv[0];

	if (vars->l_count_flag == 1)
	{
		vars->l_count++;
		vars->l_count_flag = 0;
	}
	for (x = 0, b = 0; vars->arg[x]; x++)
		if (!is_token(vars->arg[x], " \t\n"))
			b++;
	if (!b)
		return;
	path = path_access(vars, _getenv(vars, "PATH="), vars->argv[0]);
	if (path)
	{
		vars->path = path;
		fork_cmd(vars);
	}
	else
	{
		if ((interactive(vars) || _getenv(vars, "PATH=")
			|| vars->argv[0][0] == '/') && syn_cmd(vars, vars->argv[0]))
			fork_cmd(vars);
		else if (*(vars->arg) != '\n')
		{
			vars->status = 127;
			get_error(vars, "not found\n");
		}
	}
}
/**
 * fork_cmd - A function that fork command to enable its running.
 * @vars: struct variable.
 *
 * Return: Void.
 */
void fork_cmd(var_s *vars)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(vars->path, vars->argv, get_envn(vars)) == -1)
		{
			free_var(vars, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(vars->status));
		if (WIFEXITED(vars->status))
		{
			vars->status = WEXITSTATUS(vars->status);
			if (vars->status == 126)
				get_error(vars, "Permission denied\n");
		}
	}
}
