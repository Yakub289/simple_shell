#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * aux_free - Function that will free a pointer and ineffect address.
 * @ptr: address to access pointer to free.
 *
 * Return: 1 if free or Nothing 0.
 */
int aux_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}

