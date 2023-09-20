/*
 * Opening Addressing Hash Table test
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <err.h>
#include <stdio.h>

#include <capsa/atom.h>
#include <data/ht.h>
#include <data/string.h>

static const struct data_type atom_good_type = {
	.copy	= (copy_fn *) atom_copy,
	.free	= (free_fn *) atom_free,
	.eq	= (eq_fn   *) atom_eq,
	.hash	= (hash_fn *) string_hash,
};

static size_t string_bad_hash (const void *o, size_t iv)
{
	return *(const char *) o;  /* bad hash to test collisions */
}

static const struct data_type atom_bad_type = {
	.copy	= (copy_fn *) atom_copy,
	.free	= (free_fn *) atom_free,
	.eq	= (eq_fn   *) atom_eq,
	.hash	= string_bad_hash,
};

static size_t string_very_bad_hash (const void *o, size_t iv)
{
	return 0;  /* very bad hash to test collisions */
}

static const struct data_type atom_very_bad_type = {
	.copy	= (copy_fn *) atom_copy,
	.free	= (free_fn *) atom_free,
	.eq	= (eq_fn   *) atom_eq,
	.hash	= string_very_bad_hash,
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
	const char **p, *entry;
	size_t i;

	if (!ht_init (&ht, type))
		err (1, "cannot initialize hash table");

	for (p = strings; *p != NULL; ++p)
		if (ht_insert (&ht, *p, 0) == NULL)
			err (1, "cannot insert string");

	if (ht_insert (&ht, strings[0], HT_ONCE) != NULL)
		errx (1, "string exists, but not found");

	printf ("load factor = %zu%%\n\n", ht.count * 100 / ht.size);

	ht_foreach (i, entry, &ht)
		printf ("%2zu at %2zu: %s\n",
			type->hash (ht.table[i], 0) & (ht.size - 1), i, entry);

	printf ("\nremove item #3: %s\n\n", strings [3]);

	ht_remove (&ht, strings [3]);

	ht_foreach (i, entry, &ht)
		printf ("%2zu at %2zu: %s\n",
			type->hash (ht.table[i], 0) & (ht.size - 1), i, entry);

	ht_fini (&ht);
}

int main (int argc, char *argv[])
{
	printf ("With data/hash:\n\n");
	do_test (&atom_good_type);

	printf ("\nWith bad hash (value of first character):\n\n");
	do_test (&atom_bad_type);

	printf ("\nWith very bad hash (constant value):\n\n");
	do_test (&atom_very_bad_type);

	return 0;
}
