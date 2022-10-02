/*
 * Colibri Set helpers
 *
 * Copyright (c) 2014-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_SET_H
#define COLIBRI_DATA_SET_H  1

#include <data/ht.h>

#define SET_DECLARE_TYPED(name, type, ctype)				\
									\
struct name##_set {							\
	struct ht table;						\
};									\
									\
static inline void name##_set_init (struct name##_set *o)		\
{									\
	ht_init (&o->table, &name##_type);				\
}									\
									\
static inline void name##_set_fini (struct name##_set *o)		\
{									\
	ht_fini (&o->table);						\
}									\
									\
static inline								\
struct name##_set *name##_set_copy (const struct name##_set *o)		\
{									\
	return ht_copy (o);						\
}									\
									\
static inline int name##_set_eq (const struct name##_set *a,		\
				 const struct name##_set *b)		\
{									\
	return ht_eq (a, b);						\
}									\
									\
static inline void name##_set_clean (struct name##_set *o)		\
{									\
	ht_clean (&o->table);						\
}									\
									\
static inline int name##_set_is_member (struct name##_set *o, ctype *e)	\
{									\
	return ht_lookup (&o->table, e) != NULL;			\
}									\
									\
static inline ctype *name##_set_insert (struct name##_set *o, ctype *e)	\
{									\
	return ht_insert (&o->table, e, 0);				\
}									\
									\
static inline void name##_set_remove (struct name##_set *o, ctype *e)	\
{									\
	ht_remove (&o->table, e);					\
}									\
									\
static inline int name##_set_join (struct name##_set *o,		\
				   const struct name##_set *s)		\
{									\
	size_t i;							\
	type *entry;							\
									\
	ht_foreach (i, entry, &s->table)				\
		if (name##_set_insert (o, entry) == NULL)		\
			return 0;					\
									\
	return 1;							\
}									\
									\
static inline void name##_set_diff (struct name##_set *o,		\
				    const struct name##_set *s)		\
{									\
	size_t i;							\
	type *entry;							\
									\
	ht_foreach (i, entry, &s->table)				\
		name##_set_remove (o, entry);				\
}

#define SET_DECLARE(name) \
	SET_DECLARE_TYPED (name, struct name, const struct name)

#define set_foreach(i, entry, o)					\
	for ((i) = 0; (i) < (o)->table.size; ++(i))			\
		if (((entry) = (o)->table.table[i]) != NULL)

#endif  /* COLIBRI_DATA_SET_H */
