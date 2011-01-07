#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "utils.h"
#include "index.h"
#include "rss.h"

int main (int argc, char **argv)
{
	make_index ();
	make_rss ();
	return 0;
}
