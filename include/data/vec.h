/*
 * Colibri Dynamic Array (Vector)
 *
 * Copyright (c) 2014-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_VEC_H
#define COLIBRI_DATA_VEC_H  1

#include <stdlib.h>

struct atom_vec;

int vec_resize (struct atom_vec *o, size_t size);
int vec_expand (struct atom_vec *o, size_t i);

#define VEC_DECLARE_TYPED(name, type, ctype)				\
									\
struct name##_vec {							\
	size_t count, avail;						\
	type **data;							\
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
static inline int name##_vec_resize (struct name##_vec *o, size_t next)	\
{									\
	return vec_resize ((void *) o, next);				\
}									\
									\
static inline int name##_vec_expand (struct name##_vec *o, size_t i)	\
{									\
	return vec_expand ((void *) o, i);				\
}									\
									\
static inline								\
void name##_vec_insert (struct name##_vec *o, size_t i, ctype *e)	\
{									\
	name##_free (o->data[i]);					\
	o->data[i] = name##_copy (e);					\
}									\
									\
static inline int name##_vec_append (struct name##_vec *o, ctype *e)	\
{									\
	if (o->count >= o->avail &&					\
	    !name##_vec_resize (o, o->avail * 2 | 1))			\
		return 0;						\
									\
	o->data[o->count++] = name##_copy (e);				\
	return 1;							\
}									\
									\
static inline								\
void name##_vec_insert_nc (struct name##_vec *o, size_t i, type *e)	\
{									\
	name##_free (o->data[i]);					\
	o->data[i] = e;							\
}									\
									\
static inline int name##_vec_append_nc (struct name##_vec *o, type *e)	\
{									\
	if (o->count >= o->avail &&					\
	    !name##_vec_resize (o, o->avail * 2 | 1)) {			\
		name##_free (e);					\
		return 0;						\
	}								\
									\
	o->data[o->count++] = e;					\
	return 1;							\
}									\
									\
struct name##_vec *name##_vec_alloc (void);				\
void name##_vec_free (struct name##_vec *o);				\
									\
struct name##_vec *name##_vec_copy  (const struct name##_vec *o);	\
									\
int    name##_vec_eq   (const struct name##_vec *o,			\
			const struct name##_vec *peer);			\
size_t name##_vec_hash (const struct name##_vec *o, size_t iv);		\
									\
static inline int name##_compar (const void *a, const void *b)		\
{									\
	return name##_cmp (*(const void **) a, *(const void **) b);	\
}									\
									\
static inline void name##_vec_sort (struct name##_vec *o)		\
{									\
	qsort (o->data, o->count, sizeof (o->data[0]), name##_compar);	\
}									\
									\
static inline								\
size_t name##_vec_search (const struct name##_vec *o, ctype *key)	\
{									\
	type **e = bsearch (&key, o->data, o->count,			\
			    sizeof (o->data[0]), name##_compar);	\
									\
	return e == NULL ? -1 : (e - o->data);				\
}									\

#define VEC_DECLARE(name) \
	VEC_DECLARE_TYPED(name, struct name, const struct name)

#define VEC_DEFINE_ALLOC(name)						\
									\
struct name##_vec *name##_vec_alloc (void)				\
{									\
	struct name##_vec *o;						\
									\
	if ((o = malloc (sizeof (*o))) == NULL)				\
		return o;						\
									\
	name##_vec_init (o);						\
	return o;							\
}									\
									\
void name##_vec_free (struct name##_vec *o)				\
{									\
	if (o == NULL)							\
		return;							\
									\
	name##_vec_fini (o);						\
	free (o);							\
}									\

#define VEC_DEFINE_COPY(name)						\
									\
struct name##_vec *name##_vec_copy  (const struct name##_vec *o)	\
{									\
	struct name##_vec *copy;					\
	size_t i;							\
									\
	if ((copy = name##_vec_alloc ()) == NULL)			\
		return copy;						\
									\
	if (!name##_vec_resize (copy, o->avail))			\
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
int name##_vec_eq (const struct name##_vec *o,				\
		   const struct name##_vec *peer)			\
{									\
	size_t i;							\
									\
	if (o->count != peer->count)					\
		return 0;						\
									\
	for (i = 0; i < o->count; ++i)					\
		if (!name##_eq (o->data[i], peer->data[i]))		\
			return 0;					\
									\
	return 1;							\
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

#endif  /* COLIBRI_DATA_VEC_H */
