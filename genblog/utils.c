#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#include "utils.h"


int rfc822_from_tstamp (time_t timestamp, char *out_buffer, size_t bufsize)
{
	struct tm *timeinfo;
	timeinfo = localtime (&timestamp);
	mktime (timeinfo);
	
	size_t l = strftime (out_buffer, bufsize-1, "%a, %d %b %Y %H:%M:%S %z", timeinfo);

	return l;
}

FILE *fopen_or_die (const char *fname, const char *mode)
{
	FILE *ret = fopen (fname, mode);
	if (!ret)
	{
		fprintf(stderr, "couldn't open file <%s> with mode <%s>.\n", fname, mode);
		exit(23);

		return NULL;
	}

	return ret;
}

void append_file_to_fp (const char *filename, FILE *f_out)
{
	//printf("appending %s ...\n", filename);
	FILE *f_in = fopen_or_die(filename,"rt");
	
	int c = EOF;
	while ( (c = fgetc(f_in)) != EOF)
		fputc(c, f_out);

	fclose(f_in);
}

void append_fp_to_fp (FILE *f_in, FILE *f_out)
{
	int c = EOF;
	while( (c = fgetc(f_in)) != EOF)
		fputc(c, f_out);
}

void append_str_to_fp (const char *str, FILE *f_out)
{
	fwrite(str, strlen(str), 1, f_out);
}


