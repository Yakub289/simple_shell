#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
 * _err_ato - Function that will print converted string to integer.
 * @p: string to be converted.
 *
 * Return: 0 if no integer in string or -1 if failed.
 */
int _err_ato(char *p)
{
	int x = 0;
	unsigned long int r_sult = 0;

	if (*p == '+')
		p++;
	for (x = 0;  p[x] != '\0'; x++)
	{
		if (p[x] >= '0' && p[x] <= '9')
		{
			r_sult *= 10;
			r_sult += (p[x] - '0');
			if (r_sult > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (r_sult);
}

/**
 * get_error - Fuction that will print an error message.
 * @vars: struct variable contains arguements.
 * @e_str: string containing specified error type
 *
 * Return: 0 if no numbers  appears in string or -1 if failed.
 */
void get_error(var_s *vars, char *e_str)
{
	_post(vars->f_name);
	_post(": ");
	get_di(vars->l_count, STDERR_FILENO);
	_post(": ");
	_post(vars->argv[0]);
	_post(": ");
	_post(e_str);
}
