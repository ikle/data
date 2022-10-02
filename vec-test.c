/*
 * Colibri Dynamic Array (Vector) Test
 *
 * Copyright (c) 2014-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <data/label-vec.h>
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

static void label_vec_test (const char *list[])
{
	struct label_vec v;
	size_t i;

	label_vec_init (&v);

	for (i = 0; list[i] != NULL; ++i)
		label_vec_append (&v, list[i]);

	label_vec_sort (&v);

	printf ("\ncount = %zu, avail = %zu\n\n", v.count, v.avail);

	for (i = 0; i < v.count; ++i)
		printf ("%zu: %s\n", i, v.data[i]);

	label_vec_fini (&v);
}

static void string_vec_test (const char *list[])
{
	struct string_vec v;
	size_t i;

	string_vec_init (&v);

	for (i = 0; list[i] != NULL; ++i)
		string_vec_append (&v, list[i]);

	string_vec_sort (&v);

	printf ("\ncount = %zu, avail = %zu\n\n", v.count, v.avail);

	for (i = 0; i < v.count; ++i)
		printf ("%zu: %s\n", i, v.data[i]);

	string_vec_fini (&v);
}

int main (int argc, char *argv[])
{
	label_vec_test  (list);
	string_vec_test (list);
	return 0;
}
