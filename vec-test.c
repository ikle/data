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

#include <data/string.h>
#include <data/vec.h>

VEC_DECLARE_TYPED (string, char, const char)

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

VEC_DEFINE_ALLOC (string)
VEC_DEFINE_COPY  (string)
VEC_DEFINE_EQ    (string)
VEC_DEFINE_HASH  (string)
