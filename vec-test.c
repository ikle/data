/*
 * Colibri Dynamic Array (Vector) Test
 *
 * Copyright (c) 2014-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <data/string-vec.h>

static const char *list[] = {
	"test string #1",
	"Lorem ipsum dolor sit amet",
	"consectetur adipiscing elit",
	"sed do eiusmod tempor incididunt",
	"ut labore et dolore magna aliqua",
	"test string #2",
	NULL
};

int main (int argc, char *argv[])
{
	struct string_vec v;
	size_t i;

	string_vec_init (&v);

	for (i = 0; list[i] != NULL; ++i)
		string_vec_append (&v, list[i]);

	printf ("\ncount = %zu, avail = %zu\n\n", v.count, v.avail);

	for (i = 0; i < v.count; ++i)
		printf ("%zu: %s\n", i, v.data[i]);

	string_vec_fini (&v);
	return 0;
}
