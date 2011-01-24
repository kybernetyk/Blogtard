/*
 * string methods for zstr library 
 * (c) Jaroslaw Szpilewski in 2011
 * http://nntp.pl
 * License: GPL V2
 */
#pragma once

struct zstr
{
	char *p_str;
	size_t len;
};

extern struct zstr *zstr_new (size_t len);
extern void zstr_free (struct zstr *str);

