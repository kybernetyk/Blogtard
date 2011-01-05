#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define POSTS_DIR "posts"

const char *current_dir = ".";

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

void append_post_to_fp (const char *filename, FILE *f_out)
{
	printf("\t\tappending post %s ...\n", filename);

	/* append header */
	append_file_to_fp ("templates/main/post/header.template", f_out);

	/* append link */
	append_str_to_fp ("[l] ", f_out);

	/* append the post */
	size_t len = strlen(current_dir) + strlen("/") + strlen(filename) + 1;
	char absname[len];
	sprintf(absname,"%s/%s", current_dir, filename);
	append_file_to_fp (absname, f_out);
	
	/* append footer */
	append_file_to_fp ("templates/main/post/footer.template", f_out);
}

void append_date_to_fp (const char *date, FILE *f_out)
{
	append_file_to_fp ("templates/main/date/prefix.template", f_out);
	append_str_to_fp (date, f_out);
	append_file_to_fp ("templates/main/date/suffix.template", f_out);
}

void append_posts_from_dir_to_fp (const char *dirname, FILE *f_out)
{
	//todo: check if ent is dir or file. on file continue on dir process
	size_t len = strlen(current_dir) + strlen("/") + strlen(dirname) + 1;
	char absname[len];
	sprintf(absname,"%s/%s", current_dir, dirname);
	
	printf("\tappend_posts_from_dir_to_fp: %s\n", absname); 

	
	//save pos for possible rewind if no posts were added for this date
	size_t savepos = ftell(f_out);
	append_date_to_fp (dirname, f_out);

	append_file_to_fp ("templates/main/date/blockheader.template", f_out);
	
	//let's add the posts for today
	int post_count_for_date = 0;

	struct dirent **dir_entries;
	int n = scandir(absname, &dir_entries, 0, alphasort);
	if (n < 0)
	{
		fprintf(stderr, "couldn't open dir %s for reading\n", absname);
		exit(3);
	}

	while (n--)
	{
		if (dir_entries[n]->d_name[0] == '.')
			continue;

		current_dir = absname;
		post_count_for_date ++;
		append_post_to_fp (dir_entries[n]->d_name, f_out);
	}
	free (dir_entries);
	
	append_file_to_fp ("templates/main/date/blockfooter.template", f_out);

	//if no posts were added for this date, let's rewind to the previous position
	//so we won't have an empty date header
	if (post_count_for_date == 0)
		fseek(f_out, savepos, SEEK_SET);

}

void make_index ()
{
	printf("making index ...\n");

	FILE *f_out = fopen_or_die ("out/index.html", "wt");

	append_file_to_fp("templates/main/header.template", f_out);

	struct dirent **dir_entries;
	int n = scandir(POSTS_DIR, &dir_entries, 0, alphasort);
	if (n < 0)
	{
		fprintf(stderr, "couldn't open posts dir for reading\n");
		exit(3);
	}

	//reverse dir iteration because blog posts are upside down (latest on top)
	while (n--)
	{
		if (dir_entries[n]->d_name[0] == '.')
			continue;

		current_dir = POSTS_DIR;
		append_posts_from_dir_to_fp (dir_entries[n]->d_name, f_out);
	}
	free (dir_entries);

	append_file_to_fp ("templates/main/footer.template", f_out);
	fclose(f_out);
}


int main (int argc, char **argv)
{
	make_index ();

	return 0;
}
