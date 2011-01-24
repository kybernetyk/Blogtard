#include <stdio.h>
#include "zstrlib.h"

//#define __JS_TEST__STRSPLIT__
#ifdef __JS_TEST__STRSPLIT__
int main (int argc, char **argv)
{
	const char str[] = "this,is,a,comma,seperated,,list,lol. Let's have some fun!";
	printf("string: %s\n", str);

	struct zstrlist *list = zstr_split(str, ",");
	
	for (int i = 0; i < list->count; i++)
	{
		printf("%i[%lu]: %s\n",i,list->elements[i]->len, list->elements[i]->p_str);
	}
	zstrlist_free(list);

	return 0;
}
#endif
