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

/**
 * get_di - Write a function that produce a digit to (base 10).
 * @input: the input
 * @fl: print line
 *
 * Return: number of characters printed
 */
int get_di(int input, int fl)
{
	int (*__putchar)(char) = _putchar;
	int p, count = 0;
	unsigned int _abs_, current;

	if (fl == STDERR_FILENO)
		__putchar = _postchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (p = 1000000000; p > 1; p /= 10)
	{
		if (_abs_ / p)
		{
			__putchar('0' + current / p);
			count++;
		}
		current %= p;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * trans_number - Allocate determinant to switch a function case.
 * @num: number.
 * @base: base.
 * @flags: argument flags
 *
 * Return: string
 */
char *trans_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pt;
	unsigned long digit = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		digit = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffer[49];
	*pt = '\0';

	do	{
		*--pt = array[digit % base];
		digit /= base;
	} while (digit != 0);

	if (sign)
		*--pt = sign;
	return (pt);
}

/**
 * delete_comment - Function that replaces first initialize of '#' with '\0'.
 * @buf: String modifying buff.
 *
 * Return: Always 0 (success).
 */
void delete_comment(char *buf)
{
	int d;

	for (d = 0; buf[d] != '\0'; d++)
		if (buf[d] == '#' && (!d || buf[d - 1] == ' '))
		{
			buf[d] = '\0';
			break;
		}
}
