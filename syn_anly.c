#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
 * syn_cmd - Synchroniztion of executable command files.
 * @vars: struct variable.
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int syn_cmd(var_s *vars, char *path)
{
	struct stat st;
	(void)vars;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * syn_char - Synchronize pathways for  string characters.
 * @pathway: character path
 * @begin: starting index
 * @end: stopping index
 *
 * Return: pointer to new buffer
 */
char *syn_char(char *pathway, int begin, int end)
{
	static char buf[1024];
	int w = 0, y = 0;

	for (w = 0, w = begin; w < end; w++)
		if (pathway[w] != ':')
			buf[y++] = pathway[w];
	buf[y] = 0;
	return (buf);
}

/**
 * path_access - Write a funtion to enable open strings.
 * @vars: the info struct
 * @pathway: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *path_access(var_s *vars, char *pathway, char *cmd)
{
	int x = 0, curr_pos = 0;
	char *path;

	if (!pathway)
		return (NULL);
	if ((_strlen(cmd) > 2) && begin_at(cmd, "./"))
	{
		if (syn_cmd(vars, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathway[x] || pathway[x] == ':')
		{
			path = syn_char(pathway, curr_pos, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (syn_cmd(vars, path))
				return (path);
			if (!pathway[x])
				break;
			curr_pos = x;
		}
		x++;
	}
	return (NULL);
}
