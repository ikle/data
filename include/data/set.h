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

#define SET_DECLARE(Type)						\
									\
struct Type##_set {							\
	struct ht table;						\
};									\
									\
static inline void Type##_set_init (struct Type##_set *o)		\
{									\
	ht_init (&o->table, &Type##_type);				\
}									\
									\
static inline void Type##_set_fini (struct Type##_set *o)		\
{									\
	ht_fini (&o->table);						\
}									\
									\
static inline void Type##_set_clean (struct Type##_set *o)		\
{									\
	ht_clean (&o->table);						\
}									\
									\
static inline int Type##_set_is_member (struct Type##_set *o,		\
					const struct Type *e)		\
{									\
	return ht_lookup (&o->table, e) != NULL;			\
}									\
									\
static inline const struct Type *Type##_set_add (struct Type##_set *o,	\
						 const struct Type *e)	\
{									\
	return ht_insert (&o->table, e, 1);				\
}									\
									\
static inline void Type##_set_del (struct Type##_set *o,		\
				   const struct Type *e)		\
{									\
	ht_remove (&o->table, e);					\
}									\
									\
static inline int Type##_set_join (struct Type##_set *o,		\
				   const struct Type##_set *s)		\
{									\
	size_t i;							\
	struct Type *entry;						\
									\
	ht_foreach (i, entry, &s->table)				\
		if (Type##_set_add (o, entry) == NULL)			\
			return 0;					\
									\
	return 1;							\
}									\
									\
static inline void Type##_set_diff (struct Type##_set *o,		\
				    const struct Type##_set *s)		\
{									\
	size_t i;							\
	struct Type *entry;						\
									\
	ht_foreach (i, entry, &s->table)				\
		Type##_set_del (o, entry);				\
}

#endif  /* COLIBRI_DATA_SET_H */
