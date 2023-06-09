#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
 * _strcpy - Function that prints copies a string character.
 * @dist: destination of string.
 * @rsc: source of string character.
 *
 * Return: pointer to access destination address.
 */
char *_strcpy(char *dist, char *rsc)
{
	int x = 0;

	if (dist == rsc || rsc == 0)
		return (dist);
	while (rsc[x])
	{
		dist[x] = rsc[x];
		x++;
	}

	dist[x] = 0;

	return (dist);
}

/**
 * _strdup - Function that prints duplicated string character.
 * @str: duplicated string character.
 *
 * Return: pointer to access duplicated string character.
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *ate;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ate = malloc(sizeof(char) * (len + 1));

	if (!ate)
		return (NULL);

	for (len++; len--;)
		ate[len] = *--str;

	return (ate);
}

/**
 * _puts - Function that will prints an input string character.
 * @str: printed string.
 *
 * Return: Nothing 0.
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}
