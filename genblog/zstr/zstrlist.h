/*
 * helper methods for splitting a C "string" into a list of substrings.
 * (c) Jaroslaw Szpilewski in 2011
 * http://nntp.pl
 * License: GPL V2
 */
#pragma once

struct zstrlist
{
	struct zstr **elements;
	
	size_t count;  //current element count
	size_t capacity;  //allocated memory for elements
};

extern struct zstrlist *zstrlist_new (size_t init_capacity);
extern void zstrlist_free (struct zstrlist *list);
extern size_t zstrlist_append (struct zstrlist *list, struct zstr *str);


