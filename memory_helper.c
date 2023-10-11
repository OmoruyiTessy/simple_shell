#include "shell.h"
/**
 * free_and_null - Frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free simple shell
 *
 * This function frees the memory pointed to by the given pointer and
 * then sets the pointer itself to NULL to prevent a dangling pointer.
 *
 * Return: 1 if freed, 0 otherwise.
 */
int free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
