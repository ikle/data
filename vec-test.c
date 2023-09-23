/*
 * Capsa Dynamic Array (Vector) Test
 *
 * Copyright (c) 2014-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <capsa/int-vec.h>
#include <capsa/label-vec.h>
#include <capsa/string-vec.h>

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
	const char **e;

	label_vec_init (&v);

	for (i = 0; list[i] != NULL; ++i)
		label_vec_append (&v, list[i]);

	label_vec_sort (&v);

	printf ("\ncount = %zu, avail = %zu\n\n", v.count, v.avail);

	for (i = 0; i < v.count; ++i)
		printf ("%zu: %s\n", i, v.data[i]);

	if ((e = label_vec_search (&v, list[k])) != NULL)
		printf ("\nstring %zu '%s' found at %zu\n",
			k, list[k], e - v.data);

	label_vec_fini (&v);
}

static void string_vec_test (const char *list[], size_t k)
{
	struct string_vec v;
	size_t i;
	char **e;

	string_vec_init (&v);

	for (i = 0; list[i] != NULL; ++i)
		string_vec_append (&v, list[i]);

	string_vec_sort (&v);

	printf ("\ncount = %zu, avail = %zu\n\n", v.count, v.avail);

	for (i = 0; i < v.count; ++i)
		printf ("%zu: %s\n", i, v.data[i]);

	if ((e = string_vec_search (&v, list[k])) != NULL)
		printf ("\nstring %zu '%s' found at %zu\n",
			k, list[k], e - v.data);

	string_vec_fini (&v);
}

static const int nlist[] = { 1, 13, 3, 143, -17, 39, 40, 38, 0 };

static void int_vec_test (const int list[], size_t k)
{
	struct int_vec v;
	size_t i;
	int *e;

	int_vec_init (&v);

	for (i = 0; list[i] != 0; ++i)
		int_vec_append (&v, list[i]);

	int_vec_sort (&v);

	printf ("\ncount = %zu, avail = %zu\n\n", v.count, v.avail);

	for (i = 0; i < v.count; ++i)
		printf ("%zu: %d\n", i, v.data[i]);

	if ((e = int_vec_search (&v, list[k])) != NULL)
		printf ("\ninteger %zu '%d' found at %zu\n",
			k, list[k], e - v.data);

	int_vec_fini (&v);
}

int main (int argc, char *argv[])
{
	size_t i;

	printf ("Test set of strings:\n\n");

	for (i = 0; list[i] != NULL; ++i)
		printf ("%zu: %s\n", i, list[i]);

	label_vec_test  (list, 3);
	string_vec_test (list, 4);
	int_vec_test (nlist, 7);
	return 0;
}
