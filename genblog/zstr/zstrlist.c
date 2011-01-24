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

void zstrlist_free (struct zstrlist *list)
{
	size_t i;
	for (i = 0; i < list->count; i++)
	{
		zstr_free(list->elements[i]);
	}

	free(list->elements);
}

