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
	struct name##_vec *o;						\
									\
	if ((o = malloc (sizeof (*o))) == NULL)				\
		return o;						\
									\
	name##_vec_init (o);						\
	return o;							\
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
static inline								\
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
									\
static inline								\
int name##_vec_cmp (const struct name##_vec *o,				\
		    const struct name##_vec *p)				\
{									\
	const size_t min = o->count < p->count ? o->count : p->count;	\
	size_t i;							\
	int c;								\
									\
	for (i = 0; i < min; ++i)					\
		if ((c = name##_cmp (o->data[i], p->data[i])) < 0)	\
			return -1;					\
		else if (c > 0)						\
			return +1;					\
									\
	return o->count > min ? +1 : p->count > min ? -1 : 0;		\
}									\
									\
static inline								\
size_t name##_vec_hash (const struct name##_vec *o, size_t iv)		\
{									\
	size_t i;							\
									\
	for (i = 0; i < o->count; ++i)					\
		iv = name##_hash (o->data[i], iv);			\
									\
	return iv;							\
}									\
									\
static inline bool name##_vec_expand (struct name##_vec *o)		\
{									\
	return vec_expand ((void *) o, sizeof (type));			\
}									\
									\
static inline								\
bool name##_vec_insert (struct name##_vec *o, size_t i, ctype e)	\
{									\
	name##_free (o->data[i]);					\
	return name##_copy (&e, o->data + i);				\
}									\
									\
static inline bool name##_vec_append (struct name##_vec *o, ctype e)	\
{									\
	if ((o->count >= o->avail && !name##_vec_expand (o)) ||		\
	    !name##_copy (&e, o->data + o->count))			\
		return false;						\
									\
	++o->count;							\
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
									\
static inline								\
bool name##_vec_copy (const struct name##_vec *s, struct name##_vec *d)	\
{									\
	size_t i;							\
									\
	if ((d->data = malloc (s->avail * sizeof (type))) == NULL)	\
		return false;						\
									\
	for (i = 0; i < s->count; ++i)					\
		if (!name##_copy (s->data + i, d->data + i))		\
			goto no_copy;					\
									\
	d->count = s->count;						\
	d->avail = s->avail;						\
	return true;							\
no_copy:								\
	d->count = i;							\
	name##_vec_fini (d);						\
	return false;							\
}									\

#define VEC_DECLARE(name) \
	VEC_DECLARE_TYPED(name, struct name *, const struct name *)

#endif  /* CAPSA_VEC_H */
