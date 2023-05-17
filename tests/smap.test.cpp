#include <stdlib.h>
#include "catch.hpp"
#include "smap.h"

static int* create_int(int value)
{
	int *i = (int *)calloc(1, sizeof *i);
	*i = value;
	return i;
}

TEST_CASE("Push and get")
{
	SECTION("Push some elements") 
	{
		const char *keys[] = {
			"hi",
			"ih",
		};

		t_smap *m = smap_create();
		int i;
		for (i = 0; i < (int)(sizeof keys / sizeof keys[0]); ++i) {
			smap_push(m, keys[i], create_int(i + 1));
		}

		for (i = 0; i < (int)(sizeof keys / sizeof keys[0]); ++i) {
			REQUIRE(*(int *)smap_get(m, keys[i]) == (i + 1));
		}
		smap_destroy(m);
	}
}
