#include <stdio.h>
#include <stdlib.h>
#include "smap.h"

static int* create_int(int value)
{
	int *i = calloc(1, sizeof *i);
	*i = value;
	return i;
}

int main()
{
	const char *keys[] = {
		"hi",
		"ih",
		"hello",
		"a",
		"b",
		"c",
		"d",
		"e",
		"f",
		"g",
		"h",
		"j",
		"k",
		"l",
		"a"
	};
	
	t_smap *m = smap_create();

	// int i;
	// for (i = 0; i < (int)(sizeof keys / sizeof keys[0]); ++i) {
	// 	smap_push(m, keys[i], create_int(i + 1));
	// }

	// for (i = 0; i < (int)(sizeof keys / sizeof keys[0]); ++i) {
	// 	printf("%s - %d \n", keys[i], *(int *)smap_get(m, keys[i]));
	// }

	// printf("smap_clean\n");
	// smap_clean(m);


	// for (i = 0; i < (int)(sizeof keys / sizeof keys[0]); ++i) {
	// 	smap_push(m, keys[i], create_int(i + 1));
	// }

	// for (i = 0; i < (int)(sizeof keys / sizeof keys[0]); ++i) {
	// 	printf("%s - %d \n", keys[i], *(int *)smap_get(m, keys[i]));
	// }
	
	int i = 0;
	smap_push(m, "abcdifg", create_int(++i));
	smap_push(m, "gabcdif", create_int(++i));
	smap_push(m, "fgabcdi", create_int(++i));
	smap_push(m, "ifgabcd", create_int(++i));
	smap_push(m, "difgabc", create_int(++i));
	smap_push(m, "cdifgab", create_int(++i));
	smap_push(m, "bcdifga", create_int(++i));

	for (i = 0; i < (int)(sizeof keys / sizeof keys[0]); ++i) {
		smap_push(m, keys[i], create_int(i + 1));
	}

	for (i = 0; i < (int)(sizeof keys / sizeof keys[0]); ++i) {
		printf("%s - %d \n", keys[i], *(int *)smap_get(m, keys[i]));
	}

	smap_destroy(m);
	
	return 0;
}
