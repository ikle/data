/*
 * S-Expressions, internals
 *
 * Copyright (c) 2019-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_SE_INT_H
#define COLIBRI_DATA_SE_INT_H  1

#include <data/se.h>

/*
 * NOTE: We assume max (sizeof (long long), sizeof (long double)) > 1,
 *       thus malloc returns aligned pointer at least to 2.
 */

static inline struct se *name_to_atom (const char *name)
{
	return (void *) ((ptrdiff_t) name | 1);
}

static inline const char *atom_to_name (const struct se *o)
{
	return (void *) ((ptrdiff_t) o & ~1);
}

static inline int se_is_atom (const struct se *o)
{
	return o == NULL || ((ptrdiff_t) o & 1) != 0;
}

struct se_pair {
	struct se *head, *tail;
};

static inline struct se *pair_to_se (struct se_pair *o)
{
	return (void *) o;
}

static inline struct se_pair *se_to_pair (struct se *o)
{
	return (void *) o;
}

#endif  /* COLIBRI_DATA_SE_INT_H */
