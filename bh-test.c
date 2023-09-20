/*
 * Simple Binary Heap with Wait Queue
 *
 * Copyright (c) 2015-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <data/bh.h>

static int gt (const void *a, const void *b)
{
	return a > b;
}

static const int test[] = {
	1, 2, 3, 17, 53, 413, 3, 42, 15, 32, 3, 8, 9, 11, 112, 327, 0
};

int main (int argc, char *argv[])
{
	struct bh o;
	const int *p, *e;

	bh_init (&o, gt);

	printf ("push");

	for (p = test; *p != 0; ++p)
		if (bh_push (&o, NULL + *p, 0))
			printf (" %d", *p);

	printf ("\ntop = %ld\npop", (long) bh_top (&o));

	while ((e = bh_pop (&o)) != NULL)
		printf (" %ld", (long) e);

	printf ("\npush");

	for (p = test; *p != 0; ++p)
		if (bh_push (&o, NULL + *p, 0))
			printf (" %d", *p);

	printf ("\ntop = %ld\npop", (long) bh_top (&o));

	while ((e = bh_pop (&o)) != NULL)
		printf (" %ld", (long) e);

	printf ("\n");

	bh_fini (&o, NULL);
	return 0;
}
