#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "utils.h"
#include "rss.h"
#include "global.h"

//TODO: 
//[ ] date for each item
//[ ] link to the items not to the main page
//[ ] get the title somehow right (removing html tags)

static const char *current_dir = ".";

static void append_element_to_fp (const char *filename, FILE *f_out)
{
	printf("\t\tappending element %s ...\n", filename);

	/* append header */
	append_file_to_fp ("templates/rss/element/header.template", f_out);


	/* append description */
	append_file_to_fp ("templates/rss/element/description_header.template", f_out);


	/* append the post */
	size_t len = strlen(current_dir) + strlen("/") + strlen(filename) + 1;
	char absname[len];
	sprintf(absname,"%s/%s", current_dir, filename);
	append_file_to_fp (absname, f_out);
	//append_str_to_fp (absname, f_out);

	/* desc end */
	append_file_to_fp ("templates/rss/element/description_footer.template", f_out);

	/* append title */
	append_file_to_fp ("templates/rss/element/title_header.template", f_out);

	FILE *el = fopen_or_die (absname, "rt");
	char title[32];
	fread(title, 28, 1, el);
	title[27] = '.';
	title[28] = '.';
	title[29] = '.';
	title[30] = '\0';
	fclose (el);

	append_str_to_fp (title, f_out);

	/* title end */
	append_file_to_fp ("templates/rss/element/title_footer.template", f_out);





	/* append link */
	append_file_to_fp ("templates/rss/element/link_header.template", f_out);
	append_str_to_fp ("http://fettemama.org", f_out);
	append_file_to_fp ("templates/rss/element/link_footer.template", f_out);

	/* append guid */
	append_file_to_fp ("templates/rss/element/guid_header.template", f_out);
	append_str_to_fp ("http://fettemama.org/", f_out);
	append_str_to_fp (absname, f_out);
	append_file_to_fp ("templates/rss/element/guid_footer.template", f_out);

	/* append date */
	append_file_to_fp ("templates/rss/element/date_header.template", f_out);

	struct stat attribs;
	stat (absname, &attribs);

	char s_time[255];
	rfc822_from_tstamp (attribs.st_mtimespec.tv_sec, s_time, 255);

	append_str_to_fp (s_time, f_out);

	append_file_to_fp ("templates/rss/element/date_footer.template", f_out);

	/* append footer */
	append_file_to_fp ("templates/rss/element/footer.template", f_out);
}



static void append_elements_from_dir_to_fp (const char *dirname, FILE *f_out)
{
		//todo: check if ent is dir or file. on file continue on dir process
	size_t len = strlen(current_dir) + strlen("/") + strlen(dirname) + 1;
	char absname[len];
	sprintf(absname,"%s/%s", current_dir, dirname);
	
	printf("\tappend_elements_from_dir_to_fp: %s\n", absname); 


	size_t savepos = ftell(f_out);
	
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
		append_element_to_fp (dir_entries[n]->d_name, f_out);
	}
	free (dir_entries);
	

	//if no posts were added for this date, let's rewind to the previous position
	//so we won't have an empty date header
	if (post_count_for_date == 0)
		fseek(f_out, savepos, SEEK_SET);


}


void make_rss ()
{
	printf("making rss ...\n");

	FILE *f_out = fopen_or_die ("out/rss.xml", "wt");
	
	append_file_to_fp ("templates/rss/header.template", f_out);

	struct dirent **dir_entries;
	int n = scandir(POSTS_DIR, &dir_entries, 0, alphasort);
	if (n < 0)
	{
		fprintf (stderr, "couldn't open posts dir for reading\n");
		exit (8);
	}

	while (n--)
	{
		if (dir_entries[n]->d_name[0] == '.')
			continue;

		current_dir = POSTS_DIR;
		append_elements_from_dir_to_fp (dir_entries[n]->d_name, f_out);
	}
	free (dir_entries);

	append_file_to_fp ("templates/rss/footer.template", f_out);
	fclose (f_out);
}
