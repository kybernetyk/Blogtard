/*
 * helper methods for splitting a C "string" into a list of substrings.
 * (c) Jarosław Szpilewski in 2011
 * http://nntp.pl
 * http://github.com/jsz
 * License: GPL V2
 */

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "zstr.h"
#include "zstrlist.h"

struct zstrlist *zstrlist_new (size_t init_capacity)
{
	if (init_capacity <= 0)
	{
		fprintf(stderr, "capacity is null or negative!\n");
		abort();
		return NULL;
	}

	struct zstrlist *ret = (struct zstrlist*)malloc(sizeof(struct zstrlist));
	ret->elements = (struct zstr **)malloc(sizeof(struct zstr *) * init_capacity);
	ret->count = 0;
	ret->capacity = init_capacity;
	return ret;
}

void zstrlist_free (struct zstrlist *list)
{
	size_t i;
	for (i = 0; i < list->capacity; i++)
	{
		if (list->elements[i])
			zstr_free(list->elements[i]);
	}

	free(list->elements);
}

size_t zstrlist_append (struct zstrlist *list, struct zstr *str)
{
	if (!list)
	{
		fprintf(stderr, "List is null!\n");
		abort();
		return -1;
	}

	size_t pos = list->count;
	if (pos >= list->capacity)
	{
	//	printf("realloc list!\n");
		//printf("count: %lu, cap: %lu\n", list->count, list->capacity);
		list->elements = realloc(list->elements, sizeof(struct zstr *) * (list->capacity * 2));
		list->capacity *= 2;
	}
	
	list->elements[pos] = str;
	list->count ++;

	return pos;
}
