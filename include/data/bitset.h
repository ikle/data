/*
 * Compact Binary Set
 *
 * Copyright (c) 2007-2017,2019 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef DATA_BITSET_H
#define DATA_BITSET_H  1

#include <stdint.h>
#include <stdlib.h>

#include <data/type.h>

struct bitset {
	size_t count;	/* number of allocated words */
	unsigned long *set;
};

static inline void bitset_init (struct bitset *o)
{
	o->count = 0;
	o->set = NULL;
}

static inline void bitset_fini (struct bitset *o)
{
	free (o->set);
}

int bitset_eq (const void *a, const void *b);
size_t bitset_hash (const void *o);

int bitset_is_member (const struct bitset *o, size_t x);

/* o = o U {x} */
int bitset_add (struct bitset *o, size_t x);

/* o = o \ {x} */
void bitset_del (struct bitset *o, size_t x);

/* o = o U s */
int bitset_join (struct bitset *o, const struct bitset *s);

/* o = o \ s */
int bitset_diff (struct bitset *o, const struct bitset *s);

#endif  /* DATA_BITSET_H */
