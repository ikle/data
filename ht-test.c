/*
 * Opening Addressing Hash Table test
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <err.h>
#include <stdio.h>

#include <data/hash.h>
#include <data/ht.h>
#include <data/string.h>

static void *string_copy_const (const void *from)
{
	return (void *) from;
}

static const struct data_type string_good_type = {
	.copy	= string_copy_const,
	.hash	= string_hash,
	.eq	= string_eq,
};

static size_t string_bad_hash (size_t iv, const void *o)
{
	return *(const char *) o;  /* bad hash to test collisions */
}

static const struct data_type string_bad_type = {
	.copy	= string_copy_const,
	.hash	= string_bad_hash,
	.eq	= string_eq,
};

static size_t string_very_bad_hash (size_t iv, const void *o)
{
	return 0;  /* very bad hash to test collisions */
}

static const struct data_type string_very_bad_type = {
	.copy	= string_copy_const,
	.hash	= string_very_bad_hash,
	.eq	= string_eq,
};

static const char *strings[] = {
	"test string #1",
	"Lorem ipsum dolor sit amet",
	"consectetur adipiscing elit",
	"sed do eiusmod tempor incididunt",
	"ut labore et dolore magna aliqua",
	"test string #2",
	NULL,
};

static void do_test (const struct data_type *type)
{
	struct ht ht;
	const char **p;
	size_t i;

	if (!ht_init (&ht, type))
		err (1, "cannot initialize hash table");

	for (p = strings; *p != NULL; ++p)
		if (!ht_insert (&ht, (void *) *p, 0))
			err (1, "cannot insert string");

	if (ht_insert (&ht, (void *) strings[0], 0))
		errx (1, "string exists, but not found");

	printf ("load factor = %zu%%\n\n", ht.count * 100 / ht.size);

	for (i = 0; i < ht.size; ++i)
		if (ht.table[i] != NULL)
			printf ("%2zu at %2zu: %s\n",
				type->hash (0, ht.table[i]) & (ht.size - 1), i,
				(const char *) ht.table[i]);

	ht_fini (&ht);
}

int main (int argc, char *argv[])
{
	printf ("With data/hash:\n\n");
	do_test (&string_good_type);

	printf ("\nWith bad hash (value of first character):\n\n");
	do_test (&string_bad_type);

	printf ("\nWith very bad hash (constant value):\n\n");
	do_test (&string_very_bad_type);

	return 0;
}
