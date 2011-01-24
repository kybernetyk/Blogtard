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
	size_t count;
};

extern void zstrlist_free (struct zstrlist *list);


