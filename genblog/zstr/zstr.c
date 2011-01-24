/*
 * zstr.c - string methods for zstr library 
 * (c) Jarosław Szpilewski in 2011
 * http://nntp.pl
 * http://github.com/jsz
 * License: GPL V2
 */

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "zstr.h"

struct zstr *zstr_new (size_t len)
{
	struct zstr *ret = (struct zstr*)malloc(sizeof (struct zstr));
	ret->p_str = (char *)malloc(len * sizeof (char));
	ret->len = len;
	return ret;
}

void zstr_free (struct zstr *str)
{
	free (str->p_str);
}

