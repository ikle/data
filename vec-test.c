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

static void label_vec_test (const char *list[], size_t k)
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

	if ((i = label_vec_search (&v, list[k])) != -1)
		printf ("\nstring %zu '%s' found at %zu\n", k, list[k], i);

	label_vec_fini (&v);
}

static void string_vec_test (const char *list[], size_t k)
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

	if ((i = string_vec_search (&v, list[k])) != -1)
		printf ("\nstring %zu '%s' found at %zu\n", k, list[k], i);

	string_vec_fini (&v);
}

int main (int argc, char *argv[])
{
	size_t i;

	printf ("Test set of strings:\n\n");

	for (i = 0; list[i] != NULL; ++i)
		printf ("%zu: %s\n", i, list[i]);

	label_vec_test  (list, 3);
	string_vec_test (list, 4);
	return 0;
}
