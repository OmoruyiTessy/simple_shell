#include "shell.h"
/**
 * custom_memset - Fills a memory area with a constant byte.
 * @dest: The pointer to the memory area.
 * @byte: The byte value to fill the memory with.
 * @n: The number of bytes to fill.
 * Return: A pointer to the memory area.
 */
char *custom_memset(char *dest, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = byte;
	return (dest);
}
/**
 * free_string_array - Frees an array of strings and the array itself.
 * @str_array: The array of strings to be freed.
 */
void free_string_array(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temp);
}
/**
 * custom_realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ed block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the reallocated block.
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
