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
#include "zstr_split.h"


struct zstrlist *zstr_split (const char *str, const char *delimiter)
{
	char *tmp = strdup(str);

	//count occurences of delimiter string
	int del_count = 0;
	char *p = tmp;
	while (1)
	{
		p = strnstr(p, delimiter, strlen(p));
		if (!p)
			break;
		del_count++;
		p+=strlen(delimiter);
	}

	//replace delimiters with 0x00
	p = tmp;
	int i = 0;
	while (1)
	{
		p = strnstr(p, delimiter, strlen(p));
		if (!p)
			break;
	  memset(p, 0x00, strlen(delimiter));	
		p += strlen(delimiter);
	}

	//extract elements between 0x00
	char *substrs[del_count+1];
	char *ppos = tmp;
	char *pend = tmp + strlen(str);
	char *t = ppos;
	i = 0;
	while (ppos <= pend)
	{
		if (*ppos == '\0')
		{
				//only add if this element is not an empty string
				//happens if delimiter is located at str+0
				if (*t != '\0')
					substrs[i++] = t;

				while (!(*++ppos)); //get past consecurive 0x00
				t = ppos;
		}
		else
			ppos ++;
	}
	int element_count = i;

	struct zstrlist *ret = zstrlist_new(element_count/3);
	char *word;
	for (int i = 0; i < element_count; i++)
	{
		word = substrs[i];
		struct zstr *z = zstr_new(strlen(word)+1);
		sprintf(z->cstr, "%s", word);
		zstrlist_append(ret, z);
	}
	
	free(tmp);
	return ret;
}

struct zstrlist *zstr_split_c (const char *str, const char *delimiter)
{
	size_t wordcount = 0;
	char *save_ptr;
	char *word;
	
	char *haystack = strdup(str);
	word = strtok_r(haystack, delimiter, &save_ptr);
	while (word)
	{
		wordcount ++;
		word = strtok_r(NULL, delimiter, &save_ptr);
	};
	free(haystack);

	struct zstrlist *ret = zstrlist_new(wordcount);
	haystack = strdup(str);
	word = strtok_r(haystack, delimiter, &save_ptr);
	size_t i = 0;
	while (word)
	{
		struct zstr *z = zstr_new(strlen(word)+1);
		sprintf(z->cstr, "%s", word);
		zstrlist_append(ret, z);

		word = strtok_r(NULL, delimiter, &save_ptr);
		i++;
	}
	free(haystack);

	return ret;
}

