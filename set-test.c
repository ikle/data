/*
 * Colibri Set Test
 *
 * Copyright (c) 2014-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <data/set.h>
#include <data/string.h>

SET_DECLARE (string)

static const char *strings[] = {
	"test string #1",
	"Lorem ipsum dolor sit amet",
	"consectetur adipiscing elit",
	"sed do eiusmod tempor incididunt",
	"ut labore et dolore magna aliqua",
	"test string #2",
	NULL,
};

static const char *string_get (const struct string *o)
{
	return (void *) o;
}

int main (int argc, char *argv[])
{
	const struct string **list = (void *) strings;
	struct string_set A;
	size_t i;
	const char *entry;

	string_set_init (&A);

	for (i = 0; list[i] != NULL; ++i)
		if (string_set_add (&A, list[i]) == NULL)
			fprintf (stderr, "W: cannot add '%s' to set\n",
				 string_get (list[i]));

	printf ("A:\n\n");

	set_foreach (i, entry, &A)
		printf ("%2zu: %s\n", i, entry);

	string_set_del (&A, list[1]);
	string_set_del (&A, list[3]);

	printf ("\nA \\ {list[1], list[3]}:\n\n");

	set_foreach (i, entry, &A)
		printf ("%2zu: %s\n", i, entry);

	string_set_fini (&A);
	return 0;
}
