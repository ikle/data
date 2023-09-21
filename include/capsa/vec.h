/*
 * Capsa Dynamic Array (Vector)
 *
 * Copyright (c) 2014-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_VEC_H
#define CAPSA_VEC_H  1

#include <capsa/types.h>
#include <stdlib.h>

struct atom_vec;

void *unit_vec_alloc (void);
void *unit_vec_copy (const struct atom_vec *o, size_t size);

bool vec_expand    (struct atom_vec *o, size_t size);
bool vec_resize_nc (struct atom_vec *o, size_t size, size_t avail);

#define VEC_DECLARE_TYPED(name, type, ctype)				\
									\
struct name##_vec {							\
	size_t count, avail;						\
	type *data;							\
};									\
									\
static inline void name##_vec_init (struct name##_vec *o)		\
{									\
	o->count = 0;							\
	o->avail = 0;							\
	o->data  = NULL;						\
}									\
									\
static inline void name##_vec_fini (struct name##_vec *o)		\
{									\
	size_t i;							\
									\
	for (i = 0; i < o->count; ++i)					\
		name##_free (o->data[i]);				\
									\
	free (o->data);							\
}									\
									\
static inline struct name##_vec *name##_vec_alloc (void)		\
{									\
	return unit_vec_alloc ();					\
}									\
									\
static inline void name##_vec_free (struct name##_vec *o)		\
{									\
	if (o == NULL)							\
		return;							\
									\
	name##_vec_fini (o);						\
	free (o);							\
}									\
									\
static inline bool name##_vec_expand (struct name##_vec *o)		\
{									\
	return vec_expand ((void *) o, sizeof (type));			\
}									\
									\
static inline								\
void name##_vec_insert (struct name##_vec *o, size_t i, ctype e)	\
{									\
	name##_free (o->data[i]);					\
	o->data[i] = name##_copy (e);					\
}									\
									\
static inline bool name##_vec_append (struct name##_vec *o, ctype e)	\
{									\
	if (o->count >= o->avail && !name##_vec_expand (o))		\
		return false;						\
									\
	o->data[o->count++] = name##_copy (e);				\
	return true;							\
}									\
									\
static inline								\
void name##_vec_insert_nc (struct name##_vec *o, size_t i, type e)	\
{									\
	name##_free (o->data[i]);					\
	o->data[i] = e;							\
}									\
									\
static inline bool name##_vec_append_nc (struct name##_vec *o, type e)	\
{									\
	if (o->count >= o->avail && !name##_vec_expand (o)) {		\
		name##_free (e);					\
		return false;						\
	}								\
									\
	o->data[o->count++] = e;					\
	return true;							\
}									\
									\
bool   name##_vec_eq   (const struct name##_vec *o,			\
			const struct name##_vec *peer);			\
size_t name##_vec_hash (const struct name##_vec *o, size_t iv);		\
									\
static inline int name##_compar (const void *a, const void *b)		\
{									\
	return name##_cmp (*(ctype *) a, *(ctype *) b);			\
}									\
									\
static inline void name##_vec_sort (struct name##_vec *o)		\
{									\
	qsort (o->data, o->count, sizeof (o->data[0]), name##_compar);	\
}									\
									\
static inline								\
size_t name##_vec_search (const struct name##_vec *o, ctype key)	\
{									\
	type *e = bsearch (&key, o->data, o->count,			\
			   sizeof (o->data[0]), name##_compar);		\
									\
	return e == NULL ? -1 : (e - o->data);				\
}									\

#define VEC_DECLARE(name) \
	VEC_DECLARE_TYPED(name, struct name *, const struct name *)

#define VEC_DECLARE_UNIT_COPY(name)					\
									\
static inline								\
struct name##_vec *name##_vec_copy (const struct name##_vec *o)		\
{									\
	return unit_vec_copy ((void *) o, sizeof (o->data[0]));		\
}									\

#define VEC_DECLARE_COPY(name)						\
									\
struct name##_vec *name##_vec_copy (const struct name##_vec *o);	\

#define VEC_DEFINE_COPY(name)						\
									\
struct name##_vec *name##_vec_copy (const struct name##_vec *o)		\
{									\
	struct name##_vec *copy;					\
	size_t i;							\
									\
	if ((copy = name##_vec_alloc ()) == NULL)			\
		return copy;						\
									\
	if (!vec_resize_nc ((void *) copy, sizeof (o->data[0]), o->avail))	\
		goto no_resize;						\
									\
	for (i = 0; i < o->count; ++i) {				\
		copy->data[i] = name##_copy (o->data[i]);		\
									\
		if (copy->data[i] == NULL && o->data[i] != NULL)	\
			goto no_copy;					\
	}								\
									\
	copy->count = i;						\
	return copy;							\
no_copy:								\
	copy->count = i;						\
no_resize:								\
	name##_vec_free (copy);						\
	return NULL;							\
}									\

#define VEC_DEFINE_EQ(name)						\
									\
bool name##_vec_eq (const struct name##_vec *o,				\
		    const struct name##_vec *peer)			\
{									\
	size_t i;							\
									\
	if (o->count != peer->count)					\
		return false;						\
									\
	for (i = 0; i < o->count; ++i)					\
		if (!name##_eq (o->data[i], peer->data[i]))		\
			return false;					\
									\
	return true;							\
}									\

#define VEC_DEFINE_HASH(name)						\
									\
size_t name##_vec_hash (const struct name##_vec *o, size_t iv)		\
{									\
	size_t i;							\
									\
	for (i = 0; i < o->count; ++i)					\
		iv = name##_hash (o->data[i], iv);			\
									\
	return iv;							\
}									\

#endif  /* CAPSA_VEC_H */
