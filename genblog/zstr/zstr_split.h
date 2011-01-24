/*
 * helper methods for splitting a C "string" into a list of substrings.
 * (c) Jaroslaw Szpilewski in 2011
 * http://nntp.pl
 * License: GPL V2
 */
#pragma once
extern struct zstrlist *zstr_split (const char *str, const char *delimiter);

